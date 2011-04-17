//
// Configuration
//

// Include guard
#ifndef STATIONREADER_H
#define STATIONREADER_H

// Includes
#include <QList>
#include <QDateTime>
#include "api/reader.h"
#include "api/data/station.h"

namespace iRail
{
    class StationReader : public Reader
    {
    Q_OBJECT
    public:
        // Construction and destruction
        StationReader();

        // Reader interface
        void readDocument();

        // Basic I/O
        double version() const;
        QDateTime timestamp() const;
        QList<Station> stations() const;
    private:
        // Member data
        double mVersion;
        QDateTime mTimestamp;
        QList<Station> mStations;

        // Tag readers
        void allocate();
        void readStations();
        Station readStation();
    };
}

#endif // STATIONREADER_H
