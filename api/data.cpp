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

unsigned int iRail::qHash(const Data::Id& id)
{
    return id.hash();
}

bool iRail::operator==(const Data::Id& lhs, const Data::Id& rhs)
{
    return lhs.equals(rhs);
}

bool iRail::operator==(const Data& lhs, const Data& rhs)
{
    return lhs.equals(rhs);
}
