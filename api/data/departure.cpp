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
// Operator implementation
//

bool Departure::equals(const Data& data) const
{
    const Departure& other = dynamic_cast<const Departure&>(data);
    return  (id() == other.id() &&
             delay() == other.delay());
}

Data& Departure::assign(const Data& data)
{
    const Departure& other = dynamic_cast<const Departure&>(data);
    if (this != &other)
    {
        Q_ASSERT(this->id() == other.id());

        setDelay(other.delay());
    }
    return *this;
}

unsigned int Departure::Id::hash() const
{
    return qHash(origin) ^ qHash(vehicle);
}

bool Departure::Id::equals(const AbstractId& data) const
{
    const Departure::Id& other = dynamic_cast<const Departure::Id&>(data);
    return  (vehicle->id() == other.vehicle->id() &&
             origin->id() == other.origin->id());
}
