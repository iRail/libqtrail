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

bool iRail::operator||(const Connection& lhs, const Connection& rhs)
{
    return  (lhs.departure() || rhs.departure() &&
             lhs.arrival() || rhs.arrival());
}

QDataStream& iRail::operator<<(QDataStream& iStream, const Connection& iConnection)
{
    iStream << iConnection.mDeparture;
    iStream << iConnection.mArrival;
    iStream << iConnection.mTerminus;
    iStream << iConnection.mVehicle;

    return iStream;
}
QDataStream& iRail::operator>>(QDataStream& iStream, Connection& iConnection)
{
    Stop* tDeparture = new Stop(new Station("dummy"), QDateTime());
    iStream >> tDeparture;
    iConnection.mDeparture = tDeparture;

    Stop* tArrival = new Stop(new Station("dummy"), QDateTime());
    iStream >> tDeparture;
    iConnection.mArrival = tArrival;

    Station* tTerminus = new Station("dummy");
    iStream >> tTerminus;
    iConnection.mTerminus = tTerminus;

    Vehicle* tVehicle = new Vehicle("dummy");
    iStream >> tVehicle;
    iConnection.mVehicle = tVehicle;

    return iStream;
}
