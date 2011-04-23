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
#include <QHash>
#include "api/exception.h"
#include "api/data/connection.h"
#include "api/data/journey.h"
#include "api/containercache.h"

namespace iRail
{
    class ConnectionList : public QAbstractListModel
    {
    Q_OBJECT
    public:
        // Construction and destruction
        ConnectionList(const Journey::Id& iJourney, QObject* iParent = 0);
        ~ConnectionList();

        // Basic I/O
        const Journey::Id& journeyId() const;

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
        Journey::Id mJourneyId;
        QHash<Connection::Id, Connection*> mConnections;
    };

    typedef QSharedPointer<ConnectionList> ConnectionListPointer;
}

Q_DECLARE_METATYPE(iRail::ConnectionList)
Q_DECLARE_METATYPE(iRail::ConnectionListPointer)

#endif // CONNECTIONLIST_H
