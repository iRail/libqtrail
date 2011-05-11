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

Station::Station(Id iId) : mId(iId)
{
    mName = "";
}


Station::~Station()
{
}


//
// Basic I/O
//

QVariant Station::field(int iRole) const
{
    switch (iRole)
    {
    case Station::GUIDRole:
        return QVariant::fromValue(id()->guid);
    case Qt::DisplayRole:
    case Station::NameRole:
        return QVariant::fromValue(name());
    case Station::LocationRole:
        return QVariant::fromValue(location());
    default:
        return QVariant();
    }
}

Station::Id const* Station::id() const
{
    return &mId;
}

QString Station::name() const
{
    return mName;
}

void Station::setName(const QString &iName)
{
    mName = iName;
}

Location const* Station::location() const
{
    return &mLocation;
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
             location() == other.location());
}

Data& Station::assign(const Data& data)
{
    const Station& other = dynamic_cast<const Station&>(data);
    if (this != &other)
    {
        Q_ASSERT(this->id() == other.id());

        setName(other.name());
        setLocation(*other.location());
    }
    return *this;
}

unsigned int Station::Id::hash() const
{
    return qHash(guid);
}

bool Station::Id::equals(const AbstractId& data) const
{
    const Station::Id& other = dynamic_cast<const Station::Id&>(data);
    return  (guid == other.guid);
}


//
// Operators
//

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

QDataStream& operator<<(QDataStream& iStream, const Station::Id& iStationId)
{
    iStream << iStationId.guid;

    return iStream;
}

QDataStream& operator>>(QDataStream& iStream, Station::Id& iStationId)
{
    iStream >> iStationId.guid;

    return iStream;
}

