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
// Operators
//

QDebug Liveboard::operator<<(QDebug dbg) const
{
    dbg << "Liveboard(station=" << station() << ",departures=" << departures().size() << ")";

    return dbg.maybeSpace();
}

QDataStream& Liveboard::operator<<(QDataStream& iStream) const
{
    iStream << mStation;

    iStream << mDepartures.size();
    foreach (Departure tDeparture, mDepartures)
        tDeparture.operator <<(iStream);

    return iStream;
}

QDataStream& Liveboard::operator>>(QDataStream& iStream)
{
    iStream >> mStation;

    int tDepartures;
    iStream >> tDepartures;
    mDepartures = QList<Departure>();
    for (int i = 0; i < tDepartures; i++)
    {
        Departure tDeparture;
        tDeparture.operator >>(iStream);
        mDepartures << tDeparture;
    }

    return iStream;
}
