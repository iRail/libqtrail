//
// Configuration
//

// Include guard
#ifndef CONNECTIONLIST_H
#define CONNECTIONLIST_H

// Includes
#include <QObject>
#include <QMetaType>
#include <QString>
#include <QDateTime>
#include <QHash>
#include <QAbstractListModel>
#include "api/exception.h"
#include "api/data/connection.h"
#include "api/data/journey.h"
#include "api/container.h"

namespace iRail
{
    class ConnectionList : public QAbstractListModel
    {
    Q_OBJECT
    public:
        // Construction and destruction
        ConnectionList(const Journey::Id& iJourney, QObject* iParent = 0);
        ~ConnectionList();

        // Model interface pass-through
        int rowCount(const QModelIndex& iParent = QModelIndex()) const
        { return mContainer.rowCount(iParent); }
        QVariant data(const QModelIndex& iIndex, int iRole = Qt::DisplayRole) const
        { return mContainer.data(iIndex, iRole); }
        QModelIndex indexFromItem(const Connection* iData) const
        { return mContainer.indexFromItem(iData); }

        // Basic I/O
    public:
        Journey::Id const* journeyId() const;

    private:
        // Member data
        Container<Connection> mContainer;
        QDateTime mTimestamp;
        Journey::Id mJourneyId;
    };
}

#endif // CONNECTIONLIST_H
