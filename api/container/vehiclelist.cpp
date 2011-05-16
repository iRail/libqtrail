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

VehicleList::VehicleList(QObject* iParent) : QAbstractListModel(iParent), mContainer(this)
{
    QHash<int, QByteArray> tRoleNames;
    tRoleNames[Station::GUIDRole] = "guid";
    tRoleNames[Station::LocationRole] = "location";
    setRoleNames(tRoleNames);
}

VehicleList::~VehicleList()
{
}
