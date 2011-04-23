//
// Configuration
//

// Include guard
#ifndef CONTAINERCACHE_H
#define CONTAINERCACHE_H

// Includes
#include <QString>
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
    Q_OBJECT
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
        StopListPointer stopList(const Vehicle& iVehicle) const;
        DepartureListPointer departureList(const Station& iStation) const;
        JourneyListPointer journeyList(const Stop& iDeparture, const Stop& iArrival) const;
        ConnectionListPointer connectionList(const Journey& iJourney) const;

    private:
        // Member data
        StationListPointer mStationList;
        VehicleListPointer mVehicleList;

        // Singleton
        static ContainerCache* mInstance;
    };

}

#endif // CONTAINERCACHE_H
