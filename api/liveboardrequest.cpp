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

QDebug& iRail::operator<<(QDebug dbg, const LiveboardRequest& iLiveboardRequest)
{
    dbg << "LiveboardRequest(in='" << iLiveboardRequest.station() << "'";
    if (iLiveboardRequest.timed())
        dbg << ", at='" << iLiveboardRequest.time()->toString(Qt::DefaultLocaleShortDate) << "'";
    dbg << ")";

    return dbg.maybeSpace();
}

QDataStream& iRail::operator<<(QDataStream& iStream, const LiveboardRequest& iLiveboardRequest)
{
    iStream << iLiveboardRequest.mStation;
    iStream << iLiveboardRequest.mTimed;
    if (iLiveboardRequest.mTimed)
        iStream << *iLiveboardRequest.mTime;

    return iStream;
}

QDataStream& iRail::operator>>(QDataStream& iStream, LiveboardRequest& iLiveboardRequest)
{
    iStream >> iLiveboardRequest.mStation;
    iStream >> iLiveboardRequest.mTimed;
    if (iLiveboardRequest.mTimed)
    {
        iLiveboardRequest.mTime = new QDateTime();
        iStream >> *iLiveboardRequest.mTime;
    }

    return iStream;
}

QDataStream &iRail::operator<<(QDataStream& iStream, const LiveboardRequestPointer& iLiveboardRequest)
{
    iStream << (*iLiveboardRequest);

    return iStream;
}

QDataStream &iRail::operator>>(QDataStream& iStream, LiveboardRequestPointer& iLiveboardRequest)
{
    LiveboardRequest *tLiveboardRequest = new LiveboardRequest("dummy");
    iStream >> *tLiveboardRequest;
    iLiveboardRequest = LiveboardRequestPointer(tLiveboardRequest);

    return iStream;
}
