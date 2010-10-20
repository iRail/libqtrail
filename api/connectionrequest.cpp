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
    mDateTime = 0;
}


ConnectionRequest::~ConnectionRequest()
{
    if (mDateTime)
        delete mDateTime;
}


//
// Basic I/O
//

QString ConnectionRequest::getOrigin() const
{
    return mOrigin;
}

QString ConnectionRequest::getDestination() const
{
    return mDestination;
}


bool ConnectionRequest::hasDateTime() const
{
    return (mDateTime != 0);
}

ConnectionRequest::DateTime ConnectionRequest::getDateTime() const
{
    return *mDateTime;
}

void ConnectionRequest::setDateTime(const ConnectionRequest::DateTime& iDateTime)
{
    if (mDateTime)
        delete mDateTime;
    mDateTime = new DateTime(iDateTime);
}

void ConnectionRequest::setDateTime(const TimeType& iTimeType, const QDate& iDate, const QTime& iTime)
{
    if (mDateTime)
        delete mDateTime;
    mDateTime = new DateTime();
    mDateTime->type = iTimeType;
    mDateTime->datetime.setDate(iDate);
    mDateTime->datetime.setTime(iTime);
}

//
// Debugging
//

QDebug operator<<(QDebug dbg, const ConnectionRequest &iConnectionRequest)
{
    dbg << "ConnectionRequest(from='" << iConnectionRequest.getOrigin() << "', to='" << iConnectionRequest.getDestination() << "'";
    if (iConnectionRequest.hasDateTime())
        dbg << ", at='" << iConnectionRequest.getDateTime().datetime.toString(Qt::LocaleDate) << " (" << iConnectionRequest.getDateTime().type << ")'";
    dbg << ")";
    return dbg.maybeSpace();
}
