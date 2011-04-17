//
// Configuration
//

// Includes
#include "stoplist.h"
#include <QString>

// Namespaces
using namespace iRail;


//
// Construction and destruction
//

StopList::StopList(const Vehicle& iVehicle) : mVehicle(iVehicle)
{
    qRegisterMetaType<StopList>("StopList");

    mLimited = false;
}

StopList::StopList(const Connection& iConnection)
{
    this(iConnection.vehicle());

    mLimited = true;
    mDeparture = iConnection.departure();
    mArrival = iConnection.arrival();
}

StopList::~Connection()
{
}


//
// Basic I/O
//

Vehicle StopList::vehicle() const
{
    return mVehicle;
}


//
// Operators
//

QDataStream& iRail::operator<<(QDataStream& iStream, const StopList& iStopList)
{
    iStream << iStopList.mVehicle;

    iStream << iStopList.mLimited;
    if (iStopList.mLimited)
    {
        iStream << iStopList.mArrival;
        iStream << iStopList.mDeparture;
    }

    return iStream;
}

QDataStream& iRail::operator>>(QDataStream& iStream, StopList& iStopList)
{
    iStream >> iStopList.mVehicle;

    iStream >> iStopList.mLimited;
    if (iStopList.mLimited)
    {
        iStream >> iStopList.mArrival;
        iStream >> iStopList.mDeparture;
    }

    return iStream;
}
