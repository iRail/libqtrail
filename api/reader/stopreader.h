//
// Configuration
//

// Include guard
#ifndef VEHICLEREADER_H
#define VEHICLEREADER_H

// Includes
#include "api/reader.h"
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
        VehiclePointer* vehicle(QDateTime& oTimestamp);
    private:
        // Member data
        VehiclePointer* mVehicle;
        QDateTime mTimestamp;
        double mVersion;

        // Tag readers
        void allocate();
        Vehicle* readVehicleInformation();
        Vehicle* readVehicle();
        QList<Vehicle::Stop> readStops();
        Vehicle::Stop readStop();
        QString readStation();
        QDateTime readDatetime();
    };
}

#endif // STATIONREADER_H
