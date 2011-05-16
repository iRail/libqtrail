//
// Configuration
//

// Include guard
#ifndef STATIONLIST_H
#define STATIONLIST_H

// Includes
#include <QObject>
#include <QMetaType>
#include <QString>
#include <QDateTime>
#include <QHash>
#include <QAbstractListModel>
#include "api/requesthelper.h"
#include "api/exception.h"
#include "api/data/station.h"
#include "api/container.h"

namespace iRail
{
    class StationList : public QAbstractListModel
    {
    Q_OBJECT
    public:
        // Construction and destruction
        StationList(QObject* iParent = 0);
        ~StationList();

        // Model interface pass-through
        int rowCount(const QModelIndex& iParent = QModelIndex()) const
        { return mContainer.rowCount(iParent); }
        QVariant data(const QModelIndex& iIndex, int iRole = Qt::DisplayRole) const
        { return mContainer.data(iIndex, iRole); }
        QModelIndex indexFromItem(const Station* iData) const
        { return mContainer.indexFromItem(iData); }

    public:
        // Basic I/O

    signals:
        // Data reply signals
        void success();
        void failure(const Exception& iException);

        // Data processing methods
    private slots:

    private:
        // Member data
        Container<Station> mContainer;
        QDateTime mTimestamp;
    };
}

#endif // STATIONLIST_H
