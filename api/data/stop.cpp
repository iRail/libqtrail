//
// Configuration
//

// Includes
#include "stop.h"
#include <QString>

// Namespaces
using namespace iRail;


//
// Construction and destruction
//

Stop::Stop(Id iId) : mId(iId)
{
    mPlatform = 0;
}


Stop::~Stop()
{
}


//
// Basic I/O
//

QVariant Stop::field(int iRole) const
{
    switch (iRole)
    {
    case Qt::DisplayRole:
    case Stop::StationRole:
        return QVariant::fromValue(id()->station);
    case Stop::DatetimeRole:
        return QVariant::fromValue(id()->datetime);
    case Stop::PlatformRole:
        return QVariant::fromValue(platform());
    default:
        return QVariant();
    }
}

Stop::Id const* Stop::id() const
{
    return &mId;
}

unsigned int Stop::platform() const
{
    return mPlatform;
}

void Stop::setPlatform(unsigned int iPlatform)
{
    mPlatform = iPlatform;
}


//
// Operators
//

bool iRail::operator==(const Stop& lhs, const Stop& rhs)
{
    return  (*lhs.id() == *rhs.id() &&
             lhs.platform() == rhs.platform());
}

Stop& Stop::operator=(const Stop& other)
{
    if (this != &other)
    {
        Q_ASSERT(this->id() == other.id());

        setPlatform(other.platform());
    }
    return *this;
}

inline unsigned int qHash(const Stop::Id& iStopId)
{
    return qHash(*iStopId.station->id()) ^ qHash(iStopId.datetime);
}

bool iRail::operator==(const Stop::Id& lhs, const Stop::Id& rhs)
{
    return  (*lhs.station->id() == *rhs.station->id() &&
             lhs.datetime == rhs.datetime);
}
