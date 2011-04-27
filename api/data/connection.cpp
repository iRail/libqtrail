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
// Operator implementation
//

bool Connection::equals(const Data& data) const
{
    const Connection& other = dynamic_cast<const Connection&>(data);
    return  (id() == other.id() &&
             terminus() == other.terminus() &&
             vehicle() == other.vehicle() &&
             delay() == other.delay());
}

Data& Connection::assign(const Data& data)
{
    const Connection& other = dynamic_cast<const Connection&>(data);
    if (this != &other)
    {
        Q_ASSERT(this->id() == other.id());

        setTerminus(other.terminus());
        setVehicle(other.vehicle());
        setDelay(other.delay());
    }
    return *this;
}

unsigned int Connection::Id::hash() const
{
    return (3*qHash(origin)) ^ (5*qHash(destination));
}

bool Connection::Id::equals(const AbstractId& data) const
{
    const Connection::Id& other = dynamic_cast<const Connection::Id&>(data);
    return  (origin->id() == other.origin->id() &&
             destination->id() == other.destination->id());
}
