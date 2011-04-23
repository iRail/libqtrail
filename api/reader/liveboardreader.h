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
        Station station() const;
        QHash<Departure::Id, Departure*> departures() const;
    private:
        // Member data
        double mVersion;
        QDateTime mTimestamp;
        Station mStation;
        QHash<Departure::Id, Departure*> mDepartures;

        // Tag readers
        void allocate();
        void readLiveboard();
        QString readStation();
        QHash<Departure::Id, Departure*> readDepartures();
        Departure* readDeparture();
        QString readVehicle();
        QDateTime readDatetime();
        double readDelay();
        int readPlatform();
    };
}

#endif // LIVEBOARDREADER_H
