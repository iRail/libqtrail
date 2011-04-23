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

}

ContainerCache& ContainerCache::instance()
{
    if (mInstance == 0)
        mInstance = new ContainerCache();
    return *mInstance;
}

ContainerCache::~ContainerCache()
{

}


//
// Container request methods
//

StationListPointer ContainerCache::stationList() const
{
    if (mStationList.isNull())
        mStationList = StationListPointer(new StationList(this));
    return mStationList;
}

VehicleListPointer ContainerCache::vehicleList() const
{
    if (mVehicleList.isNull())
        mVehicleList = VehicleListPointer(new StationList(this));
    return mVehicleList;
}

StopListPointer ContainerCache::stopList() const
{
    if (mStopList.isNull())
        mStopList = StopListPointer(new StopList());
    return mStopList;
}

StopListPointer ContainerCache::stopList(const Vehicle::Id& iVehicleId) const
{
    if (mStopLists.contains(iVehicleId))
        return mStopLists[iVehicleId];
    else
    {
        StopListPointer oStopList(new StopList(iVehicleId));
        mStopLists.insert(iVehicleId, oStopList);
        return oStopList;
    }
}

DepartureListPointer ContainerCache::departureList(const Station::Id& iStationId) const
{
    if (mDepartureLists.contains(iStationId))
        return mDepartureLists[iStationId];
    else
    {
        DepartureListPointer oDepartureList(new DepartureList(iStationId));
        mDepartureLists.insert(iStationId, oDepartureList);
        return oDepartureList;
    }
}

JourneyListPointer ContainerCache::journeyList(const Station::Id& iOrigin, const Station::Id& iDestination) const
{
    (QPair<Station::Id, Station::Id> iIdPair(iOrigin, iDestination);
    if (mJourneyLists.contains(iIdPair))
        return mJourneyLists[iIdPair];
    else
    {
        JourneyListPointer oJourneyList(new JourneyList(iOrigin, iDestination));
        mJourneyLists.insert(iIdPair, oJourneyList);
        return oJourneyList;
    }
}

ConnectionListPointer ContainerCache::connectionList(const Journey::Id& iJourneyId) const
{
    if (mConnectionLists.contains(iJourneyId))
        return mConnectionLists[iJourneyId];
    else
    {
        ConnectionListPointer oConnectionList(new ConnectionList(iJourneyId));
        mConnectionLists.insert(iJourneyId, oConnectionList);
        return oConnectionList;
    }
}
