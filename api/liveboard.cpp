//
// Configuration
//

// Includes
#include "liveboard.h"
#include <QString>

// Namespaces
using namespace iRail;


//
// Construction and destruction
//

Liveboard::Liveboard(QString iStation) : mStation(iStation)
{
    qRegisterMetaType<LiveboardPointer>("LiveboardPointer");
    qRegisterMetaType<Liveboard::Departure>("Liveboard::Departure");
}


//
// Basic I/O
//

QString Liveboard::station() const
{
    return mStation;
}

QList<Liveboard::Departure> Liveboard::departures() const
{
    return mDepartures;
}

void Liveboard::setDepartures(const QList<Liveboard::Departure>& iDepartures)
{
    mDepartures = QList<Liveboard::Departure>(iDepartures);
}


//
// Debugging
//

QDebug operator<<(QDebug dbg, const Liveboard &iLiveboard)
{
    dbg << "Liveboard(station=" << iLiveboard.station() << ",departures=" << iLiveboard.departures().size() << ")";
    return dbg.maybeSpace();
}
