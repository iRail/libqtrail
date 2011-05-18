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
    //mVehicleId->guid = new QString("anonymous");
    // TODO: this cannot happen... Do we need an "anonymous" stoplist?

    // TODO: remove duplicate code
    QHash<int, QByteArray> tRoleNames;
    tRoleNames[Stop::StationRole] = "station";
    tRoleNames[Stop::DatetimeRole] = "datetime";
    tRoleNames[Stop::PlatformRole] = "platform";
    setRoleNames(tRoleNames);
}

StopList::StopList(Vehicle::Id const* iVehicleId, QObject* iParent) : Container(iParent), mVehicleId(iVehicleId)
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
    return mVehicleId;
}
