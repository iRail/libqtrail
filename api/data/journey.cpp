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

    mDelay = 0;
}


//
// Basic I/O
//

Journey::Id id() const
{
    return mId;
}

unsigned int Journey::delay() const
{
    return mDelay;
}

void Journey::setDelay(unsigned int iDelay)
{
    mDelay = iDelay;
}


//
// Operators
//

bool iRail::operator==(const Journey& lhs, const Journey& rhs)
{
    return  (lhs.id().origin || rhs.id().origin &&
             lhs.id().destination || rhs.id().destination);
}

iRail::Journey& iRail::operator=(const Journey& other)
{
    if (this != &other)
    {
        Q_ASSERT(this->id() == other.id());

        setDelay(other.delay());
    }
    return *this;
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
