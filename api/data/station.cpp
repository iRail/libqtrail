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

Station::Station(Station::Id iId) : mId(iId)
{
    qRegisterMetaType<Station>("Station::Id");

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

const Location& Station::location() const
{
    return mLocation;
}

void Station::setLocation(const Location& iLocation)
{
    mLocation = iLocation;
}


//
// Operator implementation
//

bool Station::equals(const Data& data) const
{
    const Station& other = dynamic_cast<const Station&>(data);
    return  (id() == other.id() &&
             name() == other.name() &&
             *(location()) == *(other.location()));
}

Data& Station::assign(const Data& data)
{
    const Station& other = dynamic_cast<const Station&>(data);
    if (this != &other)
    {
        Q_ASSERT(this->id() == other.id());

        setName(other.name());
        setLocation(other.location());
    }
    return *this;
}

unsigned int Station::Id::hash()
{
    return qHash(guid);
}

bool Station::Id::equals(const Data::Id& data) const
{
    const Station::Id& other = dynamic_cast<const Station::Id&>(data);
    return  (guid == other.guid);
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

