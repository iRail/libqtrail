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
    connect(this, SIGNAL(replyStations(QList<StationPointer>*)), this, SLOT(cacheStations(QList<StationPointer>*)));
}


//
// Request slots
//

void CachedAPI::requestStations()
{
    // Check the cache
    const QList<StationPointer>* tCachedStations = mStorage->stations();
    if (tCachedStations != 0)
    {
        emit replyStations(new QList<StationPointer>(*tCachedStations));
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


//
// Caching slots
//

void CachedAPI::cacheStations(QList<StationPointer>* iStations)
{
    if (iStations != 0)
        mStorage->setStations(*iStations);
}
