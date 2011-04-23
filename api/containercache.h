//
// Configuration
//

// Include guard
#ifndef CONTAINERCACHE_H
#define CONTAINERCACHE_H

// Includes
#include <QString>
#include <QHash>
#include "api/container/stationlist.h"
#include "api/container/vehiclelist.h"
#include "api/container/stoplist.h"
#include "api/container/journeylist.h"
#include "api/container/departurelist.h"
#include "api/container/connectionlist.h"

namespace iRail
{
    class ContainerCache
    {
    public:
        // Construction and destruction
    private:
        ContainerCache(QObject* iParent = 0);
    public:
        static ContainerCache& instance();
        ~ContainerCache();

        // Container request methods
        StationListPointer stationList() const;
        VehicleListPointer vehicleList() const;
        StopListPointer stopList() const;
        StopListPointer stopList(const Vehicle::Id& iVehicleId) const;
        DepartureListPointer departureList(const Station::Id& iStationId) const;
        JourneyListPointer journeyList(const Station::Id& iOriginId, const Station::Id& iDestinationId) const;
        ConnectionListPointer connectionList(const Journey::Id& iJourneyId) const;

    private:
        // Member data
        StationListPointer mStationList;
        VehicleListPointer mVehicleList;
        StopListPointer mStopList;
        QHash<Vehicle::Id, StopListPointer> mStopLists;
        QHash<Station::Id, DepartureListPointer> mDepartureLists;
        QHash<QPair<Station::Id, Station::Id>, JourneyListPointer> mJourneyLists;
        QHash<Journey::Id, ConnectionListPointer> mConnectionLists;

        // Singleton
        static ContainerCache* mInstance;
    };

}

#endif // CONTAINERCACHE_H
