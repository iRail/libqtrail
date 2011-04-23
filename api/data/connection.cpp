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

Connection::Connection(IId iId) : mId(iId)
{
    mTerminus = 0;
    mVehicle = 0;
    mDelay = 0;
}


//
// Basic I/O
//

Connection::IId& Connection::id() const
{
    return mId;
}

Station Connection::terminus() const
{
    return mTerminus;
}

void Connection::setTerminus(const Station& iTerminus)
{
    mTerminus = iTerminus;
}

Vehicle Connection::vehicle() const
{
    return mVehicle;
}

void Connection::setVehicle(const Vehicl& iVehicle)
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
    return  (departure() == other.departure() &&
             arrival() == other.arrival() &&
             terminus() == other.terminus() &&
             vehicle() == other.vehicle());
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

unsigned int Connection::IId::hash() const
{
    return (3*qHash(origin)) ^ (5*qHash(destination));
}

bool Connection::IId::equals(const Data::Id& data) const
{
    const Connection::IId& other = dynamic_cast<const Connection::IId&>(data);
    return  (origin->id() == other.origin->id() &&
             destination->id() == other.destination->id());
}
