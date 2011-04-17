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

Connection::Connection(const POI& iDeparture, const POI& iArrival) : mDeparture(iDeparture, mArrival(iArrival)
{
    qRegisterMetaType<Departure>("Connection");
}


//
// Basic I/O
//

POI Connection::departure() const
{
    return mDeparture;
}

POI Connection::arrival() const
{
    return mArrival;
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

QDataStream &iRail::operator<<(QDataStream& iStream, const Connection& iConnection)
{
    iStream << iConnection.mDeparture;
    iStream << iConnection.mArrival;
    iStream << iConnection.mTerminus;
    iStream << iConnection.mVehicle;

    return iStream;
}
QDataStream &iRail::operator>>(QDataStream& iStream, Connection& iConnection)
{
    iStream >> iConnection.mDeparture;
    iStream >> iConnection.mArrival;
    iStream >> iConnection.mTerminus;
    iStream >> iConnection.mVehicle;

    return iStream;
}
