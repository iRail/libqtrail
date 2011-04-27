//
// Configuration
//

// Includes
#include "data.h"

// Namespaces
using namespace iRail;


//
// Construction and destruction
//

Data::VirtualId::VirtualId(const Data::AbstractId *iId) : id(iId)
{

}

Data::VirtualId::VirtualId(const VirtualId &iVirtualId)
{
    id = iVirtualId.id;
}


//
// Operators
//

bool iRail::operator==(const Data::AbstractId& lhs, const Data::AbstractId& rhs)
{
    return lhs.equals(rhs);
}

bool iRail::operator==(const Data& lhs, const Data& rhs)
{
    return lhs.equals(rhs);
}

bool iRail::operator==(const Data::VirtualId& lhs, const Data::VirtualId& rhs)
{
    return *(lhs.id) == *(rhs.id); // this is why VirtualId is needed, dereferencing while comparing
}
