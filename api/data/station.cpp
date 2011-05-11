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
// Operators
//

bool iRail::operator==(const Station& lhs, const Station& rhs)
{
    return  (lhs.id() == rhs.id() &&
             lhs.name() == rhs.name() &&
             *(lhs.location()) == *(rhs.location()));
}

Station& Station::operator=(const Station& other)
{
    if (this != &other)
    {
        Q_ASSERT(this->id() == other.id());

        setName(other.name());
        setLocation(*other.location());
    }
    return *this;
}

inline unsigned int qHash(const Station::Id& iStationId)
{
    return qHash(iStationId);
}

bool iRail::operator==(const Station::Id& lhs, const Station::Id& rhs)
{
    return  (lhs.guid == rhs.guid);
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

QDataStream& iRail::operator<<(QDataStream& iStream, const Station::Id& iStationId)
{
    iStream << iStationId.guid;

    return iStream;
}

QDataStream& iRail::operator>>(QDataStream& iStream, Station::Id& iStationId)
{
    iStream >> iStationId.guid;

    return iStream;
}
