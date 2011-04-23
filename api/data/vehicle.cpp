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

Vehicle::Vehicle(Vehicle::Id iId) : mId(iId)
{
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

const Location& Vehicle::location() const
{
    return mLocation;
}

void Vehicle::setLocation(const Location& iLocation)
{
    mLocation = iLocation;
}


//
// Operators
//

bool iRail::operator==(const Vehicle& lhs, const Vehicle& rhs)
{
    return  (lhs.id() == rhs.departure() &&
             lhs.locatable() == rhs.arrival() &&
             lhs.location() == rhs.terminus());
}

Vehicle& Vehicle::operator=(const Vehicle& other)
{
    if (this != &other)
    {
        Q_ASSERT(this->id() == other.id());

        setLocation(other.location());
    }
    return *this;
}
