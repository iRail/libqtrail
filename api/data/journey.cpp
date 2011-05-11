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
// Operator implementation
//

bool Journey::equals(const Data& data) const
{
    const Journey& other = dynamic_cast<const Journey&>(data);
    return  (id()->origin == other.id()->origin &&
             id()->destination == other.id()->destination &&
             delay() == other.delay());
}

Data& Journey::assign(const Data& data)
{
    const Journey& other = dynamic_cast<const Journey&>(data);
    if (this != &other)
    {
        Q_ASSERT(this->id() == other.id());

        setDelay(other.delay());
    }
    return *this;
}

unsigned int Journey::Id::hash() const
{
    return (3*qHash(origin)) ^ (5*qHash(destination));
}

bool Journey::Id::equals(const AbstractId& data) const
{
    const Journey::Id& other = dynamic_cast<const Journey::Id&>(data);
    return  (origin->id() == other.origin->id() &&
             destination->id() == other.destination->id());
}
