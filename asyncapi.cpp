//
// Configuration
//

// Includes
#include "asyncapi.h"
#include <QByteArray>
#include <QApplication>

// Namespaces
using namespace iRail;


//
// Construction and destruction
//

AsyncAPI::AsyncAPI(const QString& iClientID, const QString& iClientVersion) : mClientID(iClientID), mClientVersion(iClientVersion)
{
    mUserAgent.append("BETrains-Qt/" + mClientVersion + " (" + mClientID + " edition)");
    mNetworkReply = 0;

    mProgressLevel = 0;
    mProgress = 0;
}


//
// Error handling
//


bool AsyncAPI::hasError() const
{
    return mHasError;
}

Exception AsyncAPI::error() const
{
    return mError;
}

QString AsyncAPI::errorString() const
{
    return mError.what();
}


//
// Request slots
//

void AsyncAPI::requestStations()
{
    // Setup
    mHasError = false;
    mProgressHandler.enter();

    // Construct URL
    QUrl tURL = createBaseURL();
    tURL.setPath("stations/");

    // Create a request
    network_request(getRequest(tURL), this, SLOT(processStations()));
}

void AsyncAPI::requestConnections(ConnectionRequestPointer iConnectionRequest)
{
    // Setup
    mHasError = false;
    mProgressHandler.enter();

    // Construct URL
    QUrl tURL = createBaseURL();
    tURL.setPath("connections/");

    // Set the parameters
    tURL.addQueryItem("from", iConnectionRequest->origin());
    tURL.addQueryItem("to", iConnectionRequest->destination());
    if (iConnectionRequest->timed())
    {
        const ConnectionRequest::Time *tTime = iConnectionRequest->time();
        tURL.addQueryItem("date", tTime->datetime.date().toString("ddMMyy"));
        tURL.addQueryItem("time", tTime->datetime.time().toString("hhmm"));
        tURL.addQueryItem("timeSel", tTime->type == ConnectionRequest::Arrival ? "arrive" : "depart");
    }

    // Create a request
    network_request(getRequest(tURL), this, SLOT(processConnections()));
}


//
// Processing methods
//

void AsyncAPI::processStations()
{
    // Parse the data
    try
    {
        QList<StationPointer>* oStations = mParser.parseStations(mNetworkReply);
        emit replyStations(oStations);
    }
    catch (Exception& iException)
    {
        mError = iException;
        mHasError = true;
        emit replyStations(0);
    }

    // Clean up
    mProgressHandler.exit();
    network_cleanup();
}


void AsyncAPI::processConnections()
{
    // Parse the data
    try
    {
        QList<ConnectionPointer>* oConnections = mParser.parseConnections(mNetworkReply);
        emit replyConnections(oConnections);
    }
    catch (Exception& iException)
    {
        mError = iException;
        mHasError = true;
        emit replyConnections(0);
    }

    // Clean up
    mProgressHandler.exit();
    network_cleanup();
}

//
// Network routines
//

void AsyncAPI::network_request(QNetworkRequest iRequest, QObject* iObject, const char* iSlot)
{
    if (mNetworkReply == 0)
    {
        emit action("Performing network request");
        // TODO: this is a quite blocking request, we shouldn't wait for it!
        QApplication::processEvents();  // Temporary fix
        mNetworkReply = mNetworkAccessManager.get(iRequest);        
        // TODO: networkreply can be 0, when no connection could be established

        emit action("Downloading and decoding network reply");
        connect(mNetworkReply, SIGNAL(downloadProgress(qint64,qint64)), this, SLOT(network_progress(qint64,qint64)));
        connect(mNetworkReply, SIGNAL(finished()), iObject, iSlot);
    }
    else
    {
        mError = Exception("concurrent network requests are currently impossible");
        mHasError = true;
    }
}

void AsyncAPI::network_progress(qint64 iProgress, qint64 totalSteps)
{
    if (iProgress >= totalSteps && totalSteps > 0)
    {
        int subprogress = iProgress/totalSteps * 100;
        mProgressHandler.setProgress(subprogress);
        emit mProgressHandler.progress();
    }
}

void AsyncAPI::network_cleanup()
{
    mNetworkReply->deleteLater();
    mNetworkReply = 0;
}


//
// Auxiliary
//

QUrl AsyncAPI::createBaseURL() const
{
    // Build base URL
    QUrl oUrl;
    oUrl.setScheme("http");
    oUrl.setHost("api.irail.be");
    oUrl.setQueryDelimiters('=', '&');

    return oUrl;
}

QNetworkRequest AsyncAPI::getRequest(QUrl iURL) const
{
    QNetworkRequest oRequest;
    oRequest.setUrl(iURL);
    oRequest.setRawHeader("User-Agent", mUserAgent);

    return oRequest;
}

