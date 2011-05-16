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

Journey::Journey(Id iId) : mId(iId)
{
    mDelay = 0;
}


//
// Basic I/O
//

QVariant Journey::field(int iRole) const
{
    switch (iRole)
    {
    case Qt::DisplayRole:
    case Journey::OriginRole:
        return QVariant::fromValue(id()->origin);
    case Journey::DestinationRole:
        return QVariant::fromValue(id()->destination);
    case Journey::DelayRole:
        return QVariant::fromValue(delay());
    default:
        return QVariant();
    }
}

Journey::Id const* Journey::id() const
{
    return &mId;
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
    return  (*lhs.id() == *rhs.id() &&
             lhs.delay() == rhs.delay());
}

Journey& Journey::operator=(const Journey& other)
{
    if (this != &other)
    {
        Q_ASSERT(this->id() == other.id());

        setDelay(other.delay());
    }
    return *this;
}

bool iRail::operator==(const Journey::Id& lhs, const Journey::Id& rhs)
{
    return  (*lhs.origin->id() == *rhs.origin->id() &&
             *lhs.destination->id() == *rhs.destination->id());
}
