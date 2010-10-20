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
        QList<StationPointer>* stations() const;

        // Setters
    public slots:
        void setStations(const QList<StationPointer>& iStations);

        // Cache data
    private:
        QList<StationPointer>* mStations;
    };
}

#endif // MEMORYSTORAGE_H
