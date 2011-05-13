//
// Configuration
//

// Include guard
#ifndef CONTAINERCACHE_H
#define CONTAINERCACHE_H

// Includes
#include <QString>
#include <QHash>
#include <QObject>
#include "api/container/stationlist.h"
#include "api/container/vehiclelist.h"
#include "api/container/stoplist.h"
#include "api/container/journeylist.h"
#include "api/container/departurelist.h"
#include "api/container/connectionlist.h"

namespace iRail
{
    class ContainerCache : public QObject
    {
    Q_OBJECT
    public:
        // Construction and destruction
    private:
        ContainerCache(QObject* iParent = 0);
        ~ContainerCache();
    public:
        static ContainerCache& instance();

        // Container request methods
        StationList* stationList();
        VehicleList* vehicleList();
        StopList* stopList();
        StopList* stopList(Vehicle::Id const* iVehicleId);
        DepartureList* departureList(Station::Id const* iStationId);
        JourneyList* journeyList(Station::Id const* iOriginId, Station::Id const* iDestinationId);
        ConnectionList* connectionList(Journey::Id const* iJourneyId);

    private:
        // Member data
        StationList* mStationList;
        VehicleList* mVehicleList;
        StopList* mStopList;
        QHash<Vehicle::Id, StopList*> mStopLists;
        QHash<Station::Id, DepartureList*> mDepartureLists;
        QHash<QPair<Station::Id, Station::Id>, JourneyList*> mJourneyLists;
        QHash<Journey::Id, ConnectionList*> mConnectionLists;

        // Singleton
        static ContainerCache* mInstance;
    };

}

#endif // CONTAINERCACHE_H
