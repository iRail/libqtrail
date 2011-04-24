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
    setLongitude(iLongitude);
    setLatitude(iLatitude);
}

Location::Location()
{
    mLatitudeValid = false;
    mLatitude = 0;

    mLongitudeValid = false;
    mLongitude = 0;
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
    return  ((!lhs.mLongitudeValid || (lhs.longitude() == rhs.longitude())) &&
             (!lhs.mLatitudeValid || (lhs.latitude() == rhs.latitude())));
}

Location& Location::operator=(const Location& other)
{
    if (this != &other)
    {
        if (other.mLongitudeValid)
            setLongitude(other.longitude());
        if (other.mLatitudeValid)
            setLatitude(other.latitude());
    }
    return *this;
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

