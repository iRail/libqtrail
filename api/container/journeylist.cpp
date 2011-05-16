//
// Configuration
//

// Includes
#include "journeylist.h"
#include "api/reader/connectionsreader.h"
#include <QString>

// Namespaces
using namespace iRail;


//
// Construction and destruction
//

JourneyList::JourneyList(const Station::Id& iOrigin, const Station::Id& iDestination, QObject* iParent) : mOrigin(iOrigin), mDestination(iDestination), Container(iParent)
{
    QHash<int, QByteArray> tRoleNames;
    tRoleNames[Journey::OriginRole] = "origin";
    tRoleNames[Journey::DestinationRole] = "destination";
    tRoleNames[Journey::DelayRole] = "delay";
    setRoleNames(tRoleNames);
}

JourneyList::~JourneyList()
{
}


//
// Basic I/O
//


Station::Id const* JourneyList::origin() const
{
    return &mOrigin;
}

Station::Id const* JourneyList::destination() const
{
    return &mDestination;
}
