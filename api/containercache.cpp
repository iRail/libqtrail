//
// Configuration
//

// Includes
#include "containercache.h"

// Namespaces
using namespace iRail;

// Singleton
ContainerCache* ContainerCache::mInstance = 0;


//
// Construction and destruction
//

ContainerCache::ContainerCache(QObject* iParent) : QObject(iParent)
{
    mStationList = 0;
    mVehicleList = 0;
    mStopList = 0;
}

ContainerCache& ContainerCache::instance()
{
    if (mInstance == 0)
        mInstance = new ContainerCache();
    return *mInstance;
}

ContainerCache::~ContainerCache()
{
    // TODO: doesn't this happen automatically through QObject(parent)?
    delete mStationList;
    delete mVehicleList;
    delete mStopList;
    qDeleteAll(mStopLists);
    qDeleteAll(mDepartureLists);
    qDeleteAll(mJourneyLists);
    qDeleteAll(mConnectionLists);
}


//
// Container request methods
//

StationList* ContainerCache::stationList()
{
    if (mStationList == 0)
        mStationList = new StationList(this);
    return mStationList;
}

VehicleList* ContainerCache::vehicleList()
{
    if (mVehicleList == 0)
        mVehicleList = new VehicleList(this);
    return mVehicleList;
}

StopList* ContainerCache::stopList()
{
    if (mStopList == 0)
        mStopList = new StopList(this);
    return mStopList;
}

StopList* ContainerCache::stopList(const Vehicle::Id& iVehicleId)
{
    if (mStopLists.contains(iVehicleId))
        return mStopLists[iVehicleId];
    else
    {
        StopList* oStopList = new StopList(iVehicleId);
        mStopLists.insert(iVehicleId, oStopList);
        return oStopList;
    }
}

DepartureList* ContainerCache::departureList(const Station::Id& iStationId)
{
    if (mDepartureLists.contains(iStationId))
        return mDepartureLists[iStationId];
    else
    {
        DepartureList* oDepartureList = new DepartureList(iStationId);
        mDepartureLists.insert(iStationId, oDepartureList);
        return oDepartureList;
    }
}

JourneyList* ContainerCache::journeyList(const Station::Id& iOrigin, const Station::Id& iDestination)
{
    QPair<Station::AbstractId, Station::AbstractId> iIdPair(iOrigin, iDestination);
    if (mJourneyLists.contains(iIdPair))
        return mJourneyLists[iIdPair];
    else
    {
        JourneyList* oJourneyList = new JourneyList(iOrigin, iDestination);
        mJourneyLists.insert(iIdPair, oJourneyList);
        return oJourneyList;
    }
}

ConnectionList* ContainerCache::connectionList(const Journey::Id& iJourneyId)
{
    if (mConnectionLists.contains(iJourneyId))
        return mConnectionLists[iJourneyId];
    else
    {
        ConnectionList* oConnectionList(new ConnectionList(iJourneyId));
        mConnectionLists.insert(iJourneyId, oConnectionList);
        return oConnectionList;
    }
}
