//
// Configuration
//

// Includes
#include "departure.h"
#include <QString>

// Namespaces
using namespace iRail;


//
// Construction and destruction
//

Departure::Departure(Id iId) : mId(iId)
{
    qRegisterMetaType<Departure>("Departure");
    qRegisterMetaType<Departure::Id>("Departure::Id");
}


//
// Basic I/O
//

Departure::Id Departure::id() const
{
    return mId;
}

unsigned int Departure::delay() const
{
    return mDelay;
}

void Departure::setDelay(unsigned int iDelay)
{
    mDelay = iDelay;
}


//
// Operators
//

bool iRail::operator==(const Departure& lhs, const Departure& rhs)
{
    return  (lhs.id().vehicle == rhs.id().vehicle &&
             lhs.id().origin == rhs.id().origin);
}

inline unsigned int qHash(const Departure::Id& iDepartureId)
{
    return qHash(iDepartureId.origin) ^ qHash(iDepartureId.vehicle);
}

bool iRail::operator==(const Departure::Id& lhs, const Departure::Id& rhs)
{
    return  (lhs.vehicle->id() == rhs.vehicle->id() &&
             lhs.origin->id() == rhs.origin->id());
}
