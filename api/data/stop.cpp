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

Stop::Stop(IId iId) : mId(iId)
{
    mPlatform = 0;
}


Stop::~Stop()
{
}


//
// Basic I/O
//

Data::Id& Stop::id() const
{
    return mId;
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
    return  (id().station == other.id().station &&
             id().datetime == other.id().datetime &&
             delay() == other.delay() &&
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

unsigned int Stop::IId::hash() const
{
    return qHash(station) ^ qHash(datetime);
}

bool Stop::IId::equals(const Data::Id& data) const
{
    const Stop::IId& other = dynamic_cast<const Stop::IId&>(data);
    return  (station->id() == other.station->id() &&
             datetime == other.datetime);
}
