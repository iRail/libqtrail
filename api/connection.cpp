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


Connection::Transfer Connection::getTransfer() const
{
    return mTransfer;
}

QList<Connection::Transfer> Connection::getTransfers() const
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
    dbg << "Connection('" << iConnection.getTransfer().departure.station << "', platform " << iConnection.getTransfer().departure.platform << " → ";
    for (int i = 0; i < iConnection.getTransfers().size(); i++)
        dbg << "Connection('" << iConnection.getTransfers().at(i).arrival.station << "', platform " << iConnection.getTransfers().at(i).arrival.platform << " to " << iConnection.getTransfers().at(i).departure.platform << " → ";
    dbg << iConnection.getTransfer().arrival.station << "', platform " << iConnection.getTransfer().arrival.platform << ")";
    return dbg.maybeSpace();
}
