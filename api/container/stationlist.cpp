//
// Configuration
//

// Includes
#include "stationlist.h"
#include "api/reader/stationreader.h"
#include <QString>

// Namespaces
using namespace iRail;


//
// Construction and destruction
//

StationList::StationList(QObject* iParent) : QAbstractListModel(iParent)
{
    qRegisterMetaType<StationList>("StationList");
    qRegisterMetaType<StationListPointer>("StationListPointer");
    qRegisterMetaTypeStreamOperators<StationListPointer>("StationListPointer");

    QHash<int, QByteArray> tRoleNames;
    tRoleNames[Station::IdRole] = "id";
    tRoleNames[Station::NameRole] = "name";
    tRoleNames[Station::LocationRole] = "location";
    setRoleNames(tRoleNames);
}


StationList::~StationList()
{
    qDeleteAll(mStations.values());
    mStations.clear();
}


//
// Model interface
//

int StationList::rowCount(const QModelIndex& iParent) const
{
    return mStations.size();
}

QVariant StationList::data(const QModelIndex& iIndex, int iRole) const
{
    if (!iIndex.isValid())
        return QVariant();
    if (iIndex.row() > (mStations.size()-1) )
        return QVariant();

    // TODO: sort through virtual mapping structure
    Station* oStation = mStations.values().at(iIndex.row());
    switch (iRole)
    {
    case Station::IdRole:
        return QVariant::fromValue(oStation->id());
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
    for(int tRow = 0; tRow < mStations.size(); ++tRow)
    {
      if(mStations.values().at(tRow) == item)
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
        network_request(getRequest(tURL), this, SLOT(process()));
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
    StationReader tReader;
    try
    {
        tReader.read(mNetworkReply);
    }
    catch (ParserException& iException)
            emit failure(iException);
    QHash<Station::Id, Station*> tStationsNew = tReader.departures();

    // Process the stations
    QList<Station::Id> tStationsRemoved = mStations.keys();
    foreach (Station::Id tId, tStationsNew.keys())
    {
        if (mStations.contains(tId))
        {
            if (mStations[tId] != tStationsNew[tId])
            {
                // OPM: als een reader diepere wijzigingen kan veroorzaken (vb. een deel van de id()),
                // moet die ook veranderd worden. Hoe? aangzien const...
                (*mStations[tId]) = *(tStationsNew[tId]);

                QModelIndex tIndex = indexFromItem(mStations[tId]);
                if(tIndex.isValid())
                  emit dataChanged(tIndex, tIndex);
            }
            tStationsRemoved.removeOne(tId);
        }
        else
        {
            mStations.insert(tId, tStationsNew[tId]);
            tStationsNew.removeOne(tId);
        }
    }

    // Remove redundant or removed data
    foreach (Station::Id tId, tStationsNew.keys())
        delete tStationsNew[tId];
    foreach (Station::Id tId, tStationsRemoved.keys())
        delete mStations.take(tId);

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
        iJourneyList.mStations << tStation;
    }

    return iStream;
}
