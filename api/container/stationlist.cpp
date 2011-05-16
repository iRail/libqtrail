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

StationList::StationList(QObject* iParent) : QAbstractListModel(iParent), mContainer(this)
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
