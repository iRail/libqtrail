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
    qRegisterMetaType<Station>("Station");

    mName = "";
}


Station::~Station()
{
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

const Location Station::location() const
{
    return mLocation;
}

void Station::setLocation(const Location& iLocation)
{
    mLocation = iLocation;
}


//
// Operators
//

bool iRail::operator==(const Station& lhs, const Station& rhs)
{
    return  (lhs.id() == rhs.id() &&
             lhs.name() == rhs.name() &&
             lhs.locatable() == rhs.locatable() &&
             lhs.location() == rhs.location());
}

bool iRail::operator||(const Station& lhs, const Station& rhs)
{
    return  (lhs.id() == rhs.id());
}

QDataStream& iRail::operator<<(QDataStream& iStream, const Station& iStation)
{
    iStream << iStation.mId;
    iStream << iStation.mName;
    iStream << iStation.mLocation;

    return iStream;
}

QDataStream& iRail::operator>>(QDataStream& iStream, Station& iStation)
{
    iStream >> iStation.mId;
    iStream >> iStation.mName;
    iStream >> iStation.mLocation;

    return iStream;
}

