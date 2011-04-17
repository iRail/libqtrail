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
    qRegisterMetaType<StationListPointer>("StationListPointer");

    QHash<int, QByteArray> tRoleNames;
    tRoleNames[Station::IdRole] = "id";
    tRoleNames[Station::NameRole] = "name";
    tRoleNames[Station::LocationRole] = "location";
    setRoleNames(tRoleNames);
}


StationList::~VehicleList()
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
        iJourneyList.mStations << tStation;
    }

    return iStream;
}
