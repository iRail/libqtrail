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
    mLocation = 0;
}


Station::~Station()
{
    if (mLocation)
        delete mLocation;
}


//
// Basic I/O
//

QString Station::getName() const
{
    return mName;
}

bool Station::hasLocation() const
{
    return (mLocation != 0);
}

QPair<qreal, qreal> Station::getLocation() const
{
    return *mLocation;
}

void Station::setLocation(const Location& iLocation)
{
    if (mLocation)
        delete mLocation;
    mLocation = new Location(iLocation);
}


//
// Debugging
//

QDebug operator<<(QDebug dbg, const Station &iStation)
{
    dbg << "Station(name='" << iStation.getName() << "'";
    if (iStation.hasLocation())
        dbg << ", location='" << iStation.getLocation().first << " x " << iStation.getLocation().second << "'";
    dbg << ")";
    return dbg.maybeSpace();
}
