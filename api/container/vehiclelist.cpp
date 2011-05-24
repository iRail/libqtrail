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

VehicleList::VehicleList(QObject* iParent) : Container(iParent)
{
    QHash<int, QByteArray> tRoleNames;
    tRoleNames[Station::GUIDRole] = "guid";
    tRoleNames[Station::LocationRole] = "location";
    setRoleNames(tRoleNames);
}

VehicleList::~VehicleList()
{
}


//
// Basic I/O
//

Vehicle const* VehicleList::get(const Vehicle::Id& iId)
{
    foreach (Vehicle* tVehicle, mData)
    {
        if (*tVehicle->id() == iId)
            return tVehicle;
    }
    return 0;
}
