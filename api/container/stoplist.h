//
// Configuration
//

// Include guard
#ifndef STOPLIST_H
#define STOPLIST_H

// Includes
#include <QObject>
#include <QMetaType>
#include <QString>
#include <QDateTime>
#include <QAbstractListModel>
#include <QHash>
#include "api/exception.h"
#include "api/data/vehicle.h"
#include "api/data/connection.h"
#include "api/data/stop.h"

namespace iRail
{
    class ContainerCache;

    class StopList : public QAbstractListModel
    {
    Q_OBJECT
    private:
        // Construction and destruction
        StopList(const Vehicle::Id& iVehicleId, QObject* iParent = 0);
        ~StopList();
        friend class ContainerCache;

        // Basic I/O
    public:
        Vehicle::Id vehicleId() const;

        // Model interface
        int rowCount(const QModelIndex& iParent = QModelIndex()) const;
        QVariant data(const QModelIndex& iIndex, int iRole = Qt::DisplayRole) const;

        // Operators
        friend QDataStream &operator<<(QDataStream& iStream, const StopList& iStopList);
        friend QDataStream &operator>>(QDataStream& iStream, StopList& iStopList);

    signals:
        // Data reply signals

        // Data processing methods
    private slots:

    private:
        // Member data
        Vehicle::Id mVehicleId;
        QHash<Stop::Id, Stop*> mStops;
    };
}

#endif // STOPLIST_H
