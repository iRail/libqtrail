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

const QList<StationPointer>* MemoryStorage::stations() const
{
    return mStations;
}


//
// Setters
//

void MemoryStorage::setStations(const QList<StationPointer>* iStations)
{
    mStations = new QList<StationPointer>(*iStations);
}
