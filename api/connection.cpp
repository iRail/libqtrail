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
    qRegisterMetaTypeStreamOperators<ConnectionPointer>("ConnectionPointer");
    qRegisterMetaType<Connection::Line>("Connection::Line");
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

QDebug& iRail::operator<<(QDebug dbg, const Connection& iConnection)
{
    dbg << "Connection('" << iConnection.departure().station << "', platform " << iConnection.departure().platform << " → ";
    for (int i = 0; i < iConnection.lines().size(); i++)
        dbg << "Connection('" << iConnection.lines().at(i).arrival.station << "', platform " << iConnection.lines().at(i).arrival.platform << " to " << iConnection.lines().at(i).departure.platform << " → ";
    dbg << iConnection.arrival().station << "', platform " << iConnection.arrival().platform << ")";

    return dbg.maybeSpace();
}

QDataStream &iRail::operator<<(QDataStream& iStream, const Connection::Line& iLine)
{
    iStream << iLine.departure;
    iStream << iLine.arrival;
    iStream << iLine.terminus;
    iStream << iLine.vehicle;

    return iStream;
}
QDataStream &iRail::operator>>(QDataStream& iStream, Connection::Line& iLine)
{
    iStream >> iLine.departure;
    iStream >> iLine.arrival;
    iStream >> iLine.terminus;
    iStream >> iLine.vehicle;

    return iStream;
}

QDataStream &iRail::operator<<(QDataStream& iStream, const Connection::POI& iPOI)
{
    iStream << iPOI.station;
    iStream << iPOI.delay;
    iStream << iPOI.datetime;
    iStream << iPOI.platform;

    return iStream;
}
QDataStream &iRail::operator>>(QDataStream& iStream, Connection::POI& iPOI)
{
    iStream >> iPOI.station;
    iStream >> iPOI.delay;
    iStream >> iPOI.datetime;
    iStream >> iPOI.platform;

    return iStream;
}

QDataStream& iRail::operator<<(QDataStream& iStream, const Connection& iConnection)
{
    iStream << iConnection.mDeparture;
    iStream << iConnection.mArrival;

    iStream << iConnection.mLines.size();
    foreach (Connection::Line tLine, iConnection.mLines)
        iStream << tLine;

    return iStream;
}

QDataStream& iRail::operator>>(QDataStream& iStream, Connection& iConnection)
{
    iStream >> iConnection.mDeparture;
    iStream >> iConnection.mArrival;

    int tLines;
    iStream >> tLines;
    iConnection.mLines = QList<Connection::Line>();
    for (int i = 0; i < tLines; i++)
    {
        Connection::Line tLine;
        iStream >> tLine;
        iConnection.mLines << tLine;
    }

    return iStream;
}

QDataStream &iRail::operator<<(QDataStream& iStream, const ConnectionPointer& iConnection)
{
    iStream << (*iConnection);

    return iStream;
}

QDataStream &iRail::operator>>(QDataStream& iStream, ConnectionPointer& iConnection)
{
    Connection *tConnection = new Connection(Connection::POI(), Connection::POI());
    iStream >> *tConnection;
    iConnection = ConnectionPointer(tConnection);

    return iStream;
}
