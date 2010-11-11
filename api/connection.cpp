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
// Debugging
//

QDebug operator<<(QDebug dbg, const Connection &iConnection)
{
    dbg << "Connection('" << iConnection.departure().station << "', platform " << iConnection.departure().platform << " → ";
    for (int i = 0; i < iConnection.lines().size(); i++)
        dbg << "Connection('" << iConnection.lines().at(i).arrival.station << "', platform " << iConnection.lines().at(i).arrival.platform << " to " << iConnection.lines().at(i).departure.platform << " → ";
    dbg << iConnection.arrival().station << "', platform " << iConnection.arrival().platform << ")";
    return dbg.maybeSpace();
}
