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

Station::Station(Station::Id iId) : mId(iId), mLocation(Location())
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

Station::Id Station::id() const
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

Location const* Station::location() const
{
    return mLocation;
}

void Station::setLocation(Location const* iLocation)
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
             *(lhs.location()) == *(rhs.location()));
}

iRail::Station& iRail::operator=(const Station& other)
{
    if (this != &other)
    {
        Q_ASSERT(this->id() == other.id());

        setName(other.name());
        setLocation(other.location());
    }
    return *this;
}

QDataStream& iRail::operator<<(QDataStream& iStream, const Station& iStation)
{
    iStream << iStation.mId;
    iStream << iStation.mName;
    iStream << *(iStation.mLocation);

    return iStream;
}

QDataStream& iRail::operator>>(QDataStream& iStream, Station& iStation)
{
    iStream >> iStation.mId;
    iStream >> iStation.mName;

    Location* tLocation = new Location();
    iStream << *tLocation;
    iStation.mLocation = tLocation;

    return iStream;
}

inline unsigned int iRail::qHash(const Station &iStation)
{
    return qHash(iStation.id());
}
