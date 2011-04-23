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
    qRegisterMetaType<Connection>("Connection");
    qRegisterMetaType<Connection>("Connection::Id");
}


//
// Basic I/O
//

Id Connection::id() const
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
// Operators
//

bool iRail::operator==(const Connection& lhs, const Connection& rhs)
{
    return  (lhs.departure() == rhs.departure() &&
             lhs.arrival() == rhs.arrival() &&
             lhs.terminus() == rhs.terminus() &&
             lhs.vehicle() == rhs.vehicle());
}

iRail::Connection& iRail::operator=(const Connection& other)
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

inline unsigned int qHash(const Connection::Id& iConnection)
{
    return (3*qHash(iConnection.origin)) ^ (5*qHash(iConnection.destination));
}

bool iRail::operator==(const Connection::Id& lhs, const Connection::Id& rhs)
{
    return  (lhs.origin->id() == rhs.origin->id() &&
             lhs.destination->id() == rhs.destination->id());
}
