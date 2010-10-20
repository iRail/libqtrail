//
// Configuration
//

// Include guard
#ifndef STORAGE_H
#define STORAGE_H

// Includes
#include "station.h"
#include <QList>

namespace iRail
{
    class Storage : public QObject
    {
    Q_OBJECT
    public:
        // Getters
        // TODO: the cache _should_ be data agnostic...
        virtual QList<StationPointer>* stations() const = 0;

        // Setters
        // TODO: document that setters take ownership by taking a copy
    public slots:
        virtual void setStations(const QList<StationPointer>& iStations) = 0;
    };
}

#endif // STORAGE_H
