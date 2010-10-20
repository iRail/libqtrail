//
// Configuration
//

// Include guard
#ifndef MEMORYSTORAGE_H
#define MEMORYSTORAGE_H

// Includes
#include "api/storage.h"
#include "api/station.h"
#include <QList>

namespace iRail
{
    class MemoryStorage : public Storage
    {
    Q_OBJECT
    public:
        // Construction and destruction
        MemoryStorage();

        // Getters
        const QList<StationPointer>& stations_get() const throw(StorageException);

        // Setters
    public slots:
        void stations_set(const QList<StationPointer>& iStations) throw(StorageException);

        // Cache data
    private:
        QList<StationPointer>* mStations;
    };
}

#endif // MEMORYSTORAGE_H
