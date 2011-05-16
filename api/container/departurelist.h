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
#include <QHash>
#include <QAbstractListModel>
#include "api/exception.h"
#include "api/requesthelper.h"
#include "api/data/station.h"
#include "api/data/departure.h"
#include "api/container.h"

namespace iRail
{
    class DepartureList : public QAbstractListModel
    {
    Q_OBJECT
    public:
        // Construction and destruction
        DepartureList(const Station::Id& iStationId, QObject* iParent = 0);
        ~DepartureList();

        // Model interface pass-through
        int rowCount(const QModelIndex& iParent = QModelIndex()) const
        { return mContainer.rowCount(iParent); }
        QVariant data(const QModelIndex& iIndex, int iRole = Qt::DisplayRole) const
        { return mContainer.data(iIndex, iRole); }
        QModelIndex indexFromItem(const Departure* iData) const
        { return mContainer.indexFromItem(iData); }

        // Basic I/O
    public:
        Station::Id const* stationId() const;

        // Data request methods
        void fetch();
        void fetch(const QDateTime& iDatetime);

    signals:
        // Data reply signals
        void success();
        void failure(const Exception& iException);

        // Data processing methods
    private slots:
        void process();

    private:
        // Member data
        Container<Departure> mContainer;
        RequestHelper mRequestHelper;
        QDateTime mTimestamp;
        Station::Id mStationId;
    };
}

#endif // LIVEBOARD_H
