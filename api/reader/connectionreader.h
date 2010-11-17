//
// Configuration
//

// Include guard
#ifndef CONNECTIONREADER_H
#define CONNECTIONREADER_H

// Includes
#include "api/reader.h"
#include "api/connection.h"
#include "api/station.h"
#include <QList>
#include <QDateTime>

namespace iRail
{
    class ConnectionReader : public Reader
    {
    Q_OBJECT
    public:
        ConnectionReader(const QList<StationPointer>* iStations);
        void readDocument();
        QList<ConnectionPointer>* connections();
    private:
        // Member data
        const QList<StationPointer>* mStations;
        QList<ConnectionPointer>* mConnections;
        QDateTime mTimestamp;
        double mVersion;

        // Tag readers
        void allocate();
        void readConnections();
        Connection* readConnection();
        Connection::POI readPOI(QString& iVehicle);
        QString readVehicle();
        int readPlatform();
        QDateTime readDatetime();
        StationPointer readStation();
        QList<Connection::Line> readVias(QList<QString>& iVehicles);
        Connection::Line readVia(QString& iVehicle);
    };
}

#endif // CONNECTIONREADER_H
