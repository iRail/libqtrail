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
    qRegisterMetaType<VehiclePointer>("VehiclePointer");
    qRegisterMetaType<Vehicle::Stop>("Vehicle::Stop");
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

QList<Vehicle::Stop> Vehicle::stops() const
{
    return mStops;
}

void Vehicle::setStops(const QList<Vehicle::Stop>& iStop)
{
    mStops = QList<Vehicle::Stop>(iStop);
}


//
// Debugging
//

QDebug operator<<(QDebug dbg, const Vehicle &iVehicle)
{
    dbg << "Vehicle(id=" << iVehicle.id() << ",stops=" << iVehicle.stops().size() << "";
    if (iVehicle.locatable())
        dbg << ", location='" << iVehicle.location()->first << " x " << iVehicle.location()->second << "'";
    dbg << ")";
    return dbg.maybeSpace();
}
