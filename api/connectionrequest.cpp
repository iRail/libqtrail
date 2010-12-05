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

QDebug &iRail::operator<<(QDebug dbg, const ConnectionRequest& iRequest)
{
    dbg << "ConnectionRequest(from='" << iRequest.origin() << "', to='" << iRequest.destination() << "'";
    if (iRequest.timed())
        dbg << ", at='" << iRequest.time()->datetime.toString(Qt::DefaultLocaleShortDate) << " (" << iRequest.time()->type << ")'";
    dbg << ")";

    return dbg.maybeSpace();
}

QDataStream &iRail::operator<<(QDataStream& iStream, const ConnectionRequest& iRequest)
{
    qDebug() << "Saving connectionrequest";
    iStream << iRequest.mOrigin;
    iStream << iRequest.mDestination;
    iStream << iRequest.mTimed;
    if (iRequest.mTimed)
        iRequest.mTime->operator <<(iStream);

    return iStream;
}

QDataStream &iRail::operator>>(QDataStream& iStream, ConnectionRequest& iRequest)
{
    qDebug() << "Reading connectionrequest";
    iStream >> iRequest.mOrigin;
    iStream >> iRequest.mDestination;
    iStream >> iRequest.mTimed;
    if (iRequest.mTimed)
    {
        iRequest.mTime = new ConnectionRequest::Time();
        iRequest.mTime->operator >>(iStream);
    }

    return iStream;
}

QDataStream &iRail::operator<<(QDataStream& iStream, const ConnectionRequestPointer& iRequest)
{
    qDebug() << "Saving connectionrequestpointer for" << iRequest->origin();
    iStream << (*iRequest);

    return iStream;
}

QDataStream &iRail::operator>>(QDataStream& iStream, ConnectionRequestPointer& iRequest)
{
    qDebug() << "Reading connectionrequestpointer";
    ConnectionRequest *tConnectionRequest = new ConnectionRequest("dummy", "dummy");
    iStream >> *tConnectionRequest;
    iRequest = ConnectionRequestPointer(tConnectionRequest);

    return iStream;
}
