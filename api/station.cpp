//
// Configuration
//

// Includes
#include "station.h"
#include <QString>

// Namespaces
using namespace iRail;


//
// Construction and destruction
//

Station::Station(QString iName) : mName(iName)
{
    qRegisterMetaType<StationPointer>("StationPointer");
    mLocatable = false;
    mLocation = 0;
}


Station::~Station()
{
    if (mLocatable)
        delete mLocation;
}


//
// Basic I/O
//

QString Station::name() const
{
    return mName;
}

bool Station::locatable() const
{
    return mLocatable;
}

const Location* Station::location() const
{
    return mLocation;
}

void Station::setLocation(const Location& iLocation)
{
    if (mLocatable)
        delete mLocation;
    else
        mLocatable = true;
    mLocation = new Location(iLocation);
}


//
// Debugging
//

QDebug operator<<(QDebug dbg, const Station &iStation)
{
    dbg << "Station(name='" << iStation.name() << "'";
    if (iStation.locatable())
        dbg << ", location='" << iStation.location()->first << " x " << iStation.location()->second << "'";
    dbg << ")";
    return dbg.maybeSpace();
}
