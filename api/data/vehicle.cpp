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

    mLocatable = false;
    mLocation = 0;
}


Vehicle::~Vehicle()
{
    if (mLocatable)
        delete mLocation;
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

const Vehicle::Location* Vehicle::location() const
{
    return mLocation;
}

void Vehicle::setLocation(const Location& iLocation)
{
    if (mLocatable)
        delete mLocation;
    else
        mLocatable = true;
    mLocation = new Location(iLocation);
}


//
// Operators
//

QDataStream& iRail::operator<<(QDataStream& iStream, const Vehicle& iVehicle)
{
    iStream << iVehicle.mId;

    iStream << iVehicle.mLocatable;
    if (iVehicle.locatable())
        iStream << *iVehicle.mLocation;

    return iStream;
}

QDataStream& iRail::operator>>(QDataStream& iStream, Vehicle& iVehicle)
{
    iStream >> iVehicle.mId;

    iStream >> iVehicle.mLocatable;
    if (iVehicle.locatable())
        iStream << *iVehicle.mLocation;

    return iStream;
}
