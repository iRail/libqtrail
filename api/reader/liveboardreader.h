//
// Configuration
//

// Include guard
#ifndef LIVEBOARDREADER_H
#define LIVEBOARDREADER_H

// Includes
#include "api/reader.h"
#include "api/liveboard.h"
#include <QList>
#include <QDateTime>

namespace iRail
{
    class LiveboardReader : public Reader
    {
    Q_OBJECT
    public:
        LiveboardReader();
        void readDocument();
        LiveboardPointer* liveboard();
    private:
        // Member data
        LiveboardPointer* mLiveboard;
        QDateTime mTimestamp;
        double mVersion;

        // Tag readers
        void allocate();
        Liveboard* readLiveboard();
        QString readStation();
        Liveboard::Departure readDeparture();
        QString readVehicle();
        QDateTime readDatetime();
        double readDelay();
        int readPlatform();
    };
}

#endif // STATIONREADER_H
