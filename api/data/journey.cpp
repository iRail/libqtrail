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

Journey::Journey(Journey::Id iId) : mId(iId)
{
    qRegisterMetaType<Journey>("Journey");
    qRegisterMetaType<Journey::Id>("Journey::Id");
}


//
// Basic I/O
//

Journey::Id id() const
{
    return mId;
}


//
// Operators
//

bool iRail::operator==(const Journey& lhs, const Journey& rhs)
{
    return  (lhs.departure() == rhs.departure() &&
             lhs.arrival() == rhs.arrival() &&
             lhs.connections() == rhs.connections());
    // TODO
}

bool iRail::operator==(const Journey& lhs, const Journey& rhs)
{
    return  (lhs.departure() || rhs.departure() &&
             lhs.arrival() || rhs.arrival() &&
             lhs.connections() == rhs.connections());
}

QDataStream& iRail::operator<<(QDataStream& iStream, const Journey& iJourney)
{
    iStream << iJourney.mDeparture;
    iStream << iJourney.mArrival;

    return iStream;
}
QDataStream& iRail::operator>>(QDataStream& iStream, Journey& iJourney)
{
    Stop* tDeparture = new Stop(new Station("dummy"), QDateTime());
    iStream >> tDeparture;
    iJourney.mDeparture = tDeparture;

    Stop* tArrival = new Stop(new Station("dummy"), QDateTime());
    iStream >> tDeparture;
    iJourney.mArrival = tArrival;

    return iStream;
}
