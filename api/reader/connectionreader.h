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
        ConnectionReader();
        void readDocument();
        QList<ConnectionPointer>* connections();
    private:
        // Member data
        QList<ConnectionPointer>* mConnections;
        QDateTime mTimestamp;
        double mVersion;

        // Tag readers
        void allocate();
        void readConnections();
        Connection* readConnection();
        Connection::POI readPOI(Connection::POIType);
        QString readVehicle();
        int readPlatform();
        QDateTime readDatetime();
        QString readStation();
        QList<Connection::Transfer> readVias();
        Connection::Transfer readVia();
    };
}

#endif // CONNECTIONREADER_H
