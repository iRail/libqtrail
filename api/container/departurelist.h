//
// Configuration
//

// Include guard
#ifndef LIVEBOARD_H
#define LIVEBOARD_H

// Includes
#include <QObject>
#include <QMetaType>
#include <QString>
#include <QDateTime>
#include <QAbstractListModel>
#include <QHash>
#include "api/exception.h"
#include "api/requesthelper.h"
#include "api/data/station.h"
#include "api/data/departure.h"

namespace iRail
{
    class ContainerCache;

    class DepartureList : public QAbstractListModel
    {
    Q_OBJECT
    private:
        // Construction and destruction
        DepartureList(const Station::Id& iStationId, QObject* iParent = 0);
        ~DepartureList();
        friend class ContainerCache;

        // Basic I/O
    public:
        const Station::Id& stationId() const;

        // Model interface
        int rowCount(const QModelIndex& iParent = QModelIndex()) const;
        QVariant data(const QModelIndex& iIndex, int iRole = Qt::DisplayRole) const;

        // Data request methods
        void fetch();
        void fetch(const QDateTime& iDatetime);

        // Operators
        friend QDataStream &operator<<(QDataStream& iStream, const DepartureList& iDepartureList);
        friend QDataStream &operator>>(QDataStream& iStream, DepartureList& iDepartureList);

    signals:
        // Data reply signals
        void success();
        void failure(const Exception& iException);

        // Data processing methods
    private slots:
        void process();

    private:
        // Member data
        RequestHelper mRequestHelper;
        QDateTime mTimestamp;
        Station::Id mStationId;
        QHash<Departure::Id, Departure*> mDepartures;
    };
}

#endif // LIVEBOARD_H
