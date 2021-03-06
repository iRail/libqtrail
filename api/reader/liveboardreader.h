//
// Configuration
//

// Include guard
#ifndef LIVEBOARDREADER_H
#define LIVEBOARDREADER_H

// Includes
#include <QHash>
#include <QDateTime>
#include "api/reader.h"
#include "api/data/departure.h"
#include "api/data/station.h"

namespace iRail
{
    class LiveboardReader : public Reader
    {
    Q_OBJECT
    public:
        // Construction and destruction
        LiveboardReader();

        // Reader interface
        void readDocument();

        // Basic I/O
        double version() const;
        QDateTime timestamp() const;
        Station const* station() const;
        QList<Departure*> departures() const;
    private:
        // Member data
        double mVersion;
        QDateTime mTimestamp;
        Station const* mStation;
        QList<Departure*> mDepartures;

        // Tag readers
        void readLiveboard();
        Station const* readStation();
        QList<Departure*> readDepartures();
        Departure* readDeparture();
        Vehicle const* readVehicle();
        QDateTime readDatetime();
        double readDelay();
        QString readPlatform();
    };
}

#endif // LIVEBOARDREADER_H
