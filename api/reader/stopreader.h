//
// Configuration
//

// Include guard
#ifndef STOPREADER_H
#define STOPREADER_H

// Includes
#include <QList>
#include <QDateTime>
#include "api/reader.h"
#include "api/data/poi.h"
#include "api/data/vehicle.h"

namespace iRail
{
    class StopReader : public Reader
    {
    Q_OBJECT
    public:
        // Construction and destruction
        StopReader();

        // Reader interface
        void readDocument();

        // Basic I/O
        double version() const;
        QDateTime timestamp() const;
        Vehicle* mVehicle() const;
        QList<POI*> stops() const;
    private:
        // Member data
        double mVersion;
        QDateTime mTimestamp;
        Vehicle* mVehicle;
        QList<POI*> mStops;

        // Tag readers
        void allocate();
        void readVehicleInformation();
        Vehicle* readVehicle();
        QList<POI*> readStops();
        POI* readStop();
        Station* readStation();
        QDateTime readDatetime();
    };
}

#endif // STOPREADER_H
