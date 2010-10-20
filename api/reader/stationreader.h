//
// Configuration
//

// Include guard
#ifndef STATIONREADER_H
#define STATIONREADER_H

// Includes
#include "api/reader.h"
#include "api/station.h"
#include <QList>
#include <QDateTime>

namespace iRail
{
    class StationReader : public Reader
    {
    Q_OBJECT
    public:
        void readDocument();
        QList<StationPointer> getStations();
    private:
        // Member data
        QList<StationPointer> mStations;
        QDateTime mTimestamp;

        // Tag readers
        void readStations();
        Station* readStation();

        // Auxiliary
        void reset();
    };
}

#endif // STATIONREADER_H
