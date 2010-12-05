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

    // History and favourites: enumeration processing
    const QMetaObject& tMetaObject = SerializedStorage::staticMetaObject;
    int tEnumIndex = tMetaObject.indexOfEnumerator("VariantType");
    QMetaEnum tMetaEnum = tMetaObject.enumerator(tEnumIndex);

    // History
    iStream << history().size();
    for (int i = 0; i < history().size(); i++)
    {
        const QVariant& tHistoryEntry = history().at(i);

        if (tHistoryEntry.canConvert<LiveboardRequestPointer>())
        {
            iStream << tMetaEnum.valueToKey(LiveboardRequestType);
            iStream << tHistoryEntry.value<LiveboardRequestPointer>();
        }
        else if (tHistoryEntry.canConvert<ConnectionRequestPointer>())
        {
            iStream << tMetaEnum.valueToKey(ConnectionRequestType);
            iStream << tHistoryEntry.value<ConnectionRequestPointer>();
        }
        // else: warn
    }

    // Favourites
    iStream << favourites().size();
    for (int i = 0; i < favourites().size(); i++)
    {
        const QVariant& tFavouriteEntry = favourites().at(i);

        if (tFavouriteEntry.canConvert<LiveboardRequestPointer>())
        {
            iStream << tMetaEnum.valueToKey(LiveboardRequestType);
            iStream << tFavouriteEntry.value<LiveboardRequestPointer>();
        }
        else if (tFavouriteEntry.canConvert<ConnectionRequestPointer>())
        {
            iStream << tMetaEnum.valueToKey(ConnectionRequestType);
            iStream << tFavouriteEntry.value<ConnectionRequestPointer>();
        }
        // else: warn
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

    // History and favourites: enumeration processing
    const QMetaObject& tMetaObject = SerializedStorage::staticMetaObject;
    int tEnumIndex = tMetaObject.indexOfEnumerator("VariantType");
    QMetaEnum tMetaEnum = tMetaObject.enumerator(tEnumIndex);

    // History
    int tHistoryEntries;
    iStream >> tHistoryEntries;
    QList<QVariant> tHistory;
    for (int i = 0; i < tHistoryEntries; i++)
    {
        VariantType tType;
        char* tTypeValue;
        iStream >> tTypeValue;
        tType = static_cast<VariantType>(tMetaEnum.keyToValue(tTypeValue));

        QVariant tHistoryEntry;
        if (tType == LiveboardRequestType)
        {
            LiveboardRequestPointer tLiveboardRequest;
            iStream >> tLiveboardRequest;
            tHistoryEntry = QVariant::fromValue(tLiveboardRequest);
        }
        else if (tType == ConnectionRequestType)
        {
            ConnectionRequestPointer tConnectionRequest;
            iStream >> tConnectionRequest;
            tHistoryEntry = QVariant::fromValue(tConnectionRequest);
        }

        tHistory << tHistoryEntry;
    }
    setHistory(tHistory);

    // Favourites
    int tFavouritesEntries;
    iStream >> tFavouritesEntries;
    QList<QVariant> tFavourites;
    for (int i = 0; i < tFavouritesEntries; i++)
    {
        VariantType tType;
        char* tTypeValue;
        iStream >> tTypeValue;
        tType = static_cast<VariantType>(tMetaEnum.keyToValue(tTypeValue));

        QVariant tFavouritesEntry;
        if (tType == LiveboardRequestType)
        {
            LiveboardRequestPointer tLiveboardRequest;
            iStream >> tLiveboardRequest;
            tFavouritesEntry = QVariant::fromValue(tLiveboardRequest);
        }
        else if (tType == ConnectionRequestType)
        {
            ConnectionRequestPointer tConnectionRequest;
            iStream >> tConnectionRequest;
            tFavouritesEntry = QVariant::fromValue(tConnectionRequest);
        }

        tFavourites << tFavouritesEntry;
    }
    setFavourites(tFavourites);
}
