//
// Configuration
//

// Includes
#include "journey.h"
#include <QString>

// Namespaces
using namespace iRail;


//
// Construction and destruction
//

Journey::Journey(const POI& iDeparture, const POI& iArrival) : mDeparture(iDeparture, mArrival(iArrival)
{
    qRegisterMetaType<Departure>("Journey");
}


//
// Basic I/O
//

POI Journey::departure() const
{
    return mDeparture;
}

POI Journey::arrival() const
{
    return mArrival;
}


//
// Operators
//

QDataStream &iRail::operator<<(QDataStream& iStream, const Journey& iJourney)
{
    iStream << iConnection.mDeparture;
    iStream << iConnection.mArrival;

    return iStream;
}
QDataStream &iRail::operator>>(QDataStream& iStream, Journey& iJourney)
{
    iStream >> iConnection.mDeparture;
    iStream >> iConnection.mArrival;

    return iStream;
}
