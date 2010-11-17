//
// Configuration
//

// Include guard
#ifndef VEHICLEREADER_H
#define VEHICLEREADER_H

// Includes
#include "api/reader.h"
#include "api/station.h"
#include "api/vehicle.h"
#include <QList>
#include <QDateTime>

namespace iRail
{
    class VehicleReader : public Reader
    {
    Q_OBJECT
    public:
        VehicleReader(const QList<StationPointer>* iStations);
        void readDocument();
        VehiclePointer* vehicle();
    private:
        // Member data
        const QList<StationPointer>* mStations;
        VehiclePointer* mVehicle;
        QDateTime mTimestamp;
        double mVersion;

        // Tag readers
        void allocate();
        Vehicle* readVehicle();
        Vehicle::Location readLocation();
        QList<Vehicle::Stop> readStops();
        Vehicle::Stop readStop();
        StationPointer readStation();
        double readDelay();
        QDateTime readDatetime();
    };
}

#endif // STATIONREADER_H
