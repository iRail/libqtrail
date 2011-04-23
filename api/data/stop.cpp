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

unsigned int Stop::delay() const
{
    return mDelay;
}

void Stop::setDelay(unsigned int iDelay)
{
    mDelay = iDelay;
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
    return  (lhs.station() == rhs.station() &&
             lhs.datetime() == rhs.datetime() &&
             lhs.delay() == rhs.delay() &&
             lhs.platform() == rhs.platform());
}

bool iRail::operator||(const Stop& lhs, const Stop& rhs)
{
    return  (lhs.station() || rhs.station() &&
             lhs.datetime() == rhs.datetime());
}

QDataStream& iRail::operator<<(QDataStream& iStream, const Stop& iStop)
{
    iStream << iStop.mStation;
    iStream << iStop.mDatetime;
    iStream << iStop.mDelay;
    iStream << iStop.mPlatform;

    return iStream;
}
QDataStream& iRail::operator>>(QDataStream& iStream, Stop& iStop)
{
    Station* tStation = new Station("dumme");
    iStream >> *tStation;
    iStop.mStation = tStation;

    iStream >> iStop.mDatetime;
    iStream >> iStop.mDelay;
    iStream >> iStop.mPlatform;

    return iStream;
}
