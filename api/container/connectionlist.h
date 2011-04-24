//
// Configuration
//

// Include guard
#ifndef CONNECTIONLIST_H
#define CONNECTIONLIST_H

// Includes
#include <QObject>
#include <QMetaType>
#include <QString>
#include <QDateTime>
#include <QAbstractListModel>
#include <QHash>
#include "api/exception.h"
#include "api/data/connection.h"
#include "api/data/journey.h"

namespace iRail
{
    class ContainerCache;

    class ConnectionList : public QAbstractListModel
    {
    Q_OBJECT
    private:
        // Construction and destruction
        ConnectionList(const Journey::Id& iJourney, QObject* iParent = 0);
        ~ConnectionList();
        friend class ContainerCache;

        // Basic I/O
    public:
        const Journey::Id& journeyId() const;

        // Model interface
        int rowCount(const QModelIndex& iParent = QModelIndex()) const;
        QVariant data(const QModelIndex& iIndex, int iRole = Qt::DisplayRole) const;

        // Operators
        friend QDataStream &operator<<(QDataStream& iStream, const ConnectionList& iVehicleList);
        friend QDataStream &operator>>(QDataStream& iStream, ConnectionList& iVehicleList);

    private:
        // Member data
        QDateTime mTimestamp;
        Journey::Id mJourneyId;
        QHash<Connection::Id, Connection*> mConnections;
    };
}

#endif // CONNECTIONLIST_H
