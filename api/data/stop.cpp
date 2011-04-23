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

Stop::Stop(Stop::Id iId) : mId(iId)
{
    qRegisterMetaType<Stop>("Stop");
    qRegisterMetaType<Stop>("Stop::Id");
}


Stop::~Stop()
{
}


//
// Basic I/O
//

Stop::Id Stop::id() const
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
// Operators
//

bool iRail::operator==(const Stop& lhs, const Stop& rhs)
{
    return  (lhs.id().station == rhs.id().station &&
             lhs.id().datetime == rhs.id().datetime &&
             lhs.delay() == rhs.delay() &&
             lhs.platform() == rhs.platform());
}

iRail::Stop& iRail::operator=(const Stop& other)
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
    return qHash(iStopId.station) ^ qHash(iStopId.datetime);
}

bool iRail::operator==(const Stop::Id& lhs, const Stop::Id& rhs)
{
    return  (lhs.station->id() == rhs.station->id() &&
             lhs.datetime == rhs.datetime);
}
