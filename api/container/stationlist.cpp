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

StationList::StationList(QObject* iParent) : Container(iParent)
{
    QHash<int, QByteArray> tRoleNames;
    tRoleNames[Station::GUIDRole] = "guid";
    tRoleNames[Station::NameRole] = "name";
    tRoleNames[Station::LocationRole] = "location";
    setRoleNames(tRoleNames);
}

StationList::~StationList()
{
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
