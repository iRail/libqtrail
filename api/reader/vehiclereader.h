//
// Configuration
//

// Include guard
#ifndef VEHICLEREADER_H
#define VEHICLEREADER_H

// Includes
#include <QHash>
#include <QDateTime>
#include "api/reader.h"
#include "api/data/stop.h"
#include "api/data/vehicle.h"

namespace iRail
{
    class VehicleReader : public Reader
    {
    Q_OBJECT
    public:
        // Construction and destruction
        VehicleReader();

        // Reader interface
        void readDocument();

        // Basic I/O
        double version() const;
        QDateTime timestamp() const;
        Vehicle* vehicle() const;
        QList<Stop*> stops() const;
    private:
        // Member data
        double mVersion;
        QDateTime mTimestamp;
        Vehicle* mVehicle;
        QList<Stop*> mStops;

        // Tag readers
        void allocate();
        void readVehicleInformation();
        Vehicle* readVehicle();
        QList<Stop*> readStops();
        Stop* readStop();
        Station* readStation();
        QDateTime readDatetime();
    };
}

#endif // VEHICLEREADER_H
