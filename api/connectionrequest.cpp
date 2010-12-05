//
// Configuration
//

// Includes
#include "connectionrequest.h"

// Namespaces
using namespace iRail;


//
// Construction and destruction
//

ConnectionRequest::ConnectionRequest(const QString& iOrigin, const QString& iDestination) : mOrigin(iOrigin), mDestination(iDestination)
{
    qRegisterMetaType<ConnectionRequestPointer>("ConnectionRequestPointer");
    qRegisterMetaTypeStreamOperators<ConnectionRequestPointer>("ConnectionRequestPointer");
    mTimed = false;
    mTime = 0;
}


ConnectionRequest::~ConnectionRequest()
{
    if (mTimed)
        delete mTime;
}


//
// Basic I/O
//

QString ConnectionRequest::origin() const
{
    return mOrigin;
}

QString ConnectionRequest::destination() const
{
    return mDestination;
}


bool ConnectionRequest::timed() const
{
    return mTimed;
}

const ConnectionRequest::Time *ConnectionRequest::time() const
{
    return mTime;
}

void ConnectionRequest::setTime(const ConnectionRequest::Time& iTime)
{
    if (mTimed)
        delete mTime;
    else
        mTimed = true;
    mTime = new Time(iTime);
}

void ConnectionRequest::setTime(const TimeType& iTimeType, const QDate& iDate, const QTime& iTime)
{
    if (mTimed)
        delete mTime;
    else
        mTimed = true;
    Time *tTime = new Time();
    tTime->type = iTimeType;
    tTime->datetime.setDate(iDate);
    tTime->datetime.setTime(iTime);
    mTime = tTime;
}

//
// Operators
//

QDebug &iRail::operator<<(QDebug dbg, const ConnectionRequest& iConnectionRequest)
{
    dbg << "ConnectionRequest(from='" << iConnectionRequest.origin() << "', to='" << iConnectionRequest.destination() << "'";
    if (iConnectionRequest.timed())
        dbg << ", at='" << iConnectionRequest.time()->datetime.toString(Qt::DefaultLocaleShortDate) << " (" << iConnectionRequest.time()->type << ")'";
    dbg << ")";

    return dbg.maybeSpace();
}

QDataStream &iRail::operator<<(QDataStream& iStream, const ConnectionRequest& iConnectionRequest)
{
    iStream << iConnectionRequest.mOrigin;
    iStream << iConnectionRequest.mDestination;
    iStream << iConnectionRequest.mTimed;
    if (iConnectionRequest.mTimed)
        iConnectionRequest.mTime->operator <<(iStream);

    return iStream;
}

QDataStream &iRail::operator>>(QDataStream& iStream, ConnectionRequest& iConnectionRequest)
{
    iStream >> iConnectionRequest.mOrigin;
    iStream >> iConnectionRequest.mDestination;
    iStream >> iConnectionRequest.mTimed;
    if (iConnectionRequest.mTimed)
    {
        iConnectionRequest.mTime = new ConnectionRequest::Time();
        iConnectionRequest.mTime->operator >>(iStream);
    }

    return iStream;
}

QDataStream &iRail::operator<<(QDataStream& iStream, const ConnectionRequestPointer& iConnectionRequest)
{
    iStream << (*iConnectionRequest);

    return iStream;
}

QDataStream &iRail::operator>>(QDataStream& iStream, ConnectionRequestPointer& iConnectionRequest)
{
    ConnectionRequest *tConnectionRequest = new ConnectionRequest("dummy", "dummy");
    iStream >> *tConnectionRequest;
    iConnectionRequest = ConnectionRequestPointer(tConnectionRequest);

    return iStream;
}
