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
#include <QHash>
#include <QAbstractListModel>
#include "api/exception.h"
#include "api/data/vehicle.h"
#include "api/container.h"

namespace iRail
{
    class VehicleList : public QAbstractListModel
    {
    Q_OBJECT
    public:
        // Construction and destruction
        VehicleList(QObject* iParent = 0);
        ~VehicleList();

        // Model interface pass-through
        int rowCount(const QModelIndex& iParent = QModelIndex()) const
        { return mContainer.rowCount(iParent); }
        QVariant data(const QModelIndex& iIndex, int iRole = Qt::DisplayRole) const
        { return mContainer.data(iIndex, iRole); }
        QModelIndex indexFromItem(const Vehicle* iData) const
        { return mContainer.indexFromItem(iData); }

    public:
        // Basic I/O

    private:
        // Member data
        Container<Vehicle> mContainer;
        QDateTime mTimestamp;
    };
}

#endif // VEHICLELIST_H
