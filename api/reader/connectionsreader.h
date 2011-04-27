//
// Configuration
//

// Include guard
#ifndef CONNECTIONSREADER_H
#define CONNECTIONSREADER_H

// Includes
#include <QList>
#include <QDateTime>
#include "api/reader.h"
#include "api/data/journey.h"
#include "api/data/stop.h"
#include "api/data/connection.h"
#include "api/data/vehicle.h"
#include "api/data/station.h"

namespace iRail
{
    class ConnectionsReader : public Reader
    {
    Q_OBJECT
    public:
        // Construction and destruction
        ConnectionsReader();

        // Reader interface
        void readDocument();

        // Basic I/O
        double version() const;
        QDateTime timestamp() const;
        QList<Journey*> journeys() const;
    private:
        // Member data
        double mVersion;
        QDateTime mTimestamp;
        QList<Journey*> mJourneys;

        // Tag readers
        void allocate();
        QList<Journey*> readConnections();
        Journey* readConnection();
        Stop* readStop(Vehicle*& iVehicle, Station*& iDirection);
        Vehicle* readVehicle();
        int readPlatform();
        QDateTime readDatetime();
        Station* readStation();
        QList<Connection*> readVias(QList<Vehicle*>& iVehicles, QList<Station*>& iDirections);
        Connection* readVia(Vehicle*& iVehicle, Station*& iDirection);
    };
}

#endif // CONNECTIONSREADER_H
