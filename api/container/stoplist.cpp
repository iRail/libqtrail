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
    tRoleNames[POI::StationRole] = "station";
    tRoleNames[POI::DatetimeRole] = "datetime";
    tRoleNames[POI::DelayRole] = "delay";
    tRoleNames[POI::PlatformRole] = "platform";
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

    POI* oStop = mStops.at(iIndex.row());
    switch (iRole)
    {
    case Qt::DisplayRole:
    case POI::StationRole:
        return QVariant::fromValue(oStop->station());
    case POI::DatetimeRole:
        return QVariant::fromValue(oStop->datetime());
    case POI::DelayRole:
        return QVariant::fromValue(oStop->delay());
    case POI::PlatformRole:
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
    foreach (POI* tStop, iStopList.mStops)
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
        POI* tStop;
        iStream >> *tStop;
        iStopList.mStops << tStop;
    }

    return iStream;
}
