//
// Configuration
//

// Includes
#include "asyncapi.h"
#include <QByteArray>

// Namespaces
using namespace iRail;


//
// Construction and destruction
//

AsyncAPI::AsyncAPI(const QString& iClientID, const QString& iClientVersion) : mClientID(iClientID), mClientVersion(iClientVersion)
{
    mUserAgent.append("BETrains-Qt/" + mClientVersion + " (" + mClientID + " edition)");
    mNetworkReply = 0;
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


//
// Request slots
//

void AsyncAPI::requestStations()
{
    // Reset
    mHasError = false;

    // Construct URL
    QUrl tURL = createBaseURL();
    tURL.setPath("stations/");

    // Create a request
    network_request(getRequest(tURL), this, SLOT(processStations()));
}

void AsyncAPI::requestConnections(ConnectionRequestPointer iConnectionRequest)
{
    // Reset
    mHasError = false;

    // Construct URL
    QUrl tURL = createBaseURL();
    tURL.setPath("connections/");

    // Set the parameters
    tURL.addQueryItem("from", iConnectionRequest->getOrigin());
    tURL.addQueryItem("to", iConnectionRequest->getDestination());
    if (iConnectionRequest->hasDateTime())
    {
        ConnectionRequest::DateTime tDateTime = iConnectionRequest->getDateTime();
        QString tDate = tDateTime.datetime.date().toString("ddMMyy");
        tURL.addQueryItem("date", tDate);
        QString tTime = tDateTime.datetime.time().toString("hhmm");
        tURL.addQueryItem("time", tTime);
        QString tType = tDateTime.type == ConnectionRequest::Arrival ? "arrive" : "depart";
        tURL.addQueryItem("timeSel", tType);
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
#ifdef BETRAINS_VALIDATINGXML
        mParser.validateStations(tXmlInputSource);
        resetXmlInputSource(tXmlInputSource, iReply);
#endif // BETRAINS_VALIDATINGXML
        QList<StationPointer> oStations = mParser.parseStations(mNetworkReply);
        emit replyStations(oStations);
    }
    catch (Exception& iException)
    {
        mError = iException;
        mHasError = true;
    }

    // Clean up
    network_cleanup();
}


void AsyncAPI::processConnections()
{
    // Parse the data
    try
    {
#ifdef BETRAINS_VALIDATINGXML
        mParser.validateConnections(tXmlInputSource);
        resetXmlInputSource(tXmlInputSource, iReply);
#endif // BETRAINS_VALIDATINGXML
        QList<ConnectionPointer> oStations = mParser.parseConnections(mNetworkReply);
        emit replyConnections(oStations);
    }
    catch (Exception& iException)
    {
        mError = iException;
        mHasError = true;
    }

    // Clean up
    network_cleanup();
}

//
// Network routines
//

void AsyncAPI::network_request(QNetworkRequest iRequest, QObject* iObject, const char* iSlot)
{
    if (mNetworkReply == 0)
    {
        emit action("performing network request");
        mNetworkReply = mNetworkAccessManager.get(iRequest);        
        // TODO: networkreply can be 0, when no connection could be established

        emit action("downloading and decoding network reply");
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
        int smallprogress = iProgress/totalSteps * 100;
        emit progress(smallprogress);
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

