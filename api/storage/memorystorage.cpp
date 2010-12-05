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

const QMap<QString, StationPointer>* MemoryStorage::stations() const
{
    return mStations;
}

QDateTime MemoryStorage::stationsTimestamp() const
{
    return mStationsTimestamp;
}

void MemoryStorage::clearStations()
{
    delete mStations;
    mStations = 0;
}

const QList<QVariant>& MemoryStorage::userList(const QString &iName) const
{
    return mUserLists[iName];
}

void MemoryStorage::clearUserList(const QString &iName)
{
    mUserLists.remove(iName);
}


//
// Setters
//

void MemoryStorage::setStations(const QMap<QString, StationPointer>& iStations, const QDateTime& iTimestamp)
{
    mStations = new QMap<QString, StationPointer>(iStations);
    mStationsTimestamp = iTimestamp;

    // Manually detach the cached copy from all its COW brethren
    // This because QList deletes a COW-copy (which has not yet
    // been detached) when its parent gets destroyed...
    mStations->detach();
}

void MemoryStorage::setUserList(const QString &iName, const QList<QVariant> &iData)
{
    mUserLists[iName] = iData;
}


//
// Protected getters
//

const QMap<QString, QList<QVariant> >& MemoryStorage::userLists() const
{
    return mUserLists;
}
