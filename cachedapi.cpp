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

void CachedAPI::requestStations()
{
    // Check the cache
    QList<StationPointer>* tCachedStations = mStorage->stations();
    if (tCachedStations != 0)
    {
        emit replyStations(*tCachedStations);
        return;
    }

    // Request a new list
    emit progress_start();
    connect(this, SIGNAL(replyStations(QList<StationPointer>)), this, SLOT(cacheStations(QList<StationPointer>)));
    AsyncAPI::requestStations();

}

void CachedAPI::requestConnections(ConnectionRequestPointer iConnectionRequest)
{
    // Request a new list
    emit progress_start();
    AsyncAPI::requestConnections(iConnectionRequest);
}


//
// Caching slots
//

void CachedAPI::cacheStations(QList<StationPointer> iStations)
{
    mStorage->setStations(iStations);
    disconnect(this, SIGNAL(replyStations(QList<StationPointer>)), this, SLOT(cacheStations(QList<StationPointer>)));
}
