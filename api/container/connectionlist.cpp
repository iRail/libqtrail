//
// Configuration
//

// Includes
#include "connectionlist.h"
#include <QString>

// Namespaces
using namespace iRail;


//
// Construction and destruction
//

ConnectionList::ConnectionList(const Journey::Id& iJourneyId, QObject* iParent) : mJourneyId(iJourneyId), Container(iParent)
{
    QHash<int, QByteArray> tRoleNames;
    tRoleNames[Connection::OriginRole] = "origin";
    tRoleNames[Connection::DestinationRole] = "destination";
    tRoleNames[Connection::TerminusRole] = "terminus";
    tRoleNames[Connection::VehicleRole] = "vehicle";
    tRoleNames[Connection::DelayRole] = "delay";
    setRoleNames(tRoleNames);
}

ConnectionList::~ConnectionList()
{
}


//
// Basic I/O
//

Journey::Id const* ConnectionList::journeyId() const
{
    return &mJourneyId;
}

