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
        QList<Station*> stations() const;
    private:
        // Member data
        double mVersion;
        QDateTime mTimestamp;
        QList<Station*> mStations;

        // Tag readers
        QList<Station*> readStations();
        Station* readStation();
    };
}

#endif // STATIONSREADER_H
