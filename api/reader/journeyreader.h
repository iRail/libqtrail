//
// Configuration
//

// Include guard
#ifndef JOURNEYREADER_H
#define JOURNEYREADER_H

// Includes
#include <QList>
#include <QDateTime>
#include "api/reader.h"
#include "api/data/journey.h"
#include "api/data/poi.h"
#include "api/data/connection.h"
#include "api/data/vehicle.h"
#include "api/data/station.h"

namespace iRail
{
    class JourneyReader : public Reader
    {
    Q_OBJECT
    public:
        // Construction and destruction
        JourneyReader();

        // Reader interface
        void readDocument();

        // Basic I/O
        double version() const;
        QDateTime timestamp() const;
        QList<Journey> journeys() const;
    private:
        // Member data
        double mVersion;
        QDateTime mTimestamp;
        QList<Journey> mJourneys;

        // Tag readers
        void allocate();
        void readConnections();
        Journey* readConnection();
        POI readPOI(QString& iVehicle, QString& iDirection);
        Vehicle readVehicle();
        int readPlatform();
        QDateTime readDatetime();
        Station readStation();
        QList<Connection> readVias(QList<QString>& iVehicles, QList<QString>& iDirections);
        Connection readVia(QString& iVehicle, QString& iDirection);
    };
}

#endif // JOURNEYREADER_H