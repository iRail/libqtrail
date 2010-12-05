//
// Configuration
//

// Include guard
#ifndef MEMORYSTORAGE_H
#define MEMORYSTORAGE_H

// Includes
#include "api/storage.h"
#include "api/station.h"
#include <QMap>
#include <QDateTime>

namespace iRail
{
    class MemoryStorage : public Storage
    {
    Q_OBJECT
    public:
        // Construction and destruction
        MemoryStorage();

        // Getters
        const QMap<QString, StationPointer>* stations() const;
        QDateTime stationsTimestamp() const;
        void clearStations();
        const QList<QVariant>& favourites() const;
        void clearFavourites();
        const QList<QVariant>& history() const;
        void clearHistory();

        // Setters
    public slots:
        void setStations(const QMap<QString, StationPointer>& iStations, const QDateTime& iTimestamp);
        void setFavourites(const QList<QVariant> &iFavourites);
        void setHistory(const QList<QVariant> &iHistory);

        // Cache data
    private:
        QMap<QString, StationPointer>* mStations;
        QDateTime mStationsTimestamp;
        QList<QVariant> mHistory, mFavourites;
    };
}

#endif // MEMORYSTORAGE_H
