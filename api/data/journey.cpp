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
    return  (lhs.id().origin || rhs.id().origin &&
             lhs.id().destination || rhs.id().destination);
}

unsigned int qHash(const Journey::Id& iJourneyId)
{
    return (3*qHash(iJourneyId.origin)) ^ (5*qHash(iJourneyId.destination));
}

bool iRail::operator==(const Journey::Id& lhs, const Journey::Id& rhs)
{
    return  (lhs.origin->id() == rhs.origin->id() &&
             lhs.destination->id() == rhs.destination->id());
}
