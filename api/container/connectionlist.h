//
// Configuration
//

// Include guard
#ifndef CONNECTIONLIST_H
#define CONNECTIONLIST_H

// Includes
#include <QObject>
#include <QMetaType>
#include <QSharedPointer>
#include <QString>
#include <QDateTime>
#include <QAbstractListModel>
#include "api/exception.h"
#include "api/data/connection.h"
#include "api/data/journey.h"

namespace iRail
{
    class ConnectionList : public QAbstractListModel
    {
    Q_OBJECT
    public:
        // Construction and destruction
        ConnectionList(const Journey& iJourney, QObject* iParent = 0);
        ~ConnectionList();

        // Basic I/O
        const Journey& journey() const;

        // Model interface
        int rowCount(const QModelIndex& iParent = QModelIndex()) const;
        QVariant data(const QModelIndex& iIndex, int iRole = Qt::DisplayRole) const;

        // Operators
        friend QDataStream &operator<<(QDataStream& iStream, const ConnectionList& iVehicleList);
        friend QDataStream &operator>>(QDataStream& iStream, ConnectionList& iVehicleList);

    private:
        Q_DISABLE_COPY(VehicleList);

        // Member data
        QDateTime mTimestamp;
        const Journey& mJourney;
        QList<Connection*> mConnections;
    };

    typedef QSharedPointer<ConnectionList> ConnectionListPointer;

    QDataStream &operator<<(QDataStream& iStream, const ConnectionList& iVehicleList);
    QDataStream &operator>>(QDataStream& iStream, ConnectionList& iVehicleList);
}

Q_DECLARE_METATYPE(iRail::ConnectionList)
Q_DECLARE_METATYPE(iRail::ConnectionListPointer)

#endif // CONNECTIONLIST_H
