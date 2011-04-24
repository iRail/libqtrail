//
// Configuration
//

// Includes
#include "stationlist.h"
#include "api/reader/stationsreader.h"
#include <QString>

// Namespaces
using namespace iRail;


//
// Construction and destruction
//

StationList::StationList(QObject* iParent) : QAbstractListModel(iParent)
{
    QHash<int, QByteArray> tRoleNames;
    tRoleNames[Station::GUIDRole] = "guid";
    tRoleNames[Station::NameRole] = "name";
    tRoleNames[Station::LocationRole] = "location";
    setRoleNames(tRoleNames);
}

StationList::~StationList()
{
    qDeleteAll(mStations.values()); // TODO: neccesary?
}


//
// Model interface
//

int StationList::rowCount(const QModelIndex& iParent) const
{
    return mStationIds.size();
}

QVariant StationList::data(const QModelIndex& iIndex, int iRole) const
{
    if (!iIndex.isValid())
        return QVariant();
    if (iIndex.row() > (mStationIds.size()-1) )
        return QVariant();

    Station::Id tStationId = mStationIds.at(iIndex.row());
    Station* oStation = mStations.value(tStationId);
    switch (iRole)
    {
    case Station::GUIDRole:
        return QVariant::fromValue(oStation->id().guid);
    case Qt::DisplayRole:
    case Station::NameRole:
        return QVariant::fromValue(oStation->name());
    case Station::LocationRole:
        return QVariant::fromValue(oStation->location());
    default:
        return QVariant();
    }
}

QModelIndex StationList::indexFromItem(const Station* iStation) const
{
    Q_ASSERT(iStation);
    for(int tRow = 0; tRow < mStationIds.size(); ++tRow)
    {
      if(mStationIds.at(tRow) == iStation->id())
          return index(tRow);
    }
    return QModelIndex();
}


//
// Data request methods
//

void StationList::fetch()
{
    // Construct URL
    QUrl tURL = mRequestHelper.createBaseURL();
    tURL.setPath("stations/");

    // Create a request
    try
    {
        mRequestHelper.networkRequest(mRequestHelper.getRequest(tURL), this, SLOT(process()));
    }
    catch (NetworkException& iException)
    {
        emit failure(iException);
    }
}


//
// Data processing methods
//

void StationList::process()
{
    // Parse the data
    StationsReader tReader;
    try
    {
        tReader.read(mRequestHelper.networkReply());
    }
    catch (ParserException& iException)
    {
            emit failure(iException);
    }
    QHash<Station::Id, Station*> tStationsReceived = tReader.stations();

    // Process the stations
    QList<Station::Id> tStationsRemoved = mStationIds, tStationsAdded;
    foreach (Station::Id tId, tStationsReceived.keys())
    {
        // Station already present, check if we need to update the data
        if (mStationIds.contains(tId))
        {
            if (mStations[tId] != tStationsReceived[tId])
            {
                (*mStations[tId]) = *(tStationsReceived[tId]);

                QModelIndex tIndex = indexFromItem(mStations[tId]);
                if(tIndex.isValid())
                  emit dataChanged(tIndex, tIndex);
            }
            tStationsRemoved.removeOne(tId);
        }

        // Station not yet present, add it later in a batch
        else
            tStationsAdded << tId;
    }

    // Add new data
    beginInsertRows(QModelIndex(), rowCount(), rowCount()+tStationsAdded.size()-1);
    foreach (Station::Id tId, tStationsAdded)
    {
        mStationIds.append(tId);
        mStations.insert(tId, tStationsReceived.take(tId));
    }
    endInsertRows();

    // Delete used or removed data
    foreach (Station::Id tId, tStationsReceived.keys())
        delete tStationsReceived[tId];
    foreach (Station::Id tId, tStationsRemoved)
    {
        QModelIndex tIndex = indexFromItem(mStations[tId]);
        beginRemoveRows(QModelIndex(), tIndex.row(), tIndex.row());
        delete mStations.take(tId);
        endRemoveRows();
    }

    // Clean up
    mRequestHelper.networkCleanup();
    emit success();
}


//
// Operators
//

QDataStream& iRail::operator<<(QDataStream& iStream, const StationList& iStationList)
{
    iStream << iStationList.mStations.size();
    foreach (Station* tStation, iStationList.mStations)
        iStream << *tStation;

    return iStream;
}

QDataStream& iRail::operator>>(QDataStream& iStream, StationList& iStationList)
{
    int tStationCount;
    iStream >> tStationCount;
    Q_ASSERT(iStationList.mStations.size() == 0);
    for (int i = 0; i < tStationCount; i++)
    {
        Station* tStation;
        iStream >> *tStation;
        iStationList.mStations.insert(tStation->id(), tStation);
    }

    return iStream;
}
