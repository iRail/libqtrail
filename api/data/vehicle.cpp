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

Vehicle::Vehicle(QString iId) : mId(iId)
{
    qRegisterMetaType<Vehicle>("Vehicle");
}


Vehicle::~Vehicle()
{
}


//
// Basic I/O
//

QString Vehicle::id() const
{
    return mId;
}

bool Vehicle::locatable() const
{
    return mLocatable;
}

const Location Vehicle::location() const
{
    return mLocation;
}

void Vehicle::setLocation(const Location& iLocation)
{
    mLocation = iLocation;
}


//
// Operators
//

bool iRail::operator==(const Connection& lhs, const Connection& rhs)
{
    return  (lhs.id() == rhs.departure() &&
             lhs.locatable() == rhs.arrival() &&
             lhs.location() == rhs.terminus());
}

bool iRail::operator||(const Connection& lhs, const Connection& rhs)
{
    return  (lhs.id() == rhs.departure());
}

QDataStream& iRail::operator<<(QDataStream& iStream, const Vehicle& iVehicle)
{
    iStream << iVehicle.mId;
    iStream << iVehicle.mLocation;

    return iStream;
}

QDataStream& iRail::operator>>(QDataStream& iStream, Vehicle& iVehicle)
{
    iStream >> iVehicle.mId;
    iStream << iVehicle.mLocation;

    return iStream;
}
