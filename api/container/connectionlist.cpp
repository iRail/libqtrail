//
// Configuration
//

// Includes
#include "connectionlist.h"
#include <QString>

// Namespaces
using namespace iRail;


//
// Construction and destruction
//

ConnectionList::ConnectionList(const Journey::Id& iJourneyId, QObject* iParent) : mJourneyId(iJourneyId), QAbstractListModel(iParent)
{
    qRegisterMetaType<ConnectionList>("ConnectionList");
    qRegisterMetaType<ConnectionListPointer>("ConnectionListPointer");

    QHash<int, QByteArray> tRoleNames;
    tRoleNames[Connection::OriginRole] = "origin";
    tRoleNames[Connection::DestinationRole] = "destination";
    tRoleNames[Connection::TerminusRole] = "terminus";
    tRoleNames[Connection::VehicleRole] = "vehicle";
    tRoleNames[Connection::DelayRole] = "delay";
    setRoleNames(tRoleNames);
}

ConnectionList::~ConnectionList()
{
    qDeleteAll(mConnections.values());
    mConnections.clear();
}


//
// Basic I/O
//

const Journey& ConnectionList::journeyId() const
{
    return mJourneyId;
}


//
// Model interface
//

int ConnectionList::rowCount(const QModelIndex& iParent) const
{
    return mConnections.size();
}

QVariant ConnectionList::data(const QModelIndex& iIndex, int iRole) const
{
    if (!iIndex.isValid())
        return QVariant();
    if (iIndex.row() > (mDepartures.size()-1) )
        return QVariant();

    // TODO: sort through virtual mapping structure
    Connection* oConnections = mConnections.values().at(iIndex.row());
    switch (iRole)
    {
    case Qt::DisplayRole:
    case Connection::VehicleRole:
        return QVariant::fromValue(oConnections->vehicle());
    case Connection::OriginRole:
        return QVariant::fromValue(oConnections->departure());
    case Connection::DestinationRole:
        return QVariant::fromValue(oConnections->arrival());
    case Connection::TerminusRole:
        return QVariant::fromValue(oConnections->terminus());
    case Connection::DelayRole:
        return QVariant::fromValue(oConnections->delay());
    default:
        return QVariant();
    }
}
