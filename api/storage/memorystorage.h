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

        // Setters
    public slots:
        void setStations(const QMap<QString, StationPointer>& iStations);

        // Cache data
    private:
        QMap<QString, StationPointer>* mStations;
    };
}

#endif // MEMORYSTORAGE_H
