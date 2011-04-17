//
// Configuration
//

// Includes
#include "journeylist.h"
#include <QString>

// Namespaces
using namespace iRail;


//
// Construction and destruction
//

JourneyList::JourneyList(const POI& iDeparture, const POI& iArrival) : mDeparture(iDeparture), mArrival(iArrival)
{
    qRegisterMetaType<JourneyList>("JourneyList");
}


JourneyList::~Connection()
{
}


//
// Basic I/O
//


POI JourneyList::departure() const
{
    return mDeparture;
}

POI JourneyList::arrival() const
{
    return mArrival;
}


//
// Operators
//

QDataStream& iRail::operator<<(QDataStream& iStream, const JourneyList& iJourneyList)
{
    iStream << iJourneyList.mDeparture;
    iStream << iJourneyList.mArrival;

    iStream << iJourneyList.mConnections.size();
    foreach (Connection tConnection, iJourneyList.mConnections)
        iStream << tConnection;

    return iStream;
}

QDataStream& iRail::operator>>(QDataStream& iStream, JourneyList& iJourneyList)
{
    iStream >> iJourneyList.mDeparture;
    iStream >> iJourneyList.mArrival;

    int tConnectionCount;
    iStream >> tConnectionCount;
    iJourneyList.mConnections = QList<Connection>();
    for (int i = 0; i < tConnectionCount; i++)
    {
        Connection tConnection;
        iStream >> tConnection;
        iJourneyList.mConnections << tConnection;
    }

    return iStream;
}
