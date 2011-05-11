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
// Operator implementation
//

bool Stop::equals(const Data& data) const
{
    const Stop& other = dynamic_cast<const Stop&>(data);
    return  (id()->station == other.id()->station &&
             id()->datetime == other.id()->datetime &&
             platform() == other.platform());
}

Data& Stop::assign(const Data& data)
{
    const Stop& other = dynamic_cast<const Stop&>(data);
    if (this != &other)
    {
        Q_ASSERT(this->id() == other.id());

        setPlatform(other.platform());
    }
    return *this;
}

unsigned int Stop::Id::hash() const
{
    return qHash(*station->id()) ^ ::qHash(datetime.toMSecsSinceEpoch());
}

bool Stop::Id::equals(const AbstractId& data) const
{
    const Stop::Id& other = dynamic_cast<const Stop::Id&>(data);
    return  (station->id() == other.station->id() &&
             datetime == other.datetime);
}
