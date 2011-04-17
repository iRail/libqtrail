//
// Configuration
//

// Includes
#include "stationlist.h"
#include <QString>

// Namespaces
using namespace iRail;


//
// Construction and destruction
//

StationList::StationList()
{
    qRegisterMetaType<StationList>("StationList");
}


StationList::~Connection()
{
}


//
// Operators
//

QDataStream& iRail::operator<<(QDataStream& iStream, const StationList& iStationList)
{
    return iStream;
}

QDataStream& iRail::operator>>(QDataStream& iStream, StationList& iStationList)
{
    return iStream;
}
