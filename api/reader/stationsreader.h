//
// Configuration
//

// Include guard
#ifndef STATIONSREADER_H
#define STATIONSREADER_H

// Includes
#include <QHash>
#include <QDateTime>
#include "api/reader.h"
#include "api/data/station.h"

namespace iRail
{
    class StationsReader : public Reader
    {
    Q_OBJECT
    public:
        // Construction and destruction
        StationsReader();

        // Reader interface
        void readDocument();

        // Basic I/O
        double version() const;
        QDateTime timestamp() const;
        QHash<Station::Id, Station*> stations() const;
    private:
        // Member data
        double mVersion;
        QDateTime mTimestamp;
        QHash<Station::Id, Station*> mStations;

        // Tag readers
        void allocate();
        QHash<Station::Id, Station*> readStations();
        Station* readStation();
    };
}

#endif // STATIONSREADER_H
