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
        StationList* stationList() const;
        VehicleList* vehicleList() const;
        StopList* stopList() const;
        StopList* stopList(const Vehicle::AbstractId& iVehicleId) const;
        DepartureList* departureList(const Station::AbstractId& iStationId) const;
        JourneyList* journeyList(const Station::AbstractId& iOriginId, const Station::AbstractId& iDestinationId) const;
        ConnectionList* connectionList(const Journey::AbstractId& iJourneyId) const;

    private:
        // Member data
        StationList* mStationList;
        VehicleList* mVehicleList;
        StopList* mStopList;
        QHash<Vehicle::AbstractId, StopList*> mStopLists;
        QHash<Station::AbstractId, DepartureList*> mDepartureLists;
        QHash<QPair<Station::AbstractId, Station::AbstractId>, JourneyList*> mJourneyLists;
        QHash<Journey::AbstractId, ConnectionList*> mConnectionLists;

        // Singleton
        static ContainerCache* mInstance;
    };

}

#endif // CONTAINERCACHE_H
