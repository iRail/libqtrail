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

QDebug LiveboardRequest::operator<<(QDebug dbg) const
{
    dbg << "LiveboardRequest(in='" << station() << "'";
    if (timed())
        dbg << ", at='" << time()->toString(Qt::DefaultLocaleShortDate) << "'";
    dbg << ")";

    return dbg.maybeSpace();
}

QDataStream& LiveboardRequest::operator<<(QDataStream& iStream) const
{
    iStream << mStation;
    iStream << mTimed;
    if (mTimed)
        iStream << *mTime;

    return iStream;
}

QDataStream& LiveboardRequest::operator>>(QDataStream& iStream)
{
    iStream >> mStation;
    iStream >> mTimed;
    if (mTimed)
        iStream >> *mTime;

    return iStream;
}
