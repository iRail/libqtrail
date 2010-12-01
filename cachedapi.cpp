//
// Configuration
//

// Includes
#include "cachedapi.h"

// Namespaces
using namespace iRail;


//
// Construction and destruction
//

CachedAPI::CachedAPI(const QString& iClientID, const QString& iClientVersion, Storage* iStorage) : AsyncAPI(iClientID, iClientVersion), mStorage(iStorage)
{
    connect(this, SIGNAL(replyStations(QMap<QString, StationPointer>*, QDateTime)), this, SLOT(cacheStations(QMap<QString, StationPointer>*, QDateTime)));
}


//
// Request slots
//

void CachedAPI::requestStations(bool& oCached)
{
    // Check the cache
    const QMap<QString, StationPointer>* tCachedStations = mStorage->stations();
    if (tCachedStations != 0 && mStorage->stationsTimestamp().secsTo(QDateTime::currentDateTime()) <= STATIONS_REFRESH)
    {
        oCached = true;
        emit replyStations(new QMap<QString, StationPointer>(*tCachedStations), mStorage->stationsTimestamp());
        return;
    }

    // Request a new list
    oCached = false;
    mStorage->clearStations();
    AsyncAPI::requestStations();

}

void CachedAPI::requestConnections(const ConnectionRequestPointer& iConnectionRequest, bool& oCached)
{
    // Request a new list
    oCached = false;
    AsyncAPI::requestConnections(iConnectionRequest);
}

void CachedAPI::requestVehicle(const QString& iVehicleId, bool& oCached)
{
    // TODO: perform a cache lookup, but somehow mind expiry time!

    // Request a new list
    oCached = false;
    AsyncAPI::requestVehicle(iVehicleId);
}

void CachedAPI::requestLiveboard(const QString& iStationId, bool& oCached)
{
    // Request a new list
    oCached = false;
    AsyncAPI::requestLiveboard(iStationId);
}


//
// Caching slots
//

void CachedAPI::cacheStations(QMap<QString, StationPointer>* iStations, QDateTime iTimestamp)
{
    disconnect(this, SIGNAL(replyStations(QMap<QString, StationPointer>*, QDateTime)), this, SLOT(cacheStations(QMap<QString, StationPointer>*, QDateTime)));
    if (iStations != 0 && mStorage->stations() == 0)
    {
        mStorage->setStations(*iStations, iTimestamp);
    }
}
