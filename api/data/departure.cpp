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
    mDelay = 0;
}


//
// Basic I/O
//

QVariant Departure::field(int iRole) const
{
    switch (iRole)
    {
    case Qt::DisplayRole:
    case Departure::VehicleRole:
        return QVariant::fromValue(id()->vehicle);
    case Departure::OriginRole:
        return QVariant::fromValue(id()->origin);
    case Departure::DelayRole:
        return QVariant::fromValue(delay());
    default:
        return QVariant();
    }
}

Departure::Id const* Departure::id() const
{
    return &mId;
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
    return  (*lhs.id() == *rhs.id() &&
             lhs.delay() == rhs.delay());
}

Departure& Departure::operator=(const Departure& other)
{
    if (this != &other)
    {
        Q_ASSERT(this->id() == other.id());

        setDelay(other.delay());
    }
    return *this;
}

inline unsigned int qHash(const Departure::Id& iDepartureId)
{
    return qHash(*iDepartureId.origin->id()) ^ qHash(*iDepartureId.vehicle->id());
}

bool iRail::operator==(const Departure::Id& lhs, const Departure::Id& rhs)
{
    return  (*lhs.vehicle->id() == *rhs.vehicle->id() &&
             *lhs.origin->id() == *rhs.origin->id());
}
