//
// Configuration
//

// Include guard
#ifndef DEPARTUREREADER_H
#define DEPARTUREREADER_H

// Includes
#include <QList>
#include <QDateTime>
#include "api/reader.h"
#include "api/data/departure.h"
#include "api/data/station.h"

namespace iRail
{
    class DepartureReader : public Reader
    {
    Q_OBJECT
    public:
        // Construction and destruction
        DepartureReader();

        // Reader interface
        void readDocument();

        // Basic I/O
        double version() const;
        QDateTime timestamp() const;
        Station station() const;
        QList<Departure> departures() const;
    private:
        // Member data
        double mVersion;
        QDateTime mTimestamp;
        Station mStation;
        QList<Departure> mDepartures;

        // Tag readers
        void allocate();
        void readLiveboard();
        QString readStation();
        QList<Departure> readDepartures();
        Departure readDeparture();
        QString readVehicle();
        QDateTime readDatetime();
        double readDelay();
        int readPlatform();
    };
}

#endif // DEPARTUREREADER_H