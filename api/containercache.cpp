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

StopListPointer ContainerCache::stopList(const Vehicle& iVehicle) const
{
    return StopListPointer(new StopList(iVehicle, this));
}

DepartureListPointer ContainerCache::departureList(const Station& iStation) const
{
    return DepartureListPointer(new DepartureList(iStation, this));
}

JourneyListPointer ContainerCache::journeyList(const POI& iDeparture, const POI& iArrival) const
{
    return JourneyListPointer(new JourneyList(iDeparture, iArrival, this));
}

ConnectionListPointer ContainerCache::connectionList(const Journey& iJourney) const
{
    return ConnectionListPointer(new ConnectionList(iJourney, this));
}
