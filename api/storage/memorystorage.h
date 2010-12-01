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

        // Setters
    public slots:
        void setStations(const QMap<QString, StationPointer>& iStations, const QDateTime& iTimestamp);

        // Cache data
    private:
        QMap<QString, StationPointer>* mStations;
        QDateTime mStationsTimestamp;
    };
}

#endif // MEMORYSTORAGE_H
