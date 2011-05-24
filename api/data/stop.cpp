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

const QString& Stop::platform() const
{
    return mPlatform;
}

void Stop::setPlatform(const QString& iPlatform)
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

bool iRail::operator==(const Stop::Id& lhs, const Stop::Id& rhs)
{
    return  (*lhs.station->id() == *rhs.station->id() &&
             lhs.datetime == rhs.datetime);
}
