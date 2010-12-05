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
    qRegisterMetaTypeStreamOperators<VehiclePointer>("VehiclePointer");
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
// Operators
//

QDebug &iRail::operator<<(QDebug dbg, const Vehicle& iVehicle)
{
    dbg << "Vehicle(id=" << iVehicle.id() << ",stops=" << iVehicle.stops().size() << "";
    if (iVehicle.locatable())
        dbg << ", location='" << iVehicle.location()->first << " x " << iVehicle.location()->second << "'";
    dbg << ")";

    return dbg.maybeSpace();
}

QDataStream& iRail::operator<<(QDataStream& iStream, const Vehicle& iVehicle)
{
    iStream << iVehicle.mId;

    iStream << iVehicle.mLocatable;
    if (iVehicle.locatable())
        iStream << *iVehicle.mLocation;

    iStream << iVehicle.mStops.size();
    foreach (Vehicle::Stop tStop, iVehicle.mStops)
        tStop.operator <<(iStream);

    return iStream;
}

QDataStream& iRail::operator>>(QDataStream& iStream, Vehicle& iVehicle)
{
    iStream >> iVehicle.mId;

    iStream >> iVehicle.mLocatable;
    if (iVehicle.locatable())
        iStream << *iVehicle.mLocation;

    int tStops;
    iStream >> tStops;
    iVehicle.mStops = QList<Vehicle::Stop>();
    for (int i = 0; i < tStops; i++)
    {
        Vehicle::Stop tStop;
        tStop.operator >>(iStream);
        iVehicle.mStops << tStop;
    }

    return iStream;
}

QDataStream &iRail::operator<<(QDataStream& iStream, const VehiclePointer &iVehicle)
{
    iStream << (*iVehicle);

    return iStream;
}

QDataStream &iRail::operator>>(QDataStream& iStream, VehiclePointer &iVehicle)
{
    Vehicle *tVehicle = new Vehicle("dummy");
    iStream >> *tVehicle;
    iVehicle = VehiclePointer(tVehicle);

    return iStream;
}
