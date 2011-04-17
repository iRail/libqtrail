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
#include "api/exception.h"
#include "api/data/station.h"

namespace iRail
{
    class StationList : public QAbstractListModel
    {
    Q_OBJECT
    public:
        // Construction and destruction
        StationList(QObject* iParent = 0);
        ~StationList();

        // Model interface
        int rowCount(const QModelIndex& iParent = QModelIndex()) const;
        QVariant data(const QModelIndex& iIndex, int iRole = Qt::DisplayRole) const;

        // Operators
        friend QDataStream &operator<<(QDataStream& iStream, const StationList& iStationList);
        friend QDataStream &operator>>(QDataStream& iStream, StationList& iStationList);

    signals:
        // Data reply signals

        // Data processing methods
    private slots:

    private:
        Q_DISABLE_COPY(StationList);

        // Member data
        QDateTime mTimestamp;
        QMap<QString, Station*> mStations;
    };

    typedef QSharedPointer<StationList> StationListPointer;

    QDataStream &operator<<(QDataStream& iStream, const StationList& iStationList);
    QDataStream &operator>>(QDataStream& iStream, StationList& iStationList);
}

Q_DECLARE_METATYPE(iRail::StationList)
Q_DECLARE_METATYPE(iRail::StationListPointer)

#endif // STATIONLIST_H
