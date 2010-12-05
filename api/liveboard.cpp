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
    qRegisterMetaTypeStreamOperators<LiveboardPointer>("LiveboardPointer");
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

QDebug& iRail::operator<<(QDebug dbg, const Liveboard& iLiveboard)
{
    dbg << "Liveboard(station=" << iLiveboard.station() << ",departures=" << iLiveboard.departures().size() << ")";

    return dbg.maybeSpace();
}

QDataStream &iRail::operator<<(QDataStream& iStream, const Liveboard::Departure& iDeparture)
{
    iStream << iDeparture.station;
    iStream << iDeparture.vehicle;
    iStream << iDeparture.delay;
    iStream << iDeparture.datetime;
    iStream << iDeparture.platform;

    return iStream;
}
QDataStream &iRail::operator>>(QDataStream& iStream, Liveboard::Departure& iDeparture)
{
    iStream >> iDeparture.station;
    iStream >> iDeparture.vehicle;
    iStream >> iDeparture.delay;
    iStream >> iDeparture.datetime;
    iStream >> iDeparture.platform;

    return iStream;
}

QDataStream& iRail::operator<<(QDataStream& iStream, const Liveboard& iLiveboard)
{
    iStream << iLiveboard.mStation;

    iStream << iLiveboard.mDepartures.size();
    foreach (Liveboard::Departure tDeparture, iLiveboard.mDepartures)
        iStream << tDeparture;

    return iStream;
}

QDataStream& iRail::operator>>(QDataStream& iStream, Liveboard& iLiveboard)
{
    iStream >> iLiveboard.mStation;

    int tDepartures;
    iStream >> tDepartures;
    iLiveboard.mDepartures = QList<Liveboard::Departure>();
    for (int i = 0; i < tDepartures; i++)
    {
        Liveboard::Departure tDeparture;
        iStream >> tDeparture;
        iLiveboard.mDepartures << tDeparture;
    }

    return iStream;
}

QDataStream &iRail::operator<<(QDataStream& iStream, const LiveboardPointer& iLiveboard)
{
    iStream << (*iLiveboard);

    return iStream;
}

QDataStream &iRail::operator>>(QDataStream& iStream, LiveboardPointer& iLiveboard)
{
    Liveboard *tLiveboard = new Liveboard("dummy");
    iStream >> *tLiveboard;
    iLiveboard = LiveboardPointer(tLiveboard);

    return iStream;
}
