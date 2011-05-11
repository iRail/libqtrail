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

Vehicle::Vehicle(Id iId) : mId(iId)
{
}


Vehicle::~Vehicle()
{
}


//
// Basic I/O
//

QVariant Vehicle::field(int iRole) const
{
    switch (iRole)
    {
    case Qt::DisplayRole:
    case Vehicle::GUIDRole:
        return QVariant::fromValue(id()->guid);
    case Vehicle::LocationRole:
        return QVariant::fromValue(location());
    default:
        return QVariant();
    }
}

Vehicle::Id const* Vehicle::id() const
{
    return &mId;
}

Location const* Vehicle::location() const
{
    return &mLocation;
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

        setLocation(*other.location());
    }
    return *this;
}

inline unsigned int qHash(const Vehicle::Id& iVehicleId)
{
    return qHash(iVehicleId);
}

bool iRail::operator==(const Vehicle::Id& lhs, const Vehicle::Id& rhs)
{
    return  (lhs.guid == rhs.guid);
}
