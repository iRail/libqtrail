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
        const QList<QVariant>& userList(const QString &iName) const;
        void clearUserList(const QString &iName);

        // Setters
    public slots:
        void setStations(const QMap<QString, StationPointer>& iStations, const QDateTime& iTimestamp);
        void setUserList(const QString &iName, const QList<QVariant> &iData);

        // Protected getters
    protected:
        const QMap<QString, QList<QVariant> >& userLists() const;

        // Cache data
    private:
        QMap<QString, StationPointer>* mStations;
        QDateTime mStationsTimestamp;
        QMap<QString, QList<QVariant> > mUserLists;
    };
}

#endif // MEMORYSTORAGE_H
