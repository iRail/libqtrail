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
// Operator implementation
//

bool Vehicle::equals(const Data& data) const
{
    const Vehicle& other = dynamic_cast<const Vehicle&>(data);
    return  (id() == other.id() &&
             location() == other.location());
}

Data& Vehicle::assign(const Data& data)
{
    const Vehicle& other = dynamic_cast<const Vehicle&>(data);
    if (this != &other)
    {
        Q_ASSERT(this->id() == other.id());

        setLocation(*other.location());
    }
    return *this;
}

unsigned int Vehicle::Id::hash() const
{
    return qHash(guid);
}

bool Vehicle::Id::equals(const AbstractId& data) const
{
    const Vehicle::Id& other = dynamic_cast<const Vehicle::Id&>(data);
    return  (guid == other.guid);
}
