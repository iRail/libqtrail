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

Departure::Departure(const QString& iVehicle, const POI& iPOI) : mVehicle(iVehicle), mPOI(iPOI)
{
    qRegisterMetaType<Departure>("Departure");
}


//
// Basic I/O
//

QString Departure::vehicle() const
{
    return mVehicle;
}

POI Departure::poi() const
{
    return mPOI;
}


//
// Operators
//

bool iRail::operator==(const Departure& lhs, const Departure& rhs)
{
    return  (lhs.vehicle() == rhs.vehicle() &&
             lhs.poi() == rhs.poi());
}

bool iRail::operator||(const Departure& lhs, const Departure& rhs)
{
    return  (lhs.vehicle() || rhs.vehicle() &&
             lhs.poi() || rhs.poi());
}

QDataStream& iRail::operator<<(QDataStream& iStream, const Departure& iDeparture)
{
    iStream << iDeparture.mVehicle;
    iStream << iDeparture.mPOI;

    return iStream;
}
QDataStream& iRail::operator>>(QDataStream& iStream, Departure& iDeparture)
{    
    Vehicle* tVehicle = new Vehicle("dummy");
    iStream >> tVehicle;
    iDeparture.mVehicle = tVehicle;

    POI* tPOI = new POI(new Station("dummy"), QDateTime());
    iStream >> tDeparture;
    iConnection.mPOI = tPOI;

    return iStream;
}
