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
        VehicleReader();
        void readDocument();
        VehiclePointer* vehicle();
    private:
        // Member data
        VehiclePointer* mVehicle;
        QDateTime mTimestamp;
        double mVersion;

        // Tag readers
        void allocate();
        Vehicle* readVehicle();
        Vehicle::Location readLocation();
        QList<Vehicle::Stop> readStops();
        Vehicle::Stop readStop();
        QString readStation();
        double readDelay();
        QDateTime readDatetime();
    };
}

#endif // STATIONREADER_H
