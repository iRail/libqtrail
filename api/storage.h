//
// Configuration
//

// Include guard
#ifndef STORAGE_H
#define STORAGE_H

// Includes
#include "station.h"
#include <QList>
#include "api/exception/storageexception.h"

namespace iRail
{
    class Storage : public QObject
    {
    Q_OBJECT
    public:
        // Basic IO
        virtual void load() throw(StorageException) {}
        virtual void save() throw(StorageException) {}

        // Getters
        // TODO: the cache _should_ be data agnostic...
        virtual const QList<StationPointer>& stations_get() const throw(StorageException) = 0;

        // Setters
    public slots:
        virtual void stations_set(const QList<StationPointer>& iStations) throw(StorageException) = 0;
    };
}

#endif // STORAGE_H
