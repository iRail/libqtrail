//
// Configuration
//

// Includes
#include "departurelist.h"
#include <QString>

// Namespaces
using namespace iRail;


//
// Construction and destruction
//

DepartureList::DepartureList(const Station& iStation, QObject* iParent) : mStation(iStation), QAbstractListModel(iParent)
{
    qRegisterMetaType<DepartureList>("DepartureList");

    QHash<int, QByteArray> tRoleNames;
    tRoleNames[Departure::VehicleRole] = "vehicle";
    tRoleNames[Departure::POIRole] = "poi";
    setRoleNames(tRoleNames);
}


//
// Basic I/O
//

Station DepartureList::station() const
{
    return mStation;
}


//
// Model interface
//

int DepartureList::rowCount(const QModelIndex& iParent) const
{
    return mDepartures.size();
}

QVariant DepartureList::data(const QModelIndex& iIndex, int iRole) const
{
    if (!iIndex.isValid())
        return QVariant();
    if (iIndex.row() > (mDepartures.size()-1) )
        return QVariant();

    Departure* oDeparture = mDepartures.at(iIndex.row());
    switch (iRole)
    {
    case Qt::DisplayRole:
    case Departure::VehicleRole:
        return QVariant::fromValue(oDeparture->vehicle());
    case Departure::POIRole:
        return QVariant::fromValue(oDeparture->poi());
    default:
        return QVariant();
    }
}


//
// Operators
//

QDataStream& iRail::operator<<(QDataStream& iStream, const DepartureList& iDepartureList)
{
    iStream << iDepartureList.mStation;

    iStream << iDepartureList.mDepartures.size();
    foreach (DepartureList::Departure tDeparture, iDepartureList.mDepartures)
        iStream << tDeparture;

    return iStream;
}

QDataStream& iRail::operator>>(QDataStream& iStream, DepartureList& iDepartureList)
{
    iStream >> iDepartureList.mStation;

    int tDepartures;
    iStream >> tDepartures;
    iDepartureList.mDepartures = QList<DepartureList::Departure>();
    for (int i = 0; i < tDepartures; i++)
    {
        DepartureList::Departure tDeparture;
        iStream >> tDeparture;
        iDepartureList.mDepartures << tDeparture;
    }

    return iStream;
}

