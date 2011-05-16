//
// Configuration
//

// Includes
#include "stoplist.h"
#include "api/reader/vehiclereader.h"
#include <QString>

// Namespaces
using namespace iRail;


//
// Construction and destruction
//

StopList::StopList(QObject *iParent) : Container(iParent)
{
    mVehicleId.guid = "anonymous";

    // TODO: remove duplicate code
    QHash<int, QByteArray> tRoleNames;
    tRoleNames[Stop::StationRole] = "station";
    tRoleNames[Stop::DatetimeRole] = "datetime";
    tRoleNames[Stop::PlatformRole] = "platform";
    setRoleNames(tRoleNames);
}

StopList::StopList(const Vehicle::Id& iVehicleId, QObject* iParent) : mVehicleId(iVehicleId), Container(iParent)
{
    QHash<int, QByteArray> tRoleNames;
    tRoleNames[Stop::StationRole] = "station";
    tRoleNames[Stop::DatetimeRole] = "datetime";
    tRoleNames[Stop::PlatformRole] = "platform";
    setRoleNames(tRoleNames);
}

StopList::~StopList()
{
}


//
// Basic I/O
//

Vehicle::Id const* StopList::vehicleId() const
{
    return &mVehicleId;
}
