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
// Operators
//

QDebug Vehicle::operator<<(QDebug dbg) const
{
    dbg << "Vehicle(id=" << id() << ",stops=" << stops().size() << "";
    if (locatable())
        dbg << ", location='" << location()->first << " x " << location()->second << "'";
    dbg << ")";

    return dbg.maybeSpace();
}

QDataStream& Vehicle::operator<<(QDataStream& iStream) const
{
    iStream << mId;

    iStream << mLocatable;
    if (locatable())
        iStream << *mLocation;

    iStream << mStops.size();
    foreach (Stop tStop, mStops)
        tStop.operator <<(iStream);

    return iStream;
}

QDataStream& Vehicle::operator>>(QDataStream& iStream)
{
    iStream >> mId;

    iStream >> mLocatable;
    if (locatable())
        iStream << *mLocation;

    int tStops;
    iStream >> tStops;
    mStops = QList<Stop>();
    for (int i = 0; i < tStops; i++)
    {
        Stop tStop;
        tStop.operator >>(iStream);
        mStops << tStop;
    }

    return iStream;
}
