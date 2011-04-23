//
// Configuration
//

// Include guard
#ifndef STATIONLIST_H
#define STATIONLIST_H

// Includes
#include <QObject>
#include <QMetaType>
#include <QSharedPointer>
#include <QString>
#include <QDateTime>
#include <QAbstractListModel>
#include <QHash>
#include "api/requesthelper.h"
#include "api/exception.h"
#include "api/data/station.h"
#include "api/containercache.h"

namespace iRail
{
    class StationList : public QAbstractListModel
    {
    Q_OBJECT
    private:
        // Construction and destruction
        StationList(QObject* iParent = 0);
        ~StationList();
        friend class ContainerCache;

    public:
        // Basic I/O

        // Model interface
        int rowCount(const QModelIndex& iParent = QModelIndex()) const;
        QVariant data(const QModelIndex& iIndex, int iRole = Qt::DisplayRole) const;

        // Data request methods
        void fetch();

        // Operators
        friend QDataStream &operator<<(QDataStream& iStream, const StationList& iStationList);
        friend QDataStream &operator>>(QDataStream& iStream, StationList& iStationList);

    signals:
        // Data reply signals
        void success();
        void failure(const Exception& iException);

        // Data processing methods
    private slots:
        void process();

    private:
        Q_DISABLE_COPY(StationList);

        // Member data
        RequestHelper mRequestHelper;
        QDateTime mTimestamp;
        QHash<Station::Id, Station*> mStations;
        QList<Station::Id> mStationIds;
    };

    typedef QSharedPointer<StationList> StationListPointer;

    QDataStream &operator<<(QDataStream& iStream, const StationList& iStationList);
    QDataStream &operator>>(QDataStream& iStream, StationList& iStationList);
}

Q_DECLARE_METATYPE(iRail::StationList)
Q_DECLARE_METATYPE(iRail::StationListPointer)

#endif // STATIONLIST_H
