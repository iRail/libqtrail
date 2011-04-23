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
// Operator implementation
//

bool Vehicle::equals(const Data& data) const
{
    const Vehicle& other = dynamic_cast<const Vehicle&>(data);
    return  (id() == other.departure() &&
             locatable() == other.arrival() &&
             location() == other.terminus());
}

Data& Vehicle::assign(const Data& data)
{
    const Vehicle& other = dynamic_cast<const Vehicle&>(data);
    if (this != &other)
    {
        Q_ASSERT(this->id() == other.id());

        setLocation(other.location());
    }
    return *this;
}

unsigned int Vehicle::Id::hash()
{
    return qHash(guid);
}

bool Vehicle::Id::equals(const Data::Id& data) const
{
    const Vehicle::Id& other = dynamic_cast<const Vehicle::Id&>(data);
    return  (guid == other.guid);
}
