//
// Configuration
//

// Includes
#include "departurelist.h"
#include <QString>

// Namespaces
using namespace iRail;


//
// Construction and destruction
//

DepartureList::DepartureList(const Station& iStation) : mStation(iStation)
{
    qRegisterMetaType<DepartureList>("DepartureList");
}


//
// Basic I/O
//

Station DepartureList::station() const
{
    return mStation;
}


//
// Operators
//

QDataStream& iRail::operator<<(QDataStream& iStream, const DepartureList& iDepartureList)
{
    iStream << iDepartureList.mStation;

    iStream << iDepartureList.mDepartures.size();
    foreach (DepartureList::Departure tDeparture, iDepartureList.mDepartures)
        iStream << tDeparture;

    return iStream;
}

QDataStream& iRail::operator>>(QDataStream& iStream, DepartureList& iDepartureList)
{
    iStream >> iDepartureList.mStation;

    int tDepartures;
    iStream >> tDepartures;
    iDepartureList.mDepartures = QList<DepartureList::Departure>();
    for (int i = 0; i < tDepartures; i++)
    {
        DepartureList::Departure tDeparture;
        iStream >> tDeparture;
        iDepartureList.mDepartures << tDeparture;
    }

    return iStream;
}

