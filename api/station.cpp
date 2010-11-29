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

QDebug Station::operator<<(QDebug dbg) const
{
    dbg << "Station(id=" << id() << ",name='" << name() << "'";
    if (locatable())
        dbg << ", location='" << location()->first << " x " << location()->second << "'";
    dbg << ")";

    return dbg.maybeSpace();
}

QDataStream& Station::operator<<(QDataStream& iStream) const
{
    iStream << mId;
    iStream << mName;
    iStream << mLocatable;
    if (locatable())
        iStream << *mLocation;

    return iStream;
}

QDataStream& Station::operator>>(QDataStream& iStream)
{
    iStream >> mId;
    iStream >> mName;
    iStream >> mLocatable;
    if (locatable())
    {
        mLocation = new Location();
        iStream >> *mLocation;
    }

    return iStream;
}
