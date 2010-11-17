//
// Configuration
//

// Include guard
#ifndef STATIONREADER_H
#define STATIONREADER_H

// Includes
#include "api/reader.h"
#include "api/station.h"
#include <QMap>
#include <QDateTime>

namespace iRail
{
    class StationReader : public Reader
    {
    Q_OBJECT
    public:
        StationReader();
        void readDocument();
        QMap<QString, StationPointer>* stations();
    private:
        // Member data
        QMap<QString, StationPointer>* mStations;
        QDateTime mTimestamp;
        double mVersion;

        // Tag readers
        void allocate();
        void readStations();
        Station* readStation();
    };
}

#endif // STATIONREADER_H
