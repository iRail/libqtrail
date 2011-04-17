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
        QList<ConnectionPointer>* connections(QDateTime& oTimestamp);
    private:
        // Member data
        QList<ConnectionPointer>* mConnections;
        QDateTime mTimestamp;
        double mVersion;

        // Tag readers
        void allocate();
        void readConnections();
        Connection* readConnection();
        Connection::POI readPOI(QString& iVehicle, QString& iDirection);
        QString readVehicle();
        int readPlatform();
        QDateTime readDatetime();
        QString readStation();
        QList<Connection::Line> readVias(QList<QString>& iVehicles, QList<QString>& iDirections);
        Connection::Line readVia(QString& iVehicle, QString& iDirection);
    };
}

#endif // CONNECTIONREADER_H
