//
// Configuration
//

// Includes
#include "memorystorage.h"

// Namespaces
using namespace iRail;


//
// Construction and destruction
//

MemoryStorage::MemoryStorage()
{
    mStations = 0;
}


//
// Getters
//

const QList<StationPointer>& MemoryStorage::stations_get() const throw(StorageException)
{
    if (mStations == 0)
        throw StorageException("stations not in cache");
    return *mStations;
}


//
// Setters
//

void MemoryStorage::stations_set(const QList<StationPointer>& iStations) throw(StorageException)
{
    mStations = new QList<StationPointer>(iStations);
}
