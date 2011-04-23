//
// Configuration
//

// Includes
#include "departure.h"
#include <QString>

// Namespaces
using namespace iRail;


//
// Construction and destruction
//

Departure::Departure(Id iId) : mId(iId)
{
    qRegisterMetaType<Departure>("Departure");
    qRegisterMetaType<Departure::Id>("Departure::Id");
}


//
// Basic I/O
//

Departure::Id id() const
{
    return mId;
}


//
// Operators
//

bool iRail::operator==(const Departure& lhs, const Departure& rhs)
{
    return  (lhs.vehicle() == rhs.vehicle() &&
             lhs.Stop() == rhs.Stop());
}

bool iRail::operator||(const Departure& lhs, const Departure& rhs)
{
    return  (lhs.vehicle() || rhs.vehicle() &&
             lhs.Stop() || rhs.Stop());
}

QDataStream& iRail::operator<<(QDataStream& iStream, const Departure& iDeparture)
{
    iStream << iDeparture.mVehicle;
    iStream << iDeparture.mStop;

    return iStream;
}
QDataStream& iRail::operator>>(QDataStream& iStream, Departure& iDeparture)
{    
    Vehicle* tVehicle = new Vehicle("dummy");
    iStream >> tVehicle;
    iDeparture.mVehicle = tVehicle;

    Stop* tStop = new Stop(new Station("dummy"), QDateTime());
    iStream >> tDeparture;
    iConnection.mStop = tStop;

    return iStream;
}
