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

ConnectionList::ConnectionList(const Journey& iJourney, QObject* iParent) : mJourney(iJourney), QAbstractListModel(iParent)
{
    qRegisterMetaType<ConnectionList>("ConnectionList");

    QHash<int, QByteArray> tRoleNames;
    tRoleNames[Connection::DepartureRole] = "departure";
    tRoleNames[Connection::ArrivalRole] = "arrival";
    tRoleNames[Connection::TerminusRole] = "terminus";
    tRoleNames[Connection::VehicleRole] = "vehicle";
    setRoleNames(tRoleNames);
}


//
// Basic I/O
//

const Journey& ConnectionList::journey() const
{
    return mJourney;
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

    Connection* oConnections = mConnections.at(iIndex.row());
    switch (iRole)
    {
    case Qt::DisplayRole:
    case Connection::VehicleRole:
        return QVariant::fromValue(oConnections->vehicle());
    case Connection::DepartureRole:
        return QVariant::fromValue(oConnections->departure());
    case Connection::ArrivalRole:
        return QVariant::fromValue(oConnections->arrival());
    case Connection::TerminusRole:
        return QVariant::fromValue(oConnections->terminus());
    default:
        return QVariant();
    }
}


//
// Operators
//

QDataStream& iRail::operator<<(QDataStream& iStream, const ConnectionList& iConnectionList)
{
    iStream << iConnectionList.mJourney;

    iStream << iConnectionList.mConnections.size();
    foreach (Connection* tConnection, iConnectionList.mConnections)
        iStream << *tConnection;

    return iStream;
}

QDataStream& iRail::operator>>(QDataStream& iStream, ConnectionList& iConnectionList)
{
    iStream >> iConnectionList.mJourney;

    int tConnections;
    iStream >> tConnections;
    Q_ASSERT(iConnectionList.mConnections.size() == 0);
    for (int i = 0; i < tConnections; i++)
    {
        Connection* tConnection;
        iStream >> *tConnection;
        iConnectionList.mConnections << tConnection;
    }

    return iStream;
}

