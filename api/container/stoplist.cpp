//
// Configuration
//

// Includes
#include "stoplist.h"
#include <QString>

// Namespaces
using namespace iRail;


//
// Construction and destruction
//

StopList::StopList(const Vehicle& iVehicle, QObject* iParent) : mVehicle(iVehicle), QAbstractListModel(iParent)
{
    qRegisterMetaType<StopList>("StopList");
    qRegisterMetaType<StopListPointer>("StopListPointer");

    QHash<int, QByteArray> tRoleNames;
    tRoleNames[Stop::StationRole] = "station";
    tRoleNames[Stop::DatetimeRole] = "datetime";
    tRoleNames[Stop::DelayRole] = "delay";
    tRoleNames[Stop::PlatformRole] = "platform";
    setRoleNames(tRoleNames);
}

StopList::~Connection()
{
}


//
// Basic I/O
//

const Vehicle& StopList::vehicle() const
{
    return mVehicle;
}


//
// Model interface
//

int StopList::rowCount(const QModelIndex& iParent) const
{
    return mStops.size();
}

QVariant StopList::data(const QModelIndex& iIndex, int iRole) const
{
    if (!iIndex.isValid())
        return QVariant();
    if (iIndex.row() > (mStops.size()-1) )
        return QVariant();

    Stop* oStop = mStops.at(iIndex.row());
    switch (iRole)
    {
    case Qt::DisplayRole:
    case Stop::StationRole:
        return QVariant::fromValue(oStop->station());
    case Stop::DatetimeRole:
        return QVariant::fromValue(oStop->datetime());
    case Stop::DelayRole:
        return QVariant::fromValue(oStop->delay());
    case Stop::PlatformRole:
        return QVariant::fromValue(oStop->platform());
    default:
        return QVariant();
    }
}


//
// Operators
//

QDataStream& iRail::operator<<(QDataStream& iStream, const StopList& iStopList)
{
    iStream << iStopList.mVehicle;

    iStream << iStopList.mStops.size();
    foreach (Stop* tStop, iStopList.mStops)
        iStream << *tStop;

    return iStream;
}

QDataStream& iRail::operator>>(QDataStream& iStream, StopList& iStopList)
{
    iStream >> iStopList.mVehicle;

    int tStopCount;
    iStream >> tStopCount;
    Q_ASSERT(iStopList.mStops.size() == 0);
    for (int i = 0; i < tStopCount; i++)
    {
        Stop* tStop;
        iStream >> *tStop;
        iStopList.mStops << tStop;
    }

    return iStream;
}
