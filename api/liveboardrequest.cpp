//
// Configuration
//

// Includes
#include "liveboardrequest.h"

// Namespaces
using namespace iRail;


//
// Construction and destruction
//

LiveboardRequest::LiveboardRequest(const QString& iStation) : mStation(iStation)
{
    qRegisterMetaType<LiveboardRequestPointer>("LiveboardRequestPointer");
    qRegisterMetaTypeStreamOperators<LiveboardRequestPointer>("LiveboardRequestPointer");
    mTimed = false;
    mTime = 0;
}


LiveboardRequest::~LiveboardRequest()
{
    if (mTimed)
        delete mTime;
}


//
// Basic I/O
//

QString LiveboardRequest::station() const
{
    return mStation;
}


bool LiveboardRequest::timed() const
{
    return mTimed;
}

const QDateTime *LiveboardRequest::time() const
{
    return mTime;
}

void LiveboardRequest::setTime(const QDateTime& iTime)
{
    if (mTimed)
        delete mTime;
    else
        mTimed = true;
    mTime = new QDateTime(iTime);
}

void LiveboardRequest::setTime(const QDate& iDate, const QTime& iTime)
{
    if (mTimed)
        delete mTime;
    else
        mTimed = true;
    QDateTime *tTime = new QDateTime();
    tTime->setDate(iDate);
    tTime->setTime(iTime);
    mTime = tTime;
}

//
// Operators
//

QDebug& iRail::operator<<(QDebug dbg, const LiveboardRequest& iRequest)
{
    dbg << "LiveboardRequest(in='" << iRequest.station() << "'";
    if (iRequest.timed())
        dbg << ", at='" << iRequest.time()->toString(Qt::DefaultLocaleShortDate) << "'";
    dbg << ")";

    return dbg.maybeSpace();
}

QDataStream& iRail::operator<<(QDataStream& iStream, const LiveboardRequest& iRequest)
{
    iStream << iRequest.mStation;
    iStream << iRequest.mTimed;
    if (iRequest.mTimed)
        iStream << *iRequest.mTime;

    return iStream;
}

QDataStream& iRail::operator>>(QDataStream& iStream, LiveboardRequest& iRequest)
{
    iStream >> iRequest.mStation;
    iStream >> iRequest.mTimed;
    if (iRequest.mTimed)
        iStream >> *iRequest.mTime;

    return iStream;
}

QDataStream &iRail::operator<<(QDataStream& iStream, const LiveboardRequestPointer& iRequest)
{
    iStream << (*iRequest);

    return iStream;
}

QDataStream &iRail::operator>>(QDataStream& iStream, LiveboardRequestPointer& iRequest)
{
    LiveboardRequest *tLiveboardRequest = new LiveboardRequest("dummy");
    iStream >> *tLiveboardRequest;
    iRequest = LiveboardRequestPointer(tLiveboardRequest);

    return iStream;
}
