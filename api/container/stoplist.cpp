//
// Configuration
//

// Includes
#include "stoplist.h"
#include "api/reader/vehiclereader.h"
#include <QString>

// Namespaces
using namespace iRail;


//
// Construction and destruction
//

StopList::StopList(QObject *iParent) : QAbstractListModel(iParent)
{
    mVehicleId.guid = "anonymous";

    // TODO: remove duplicate code
    QHash<int, QByteArray> tRoleNames;
    tRoleNames[Stop::StationRole] = "station";
    tRoleNames[Stop::DatetimeRole] = "datetime";
    tRoleNames[Stop::PlatformRole] = "platform";
    setRoleNames(tRoleNames);
}

StopList::StopList(const Vehicle::Id& iVehicleId, QObject* iParent) : mVehicleId(iVehicleId), QAbstractListModel(iParent)
{
    QHash<int, QByteArray> tRoleNames;
    tRoleNames[Stop::StationRole] = "station";
    tRoleNames[Stop::DatetimeRole] = "datetime";
    tRoleNames[Stop::PlatformRole] = "platform";
    setRoleNames(tRoleNames);
}

StopList::~StopList()
{
    qDeleteAll(mStops.values());
    mStops.clear();
}


//
// Basic I/O
//

const Vehicle::Id& StopList::vehicleId() const
{
    return mVehicleId;
}


//
// Model interface
//

int StopList::rowCount(const QModelIndex& iParent) const
{
    Q_UNUSED(iParent);
    return mStops.size();
}

QVariant StopList::data(const QModelIndex& iIndex, int iRole) const
{
    if (!iIndex.isValid())
        return QVariant();
    if (iIndex.row() > (mStops.size()-1) )
        return QVariant();

    // TODO: sort through virtual mapping structure
    Stop* oStop = mStops.values().at(iIndex.row());
    switch (iRole)
    {
    case Qt::DisplayRole:
    case Stop::StationRole:
        return QVariant::fromValue(oStop->id().station);
    case Stop::DatetimeRole:
        return QVariant::fromValue(oStop->id().datetime);
    case Stop::PlatformRole:
        return QVariant::fromValue(oStop->platform());
    default:
        return QVariant();
    }
}
