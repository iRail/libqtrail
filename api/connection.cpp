//
// Configuration
//

// Includes
#include "connection.h"
#include <QString>

// Namespaces
using namespace iRail;


//
// Construction and destruction
//

Connection::Connection(const POI& iDeparture, const POI& iArrival) : mDeparture(iDeparture), mArrival(iArrival)
{
    qRegisterMetaType<ConnectionPointer>("ConnectionPointer");
    qRegisterMetaType<Connection::POI>("Connection::POI");
}


Connection::~Connection()
{
}


//
// Basic I/O
//


Connection::POI Connection::departure() const
{
    return mDeparture;
}

Connection::POI Connection::arrival() const
{
    return mArrival;
}

QList<Connection::Line> Connection::lines() const
{
    return mLines;
}

void Connection::setLines(const QList<Connection::Line>& iLines)
{
    mLines = QList<Connection::Line>(iLines);
}


//
// Operators
//

QDebug Connection::operator<<(QDebug dbg) const
{
    dbg << "Connection('" << departure().station << "', platform " << departure().platform << " → ";
    for (int i = 0; i < lines().size(); i++)
        dbg << "Connection('" << lines().at(i).arrival.station << "', platform " << lines().at(i).arrival.platform << " to " << lines().at(i).departure.platform << " → ";
    dbg << arrival().station << "', platform " << arrival().platform << ")";

    return dbg.maybeSpace();
}

QDataStream& Connection::operator<<(QDataStream& iStream) const
{
    mDeparture.operator <<(iStream);
    mArrival.operator <<(iStream);

    iStream << mLines.size();
    foreach (Line tLine, mLines)
        tLine.operator <<(iStream);

    return iStream;
}

QDataStream& Connection::operator>>(QDataStream& iStream)
{
    mDeparture.operator >>(iStream);
    mArrival.operator >>(iStream);

    int tLines;
    iStream >> tLines;
    mLines = QList<Line>();
    for (int i = 0; i < tLines; i++)
    {
        POI tDummy;
        Line tLine(tDummy, tDummy);
        tLine.operator >>(iStream);
        mLines << tLine;
    }

    return iStream;
}
