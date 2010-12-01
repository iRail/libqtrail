//
// Configuration
//

// Include guard
#ifndef STORAGE_H
#define STORAGE_H

// Includes
#include "station.h"
#include <QMap>

namespace iRail
{
    class Storage : public QObject
    {
    Q_OBJECT
        // Getters
    public:
        /*!
          This method fetches the list of stations from the storage.
          The actual object is returned, hence a copy should be taken
          and no changes should be applied to the returnet list iself.
          */
        virtual const QMap<QString, StationPointer>* stations() const = 0;
        virtual QDateTime stationsTimestamp() const = 0;

        // Setters
    public slots:
        /*!
          This method inserts a list of stations in the storage. The
          list is copied upon insertion.
          */
        virtual void setStations(const QMap<QString, StationPointer>& iStations, const QDateTime& iTimestamp) = 0;
    };
}

#endif // STORAGE_H
