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
}


//
// Model interface
//

int VehicleList::rowCount(const QModelIndex& iParent) const
{
    return mStations.size();
}

QVariant VehicleList::data(const QModelIndex& iIndex, int iRole) const
{
    if (!iIndex.isValid())
        return QVariant();
    if (iIndex.row() > (mVehicles.size()-1) )
        return QVariant();

    Vehicle* oVehicle = mVehicles.at(iIndex.row());
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


//
// Operators
//

QDataStream& iRail::operator<<(QDataStream& iStream, const VehicleList& iVehicleList)
{
    iStream << iVehicleList.mVehicles.size();
    foreach (Vehicle* tVehicles, iVehicleList.mVehicles)
        iStream << *tVehicles;

    return iStream;
}

QDataStream& iRail::operator>>(QDataStream& iStream, VehicleList& iVehicleList)
{
    int tVehicleCount;
    iStream >> tVehicleCount;
    Q_ASSERT(iVehicleList.mVehicles.size() == 0);
    for (int i = 0; i < tVehicleCount; i++)
    {
        Vehicle* tVehicle;
        iStream >> *tVehicle;
        iVehicleList.mVehicles << tVehicle;
    }

    return iStream;
}
