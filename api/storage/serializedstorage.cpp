//
// Configuration
//

// Includes
#include "serializedstorage.h"

// Namespaces
using namespace iRail;


//
// Construction and destruction
//

SerializedStorage::SerializedStorage() : MemoryStorage()
{
}


//
// Data I/O
//

void SerializedStorage::serialize(QDataStream& iStream)
{
    // Stations
    if (stations() != 0)
    {
        iStream << true;

        iStream << stationsTimestamp();

        iStream << stations()->count();
        QMap<QString, StationPointer>::const_iterator i;
        for (i = stations()->begin(); i != stations()->end(); ++i)
        {
            iStream << i.key();
            StationPointer tStation = i.value();
            tStation->operator <<(iStream);
        }
    }
    else
        iStream << false;

    // User lists
    iStream << userLists().size();
    QMap<QString, QList<QVariant> >::const_iterator i;
    for (i = userLists().begin(); i != userLists().end(); i++)
    {
        iStream << i.key();

        const QList<QVariant>& tUserList = i.value();
        iStream << tUserList.size();
        for (int j = 0; j < tUserList.size(); j++)
        {
            iStream << tUserList.at(j);
        }
    }
}

void SerializedStorage::deserialize(QDataStream& iStream)
{
    // Stations
    bool tHasStations;
    iStream >> tHasStations;
    if (tHasStations)
    {
        QDateTime tStationsTimestamp;
        iStream >> tStationsTimestamp;

        unsigned int tStationCount;
        iStream >> tStationCount;
        QMap<QString, StationPointer> tStations;
        for (unsigned int i = 0; i < tStationCount; i++)
        {
            QString key;
            iStream >> key;
            Station *value = new Station("dummy");
            value->operator >>(iStream);
            tStations.insert(key, StationPointer(value));
        }

        setStations(tStations, tStationsTimestamp);
    }

    // User lists
    int tUserLists;
    iStream >> tUserLists;
    for (int i = 0; i < tUserLists; i++)
    {
        QString tKey;
        iStream >> tKey;

        int tUserListEntries;
        iStream >> tUserListEntries;
        QList<QVariant> tValue;
        for (int j = 0; j < tUserListEntries; j++)
        {
            QVariant tUserListEntry;
            iStream >> tUserListEntry;
            tValue << tUserListEntry;
        }

        setUserList(tKey, tValue);
    }
}
