//
// Configuration
//

// Include guard
#ifndef CONNECTIONREADER_H
#define CONNECTIONREADER_H

// Includes
#include "api/reader.h"
#include "api/connection.h"
#include <QList>
#include <QDateTime>

namespace iRail
{
    class ConnectionReader : public Reader
    {
    Q_OBJECT
    public:
        void readDocument();
        QList<ConnectionPointer> getConnections();
    private:
        // Member data
        QList<ConnectionPointer> mConnections;
        QDateTime mTimestamp;
        double mVersion;

        // Tag readers
        void readConnections();
        Connection* readConnection();
        Connection::POI readPOI(Connection::POIType);
        QString readVehicle();
        int readPlatform();
        QDateTime readDatetime();
        QString readStation();
        QList<Connection::Transfer> readVias();
        Connection::Transfer readVia();

        // Auxiliary
        void reset();
    };
}

#endif // CONNECTIONREADER_H
