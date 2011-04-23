//
// Configuration
//

// Includes
#include "vehiclelist.h"
#include <QString>

// Namespaces
using namespace iRail;


//
// Construction and destruction
//

VehicleList::VehicleList(QObject* iParent) : QAbstractListModel(iParent)
{
    qRegisterMetaType<VehicleList>("VehicleList");
    qRegisterMetaType<VehicleListPointer>("VehicleListPointer");

    QHash<int, QByteArray> tRoleNames;
    tRoleNames[Station::IdRole] = "id";
    tRoleNames[Station::LocationRole] = "location";
    setRoleNames(tRoleNames);
}


VehicleList::~VehicleList()
{
    qDeleteAll(mVehicles.values());
    mVehicles.clear();
}


//
// Model interface
//

int VehicleList::rowCount(const QModelIndex& iParent) const
{
    return mVehicles.size();
}

QVariant VehicleList::data(const QModelIndex& iIndex, int iRole) const
{
    if (!iIndex.isValid())
        return QVariant();
    if (iIndex.row() > (mVehicles.size()-1) )
        return QVariant();

    // TODO: sort through virtual mapping structure
    Vehicle* oVehicle = mVehicles.values().at(iIndex.row());
    switch (iRole)
    {
    case Qt::DisplayRole:
    case Vehicle::IdRole:
        return QVariant::fromValue(oVehicle->id());
    case Vehicle::LocationRole:
        return QVariant::fromValue(oVehicle->location());
    default:
        return QVariant();
    }
}
