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

POI::POI(const QString& iStation, const QDateTime& iDatetime) : mStation(iStation), mDatetime(iDatetime)
{
    qRegisterMetaType<POI>("POI");
}


POI::~POI()
{
}


//
// Basic I/O
//

QString POI::station() const
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

QDataStream &iRail::operator<<(QDataStream& iStream, const POI& iPOI)
{
    iStream << iPOI.mStation;
    iStream << iPOI.mDatetime;
    iStream << iPOI.mDelay;
    iStream << iPOI.mPlatform;

    return iStream;
}
QDataStream &iRail::operator>>(QDataStream& iStream, POI& iPOI)
{
    iStream >> iPOI.mStation;
    iStream >> iPOI.mDatetime;
    iStream >> iPOI.mDelay;
    iStream >> iPOI.mPlatform;

    return iStream;
}
