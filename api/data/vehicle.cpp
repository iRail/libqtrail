//
// Configuration
//

// Includes
#include "vehicle.h"
#include <QString>

// Namespaces
using namespace iRail;


//
// Construction and destruction
//

Vehicle::Vehicle(Vehicle::Id iId) : mId(iId), mLocation(Location())
{
    qRegisterMetaType<Vehicle>("Vehicle");
    qRegisterMetaType<Vehicle::Id>("Vehicle::Id");
}


Vehicle::~Vehicle()
{
}


//
// Basic I/O
//

Vehicle::Id Vehicle::id() const
{
    return mId;
}

bool Vehicle::locatable() const
{
    return mLocatable;
}

Location const* Vehicle::location() const
{
    return mLocation;
}

void Vehicle::setLocation(Location const* iLocation)
{
    mLocation = iLocation;
}


//
// Operators
//

bool iRail::operator==(const Connection& lhs, const Connection& rhs)
{
    return  (lhs.id() == rhs.departure() &&
             lhs.locatable() == rhs.arrival() &&
             lhs.location() == rhs.terminus());
}
