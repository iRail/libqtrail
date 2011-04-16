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
    mUserAgent.append("BeTrains-Qt/" + mClientVersion + " (" + mClientID + " edition)");
    mNetworkReply = 0;

    switch (QLocale::system().language())
    {
    case QLocale::English:
        mClientLanguage = "en";
        break;
    case QLocale::French:
        mClientLanguage = "fr";
        break;
    case QLocale::German:
        mClientLanguage = "de";
        break;
    case QLocale::Dutch:
        mClientLanguage = "nl";
        break;
    default:
        mClientLanguage = "en";
    }

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

void AsyncAPI::requestConnections(const ConnectionRequestPointer& iConnectionRequest)
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

void AsyncAPI::requestVehicle(const QString& iVehicleId)
{
    // Setup
    mHasError = false;
    mProgressHandler.enter();

    // Construct URL
    QUrl tURL = createBaseURL();
    tURL.setPath("vehicle/");

    // Set the parameters
    tURL.addQueryItem("id", iVehicleId);

    // Create a request
    network_request(getRequest(tURL), this, SLOT(processVehicle()));
}

void AsyncAPI::requestLiveboard(const LiveboardRequestPointer& iLiveboardRequest)
{
    // Setup
    mHasError = false;
    mProgressHandler.enter();

    // Construct URL
    QUrl tURL = createBaseURL();
    tURL.setPath("liveboard/");

    // Set the parameters
    tURL.addQueryItem("id", iLiveboardRequest->station());
    if (iLiveboardRequest->timed())
    {
        tURL.addQueryItem("date", iLiveboardRequest->time()->date().toString("ddMMyy"));
        tURL.addQueryItem("time", iLiveboardRequest->time()->time().toString("hhmm"));
    }

    // Create a request
    network_request(getRequest(tURL), this, SLOT(processLiveboard()));
}


//
// Processing methods
//

void AsyncAPI::processStations()
{
    // Parse the data
    QMap<QString, StationPointer>* oStations;
    QDateTime tTimestamp;
    try
    {
        oStations = mParser.parseStations(mNetworkReply, tTimestamp);
    }
    catch (Exception& iException)
    {
        mError = iException;
        mHasError = true;
        oStations = 0;
    }

    // Clean up
    mProgressHandler.exit();
    network_cleanup();
    emit replyStations(oStations, tTimestamp);
}

void AsyncAPI::processConnections()
{
    // Parse the data;
    QList<ConnectionPointer>* oConnections;
    QDateTime tTimestamp;
    try
    {
        oConnections = mParser.parseConnections(mNetworkReply, tTimestamp);
    }
    catch (Exception& iException)
    {
        mError = iException;
        mHasError = true;
        oConnections = 0;
    }

    // Clean up
    mProgressHandler.exit();
    network_cleanup();
    emit replyConnections(oConnections, tTimestamp);
}

void AsyncAPI::processVehicle()
{
    // Parse the data;
    VehiclePointer* oVehicle;
    QDateTime tTimestamp;
    try
    {
        oVehicle = mParser.parseVehicle(mNetworkReply, tTimestamp);
    }
    catch (Exception& iException)
    {
        mError = iException;
        mHasError = true;
        oVehicle = 0;
    }

    // Clean up
    mProgressHandler.exit();
    network_cleanup();
    emit replyVehicle(oVehicle, tTimestamp);
}

void AsyncAPI::processLiveboard()
{
    // Parse the data;
    LiveboardPointer* oLiveboard;
    QDateTime tTimestamp;
    try
    {
        oLiveboard = mParser.parseLiveboard(mNetworkReply, tTimestamp);
    }
    catch (Exception& iException)
    {
        mError = iException;
        mHasError = true;
        oLiveboard = 0;
    }

    // Clean up
    mProgressHandler.exit();
    network_cleanup();
    emit replyLiveboard(oLiveboard, tTimestamp);
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

        // TODO: this doesn't cach errors properly, e.g. when connection to a nonexisting url
        if (mNetworkReply->error() != QNetworkReply::NoError)
        {
            qDebug() << mNetworkReply->errorString();
        }

        emit action("Downloading and decoding network reply");
        connect(mNetworkReply, SIGNAL(downloadProgress(qint64,qint64)), this, SLOT(network_progress(qint64,qint64)));
        connect(mNetworkReply, SIGNAL(finished()), iObject, iSlot);
    }
    else
    {
        // TODO: flagging this doesn't cancel cached connection request
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
    oUrl.addQueryItem("lang", mClientLanguage);
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

