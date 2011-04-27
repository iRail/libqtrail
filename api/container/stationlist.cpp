//
// Configuration
//

// Includes
#include "stationlist.h"
#include "api/reader/stationsreader.h"
#include <QString>

// Namespaces
using namespace iRail;


//
// Construction and destruction
//

StationList::StationList(QObject* iParent) : QAbstractListModel(iParent)
{
    QHash<int, QByteArray> tRoleNames;
    tRoleNames[Station::GUIDRole] = "guid";
    tRoleNames[Station::NameRole] = "name";
    tRoleNames[Station::LocationRole] = "location";
    setRoleNames(tRoleNames);
}

StationList::~StationList()
{
    qDeleteAll(mStations.values()); // TODO: neccesary?
}


//
// Model interface
//

int StationList::rowCount(const QModelIndex& iParent) const
{
    Q_UNUSED(iParent);
    return mStationIds.size();
}

QVariant StationList::data(const QModelIndex& iIndex, int iRole) const
{
    if (!iIndex.isValid())
        return QVariant();
    if (iIndex.row() > (mStationIds.size()-1) )
        return QVariant();

    Station::Id const* tStationId = mStationIds.at(iIndex.row());
    Station* oStation = mStations.value(tStationId);
    switch (iRole)
    {
    case Station::GUIDRole:
        return QVariant::fromValue(oStation->id()->guid);
    case Qt::DisplayRole:
    case Station::NameRole:
        return QVariant::fromValue(oStation->name());
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
    iStream << iStationList.mStations.size();
    foreach (Station* tStation, iStationList.mStations)
        iStream << *tStation;

    return iStream;
}

QDataStream& iRail::operator>>(QDataStream& iStream, StationList& iStationList)
{
    int tStationCount;
    iStream >> tStationCount;
    Q_ASSERT(iStationList.mStations.size() == 0);
    for (int i = 0; i < tStationCount; i++)
    {
        Station* tStation;
        iStream >> *tStation;
        iStationList.mStations.insert(tStation->id(), tStation);
    }

    return iStream;
}
