//
// Configuration
//

// Includes
#include "data.h"

// Namespaces
using namespace iRail;


//
// Operators
//

unsigned int iRail::qHash(const Data::AbstractId& id)
{
    return id.hash();
}

bool iRail::operator==(const Data::AbstractId& lhs, const Data::AbstractId& rhs)
{
    return lhs.equals(rhs);
}

bool iRail::operator==(const Data& lhs, const Data& rhs)
{
    return lhs.equals(rhs);
}
