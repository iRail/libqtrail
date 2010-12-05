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

Station::Station(QString iId) : mId(iId)
{
    qRegisterMetaType<StationPointer>("StationPointer");
    qRegisterMetaTypeStreamOperators<StationPointer>("StationPointer");
    mName = "";
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

QString Station::id() const
{
    return mId;
}

QString Station::name() const
{
    return mName;
}

void Station::setName(const QString &iName)
{
    mName = iName;
}

bool Station::locatable() const
{
    return mLocatable;
}

const Station::Location* Station::location() const
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
// Operators
//

QDebug &iRail::operator<<(QDebug dbg, const Station& iStation)
{
    dbg << "Station(id=" << iStation.id() << ",name='" << iStation.name() << "'";
    if (iStation.locatable())
        dbg << ", location='" << iStation.location()->first << " x " << iStation.location()->second << "'";
    dbg << ")";

    return dbg.maybeSpace();
}

QDataStream& iRail::operator<<(QDataStream& iStream, const Station& iStation)
{
    iStream << iStation.mId;
    iStream << iStation.mName;
    iStream << iStation.mLocatable;
    if (iStation.locatable())
        iStream << *iStation.mLocation;

    return iStream;
}

QDataStream& iRail::operator>>(QDataStream& iStream, Station& iStation)
{
    iStream >> iStation.mId;
    iStream >> iStation.mName;
    iStream >> iStation.mLocatable;
    if (iStation.locatable())
    {
        iStation.mLocation = new Station::Location();
        iStream >> *iStation.mLocation;
    }

    return iStream;
}

QDataStream &iRail::operator<<(QDataStream& iStream, const StationPointer& iStation)
{
    iStream << (*iStation);

    return iStream;
}

QDataStream &iRail::operator>>(QDataStream& iStream, StationPointer& iStation)
{
    Station *tStation = new Station("dummy");
    iStream >> *tStation;
    iStation = StationPointer(tStation);

    return iStream;
}
