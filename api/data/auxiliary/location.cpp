//
// Configuration
//

// Includes
#include "location.h"
#include <QString>

// Namespaces
using namespace iRail;


//
// Construction and destruction
//
Location::Location(qreal iLongitude, qreal iLatitude)
{
    this();

    setLongitude(iLongitude);
    setLatitude(iLatitude);
}

Location::Location()
{
    qRegisterMetaType<Location>("Location");

    mLatitudeValid = false;
    mLongitudeValid = false;
}

Location::~Location()
{
}


//
// Basic I/O
//

qreal Location::longitude() const
{
    return mLongitude;
}

void Location::setLongitude(qreal iLongitude)
{
    mLongitude = iLongitude;
    mLongitudeValid = true;
}

qreal Location::latitude() const
{
    return mLatitude;
}

void Location::setLatitude(qreal iLatitude)
{
    mLatitude = iLatitude;
    mLatitudeValid = true;
}

bool Location::valid() const
{
    return mLongitudeValid && mLatitudeValid;
}


//
// Operators
//

bool iRail::operator==(const Location& lhs, const Location& rhs)
{
    return  (lhs.valid() == rhs.valid() &&
             (!lhs.mLongitudeValid() || (lhs.longitude() == rhs.longitude())),
             (!lhs.mLatitudeValid() || (lhs.latitude() == rhs.latitude())));
}

QDataStream& iRail::operator<<(QDataStream& iStream, const Location& iLocation)
{
    iStream << iLocation.mLongitudeValid;
    if (iLocation.mLongitudeValid)
        iStream << iLocation.mLongitude;

    iStream << iLocation.mLatitudeValid;
    if (iLocation.mLatitudeValid)
        iStream << iLocation.mLatitude;

    return iStream;
}

QDataStream& iRail::operator>>(QDataStream& iStream, Location& iLocation)
{
    iStream >> iLocation.mLongitudeValid;
    if (iLocation.mLongitudeValid)
        iStream >> iLocation.mLongitude;

    iStream >> iLocation.mLatitudeValid;
    if (iLocation.mLatitudeValid)
        iStream >> iLocation.mLatitude;

    return iStream;
}

