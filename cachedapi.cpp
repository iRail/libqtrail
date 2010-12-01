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
    connect(this, SIGNAL(replyStations(QMap<QString, StationPointer>*, QDateTime)), this, SLOT(cacheStations(QMap<QString, StationPointer>*, QDateTime)));
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
    if (iStations != 0)
    {
        const QMap<QString, StationPointer>* tCachedStations = mStorage->stations();
        if (tCachedStations != 0 && mStorage->stationsTimestamp() == iTimestamp)
        {
            qWarning() << "! " << "Cached data is outdated, but API did not return anything new, forcing it to seem refreshed";
            mStorage->setStations(*iStations, QDateTime::currentDateTime());
            // TODO: is this good? or keep on refreshing?
        }
        else
            mStorage->setStations(*iStations, iTimestamp);
    }
}
