//
// Configuration
//

// Includes
#include "stationlist.h"
#include <QString>

// Namespaces
using namespace iRail;


//
// Construction and destruction
//

StationList::StationList(QObject* iParent) : QAbstractListModel(iParent)
{
    qRegisterMetaType<StationList>("StationList");

    QHash<int, QByteArray> tRoleNames;
    tRoleNames[Station::IdRole] = "id";
    tRoleNames[Station::NameRole] = "name";
    tRoleNames[Station::LocatableRole] = "locatable";
    tRoleNames[Station::LocationRole] = "location";
    setRoleNames(tRoleNames);
}


StationList::~Connection()
{
}


//
// Model interface
//

int StationList::rowCount(const QModelIndex& iParent) const
{
    return mStations.size();
}

QVariant StationList::data(const QModelIndex& iIndex, int iRole) const
{
    if (!iIndex.isValid())
        return QVariant();
    if (iIndex.row() > (mStations.size()-1) )
        return QVariant();

    Station* oStation = mStations.at(iIndex.row());
    switch (iRole)
    {
    case Station::IdRole:
        return QVariant::fromValue(oStation->id());
    case Qt::DisplayRole:
    case Station::NameRole:
        return QVariant::fromValue(oStation->name());
    case Station::LocatableRole:
        return QVariant::fromValue(oStation->locatable());
    case Station::LocationRole:
        return QVariant::fromValue(oStation->location());
    default:
        return QVariant();
    }
}


//
// Operators
//

QDataStream& iRail::operator<<(QDataStream& iStream, const StationList& iStationList)
{
    return iStream;
}

QDataStream& iRail::operator>>(QDataStream& iStream, StationList& iStationList)
{
    return iStream;
}
