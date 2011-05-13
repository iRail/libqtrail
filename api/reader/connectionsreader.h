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

        // Temporary data
        struct ConnectionData
        {
            ConnectionData()
            {
                delay = 0;
                finished = false;
            }

            Stop const* origin;
            Stop const* destination;
            Station const* terminus;
            Vehicle const* vehicle;
            uint delay;
            bool finished;
        };

        // Tag readers
        void allocate();
        QList<Journey*> readConnections();
        Journey* readConnection();
        void readStopFields(uint& oDelay, Station*& oStation, QDateTime& oDatetime, Vehicle*& oVehicle, uint& oPlatform, Station*& oTerminus);
        void readConnectionOrigin(QList<ConnectionData>& iConnectionData);
        void readConnectionDestination(QList<ConnectionData>& iConnectionData);
        void readVias(QList<ConnectionData>& iConnectionData);
        void readVia(Stop*& oViaArrival, Stop*& oViaDeparture, Station*& oTerminus, Vehicle*& oVehicle);
        Vehicle* readVehicle();
        int readPlatform();
        QDateTime readDatetime();
        Station* readStation();
    };
}

#endif // CONNECTIONSREADER_H
