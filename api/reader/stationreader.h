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
        StationReader();
        void readDocument();
        QList<StationPointer>* stations();
    private:
        // Member data
        QList<StationPointer>* mStations;
        QDateTime mTimestamp;

        // Tag readers
        void allocate();
        void readStations();
        Station* readStation();
    };
}

#endif // STATIONREADER_H
