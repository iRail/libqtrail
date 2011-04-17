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

QDataStream &iRail::operator<<(QDataStream& iStream, const Departure& iDeparture)
{
    iStream << iDeparture.mVehicle;
    iStream << iDeparture.mPOI;

    return iStream;
}
QDataStream &iRail::operator>>(QDataStream& iStream, Departure& iDeparture)
{
    iStream >> iDeparture.mVehicle;
    iStream >> iDeparture.mPOI;

    return iStream;
}
