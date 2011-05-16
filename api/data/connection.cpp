//
// Configuration
//

// Includes
#include "connection.h"
#include <QString>

// Namespaces
using namespace iRail;


//
// Construction and destruction
//

Connection::Connection(Id iId) : mId(iId)
{
    mTerminus = 0;
    mVehicle = 0;
    mDelay = 0;
}


//
// Basic I/O
//

QVariant Connection::field(int iRole) const
{
    switch (iRole)
    {
    case Qt::DisplayRole:
    case Connection::VehicleRole:
        return QVariant::fromValue(vehicle());
    case Connection::OriginRole:
        return QVariant::fromValue(id()->origin);
    case Connection::DestinationRole:
        return QVariant::fromValue(id()->destination);
    case Connection::TerminusRole:
        return QVariant::fromValue(terminus());
    case Connection::DelayRole:
        return QVariant::fromValue(delay());
    default:
        return QVariant();
    }
}

Connection::Id const* Connection::id() const
{
    return &mId;
}

Station const* Connection::terminus() const
{
    return mTerminus;
}

void Connection::setTerminus(Station const* iTerminus)
{
    mTerminus = iTerminus;
}

Vehicle const* Connection::vehicle() const
{
    return mVehicle;
}

void Connection::setVehicle(Vehicle const* iVehicle)
{
    mVehicle = iVehicle;
}

unsigned int Connection::delay() const
{
    return mDelay;
}

void Connection::setDelay(unsigned int iDelay)
{
    mDelay = iDelay;
}


//
// Operators
//

bool iRail::operator==(const Connection& lhs, const Connection& rhs)
{
    return  (*lhs.id() == *rhs.id() &&
             *lhs.terminus() == *rhs.terminus() &&
             *lhs.vehicle() == *rhs.vehicle() &&
             lhs.delay() == rhs.delay());
}

Connection& Connection::operator=(const Connection& other)
{
    if (this != &other)
    {
        Q_ASSERT(this->id() == other.id());

        setTerminus(other.terminus());
        setVehicle(other.vehicle());
        setDelay(other.delay());
    }
    return *this;
}

bool iRail::operator==(const Connection::Id& lhs, const Connection::Id& rhs)
{
    return  (*lhs.origin->id() == *rhs.origin->id() &&
             *lhs.destination->id() == *rhs.destination->id());
}
