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

Connection::Connection(const Transfer& iTransfer) : mTransfer(iTransfer)
{
    qRegisterMetaType<ConnectionPointer>("ConnectionPointer");
}


Connection::~Connection()
{
}


//
// Basic I/O
//


Connection::Transfer Connection::transfer() const
{
    return mTransfer;
}

QList<Connection::Transfer> Connection::transfers() const
{
    return mTransfers;
}

void Connection::setTransfers(const QList<Connection::Transfer>& iTransfers)
{
    mTransfers = QList<Connection::Transfer>(iTransfers);
}



//
// Debugging
//

QDebug operator<<(QDebug dbg, const Connection &iConnection)
{
    dbg << "Connection('" << iConnection.transfer().departure.station << "', platform " << iConnection.transfer().departure.platform << " → ";
    for (int i = 0; i < iConnection.transfers().size(); i++)
        dbg << "Connection('" << iConnection.transfers().at(i).arrival.station << "', platform " << iConnection.transfers().at(i).arrival.platform << " to " << iConnection.transfers().at(i).departure.platform << " → ";
    dbg << iConnection.transfer().arrival.station << "', platform " << iConnection.transfer().arrival.platform << ")";
    return dbg.maybeSpace();
}
