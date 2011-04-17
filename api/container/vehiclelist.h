//
// Configuration
//

// Include guard
#ifndef VEHICLELIST_H
#define VEHICLELIST_H

// Includes
#include <QObject>
#include <QMetaType>
#include <QSharedPointer>
#include <QString>
#include <QDateTime>
#include <QAbstractListModel>
#include "api/exception.h"
#include "api/data/vehicle.h"

namespace iRail
{
    class VehicleList : public QAbstractListModel
    {
    Q_OBJECT
    public:
        // Construction and destruction
        VehicleList(QObject* iParent = 0);
        ~VehicleList();

        // Model interface
        int rowCount(const QModelIndex& iParent = QModelIndex()) const;
        QVariant data(const QModelIndex& iIndex, int iRole = Qt::DisplayRole) const;

        // Operators
        friend QDataStream &operator<<(QDataStream& iStream, const VehicleList& iVehicleList);
        friend QDataStream &operator>>(QDataStream& iStream, VehicleList& iVehicleList);

    private:
        Q_DISABLE_COPY(VehicleList);

        // Member data
        QDateTime mTimestamp;
        QList<Vehicle*> mVehicles;
    };

    typedef QSharedPointer<VehicleList> VehicleListPointer;

    QDataStream &operator<<(QDataStream& iStream, const VehicleList& iVehicleList);
    QDataStream &operator>>(QDataStream& iStream, VehicleList& iVehicleList);
}

Q_DECLARE_METATYPE(iRail::VehicleList)
Q_DECLARE_METATYPE(iRail::VehicleListPointer)

#endif // VEHICLELIST_H
