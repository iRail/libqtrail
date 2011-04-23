//
// Configuration
//

// Include guard
#ifndef VEHICLELIST_H
#define VEHICLELIST_H

// Includes
#include <QObject>
#include <QMetaType>
#include <QString>
#include <QDateTime>
#include <QAbstractListModel>
#include <QHash>
#include "api/exception.h"
#include "api/data/vehicle.h"

namespace iRail
{
    class ContainerCache;

    class VehicleList : public QAbstractListModel
    {
    Q_OBJECT
    private:
        // Construction and destruction
        VehicleList(QObject* iParent = 0);
        ~VehicleList();
        friend class ContainerCache;

    public:
        // Basic I/O

        // Model interface
        int rowCount(const QModelIndex& iParent = QModelIndex()) const;
        QVariant data(const QModelIndex& iIndex, int iRole = Qt::DisplayRole) const;

        // Operators
        friend QDataStream &operator<<(QDataStream& iStream, const VehicleList& iVehicleList);
        friend QDataStream &operator>>(QDataStream& iStream, VehicleList& iVehicleList);

    private:
        // Member data
        QDateTime mTimestamp;
        QHash<Vehicle::Id, Vehicle*> mVehicles;
    };
}

#endif // VEHICLELIST_H
