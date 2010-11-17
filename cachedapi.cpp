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
    connect(this, SIGNAL(replyStations(QMap<QString, StationPointer>*)), this, SLOT(cacheStations(QMap<QString, StationPointer>*)));
}


//
// Request slots
//

void CachedAPI::requestStations()
{
    // Check the cache
    const QMap<QString, StationPointer>* tCachedStations = mStorage->stations();
    if (tCachedStations != 0)
    {
        emit replyStations(new QMap<QString, StationPointer>(*tCachedStations));
        return;
    }

    // Request a new list
    emit miss();
    AsyncAPI::requestStations();

}

void CachedAPI::requestConnections(const ConnectionRequestPointer& iConnectionRequest)
{
    // Request a new list
    emit miss();
    AsyncAPI::requestConnections(iConnectionRequest);
}

void CachedAPI::requestVehicle(const QString& iVehicleId)
{
    // TODO: perform a cache lookup, but somehow mind expiry time!

    // Request a new list
    emit miss();
    AsyncAPI::requestVehicle(iVehicleId);
}


//
// Caching slots
//

void CachedAPI::cacheStations(QMap<QString, StationPointer>* iStations)
{
    if (iStations != 0)
        mStorage->setStations(*iStations);
}
