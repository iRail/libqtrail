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

Departure::Departure(IId iId) : mId(iId)
{
    mDelay = 0;
}


//
// Basic I/O
//

Data::Id& Departure::id() const
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
// Operator implementation
//

bool Departure::equals(const Data& data)
{
    const Departure& other = dynamic_cast<const Departure&>(data);
    return  (id().vehicle == other.id().vehicle &&
             id().origin == other.id().origin);
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

unsigned int Departure::IId::hash() const
{
    return qHash(origin) ^ qHash(vehicle);
}

bool Departure::IId::equals(const Data::Id& data) const
{
    const Departure::IId& other = dynamic_cast<const Departure::IId&>(data);
    return  (vehicle->id() == other.vehicle->id() &&
             origin->id() == other.origin->id());
}
