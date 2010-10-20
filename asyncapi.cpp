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
    mStorage = 0;
}

void AsyncAPI::setStorage(Storage* iStorage)
{
    // Save the cache object for later usage
    mStorage = iStorage;

    // Connect caching signals
    connect(this, SIGNAL(stations_reply(QList<StationPointer>)), mStorage, SLOT(stations_set(QList<StationPointer>)));
}


//
// Cache request methods
//

QList<StationPointer> AsyncAPI::stations_cache() throw(StorageException)
{
    if (!mStorage)
        throw StorageException("no storage defined");
    return QList<StationPointer>(mStorage->stations_get());
}


//
// Request slots
//

void AsyncAPI::stations_request()
{
    // Construct URL
    QUrl tURL = createBaseURL();
    tURL.setPath("stations/");

    // Create a request
    network_request(getRequest(tURL), this, SLOT(stations_process()));
}

void AsyncAPI::connections_request(ConnectionRequestPointer iConnectionRequest)
{
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
    network_request(getRequest(tURL), this, SLOT(connections_process()));
}


//
// Processing methods
//

void AsyncAPI::stations_process()
{
    // Parse the data
    try
    {
#ifdef BETRAINS_VALIDATINGXML
        mParser.validateStations(tXmlInputSource);
        resetXmlInputSource(tXmlInputSource, iReply);
#endif // BETRAINS_VALIDATINGXML
        QList<StationPointer> oStations = mParser.parseStations(mNetworkReply);
        emit stations_reply(oStations);
    }
    catch (Exception& iException)
    {
        // TODO: emit the exception?
        emit error(iException.toString());
    }

    // Clean up
    network_cleanup();
}


void AsyncAPI::connections_process()
{
    // Parse the data
    try
    {
#ifdef BETRAINS_VALIDATINGXML
        mParser.validateConnections(tXmlInputSource);
        resetXmlInputSource(tXmlInputSource, iReply);
#endif // BETRAINS_VALIDATINGXML
        QList<ConnectionPointer> oStations = mParser.parseConnections(mNetworkReply);
        emit connections_reply(oStations);
    }
    catch (Exception& iException)
    {
        // TODO: emit the exception?
        emit error(iException.toString());
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
        // TODO: networkreply can be 0, when no connection could be established
        mNetworkReply = mNetworkAccessManager.get(iRequest);
        connect(mNetworkReply, SIGNAL(downloadProgress(qint64,qint64)), this, SLOT(network_progress(qint64,qint64)));
        connect(mNetworkReply, SIGNAL(finished()), iObject, iSlot);
    }
    else
    {
        emit error("Concurrent network request are not possible.");
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

