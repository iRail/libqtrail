//
// Configuration
//

// Includes
#include "poi.h"
#include <QString>

// Namespaces
using namespace iRail;


//
// Construction and destruction
//

POI::POI(Station const* iStation, const QDateTime& iDatetime) : mStation(iStation), mDatetime(iDatetime)
{
    qRegisterMetaType<POI>("POI");
}


POI::~POI()
{
}


//
// Basic I/O
//

Station const* POI::station() const
{
    return mStation;
}

QDateTime POI::datetime() const
{
    return mDatetime;
}

unsigned int POI::delay() const
{
    return mDelay;
}

void POI::setDelay(unsigned int iDelay)
{
    mDelay = iDelay;
}

unsigned int POI::platform() const
{
    return mPlatform;
}

void POI::setPlatform(unsigned int iPlatform)
{
    mPlatform = iPlatform;
}


//
// Operators
//

bool iRail::operator==(const POI& lhs, const POI& rhs)
{
    return  (lhs.station() == rhs.station() &&
             lhs.datetime() == rhs.datetime() &&
             lhs.delay() == rhs.delay() &&
             lhs.platform() == rhs.platform());
}

bool iRail::operator||(const POI& lhs, const POI& rhs)
{
    return  (lhs.station() || rhs.station() &&
             lhs.datetime() == rhs.datetime());
}

QDataStream& iRail::operator<<(QDataStream& iStream, const POI& iPOI)
{
    iStream << iPOI.mStation;
    iStream << iPOI.mDatetime;
    iStream << iPOI.mDelay;
    iStream << iPOI.mPlatform;

    return iStream;
}
QDataStream& iRail::operator>>(QDataStream& iStream, POI& iPOI)
{
    Station* tStation = new Station("dumme");
    iStream >> *tStation;
    iPOI.mStation = tStation;

    iStream >> iPOI.mDatetime;
    iStream >> iPOI.mDelay;
    iStream >> iPOI.mPlatform;

    return iStream;
}
