//
// Configuration
//

// Include guard
#ifndef JOURNEYLIST_H
#define JOURNEYLIST_H

// Includes
#include <QObject>
#include <QMetaType>
#include <QString>
#include <QDateTime>
#include <QHash>
#include <QAbstractListModel>
#include "api/exception.h"
#include "api/data/journey.h"
#include "api/container.h"

namespace iRail
{
    class JourneyList : public QAbstractListModel
    {
    Q_OBJECT
    public:
        // Construction and destruction
        JourneyList(const Station::Id& iOrigin, const Station::Id& iDestination, QObject* iParent = 0);
        ~JourneyList();

        // Model interface pass-through
        int rowCount(const QModelIndex& iParent = QModelIndex()) const
        { return mContainer.rowCount(iParent); }
        QVariant data(const QModelIndex& iIndex, int iRole = Qt::DisplayRole) const
        { return mContainer.data(iIndex, iRole); }
        QModelIndex indexFromItem(const Journey* iData) const
        { return mContainer.indexFromItem(iData); }

        // Basic I/O
    public:
        Station::Id const* origin() const;
        Station::Id const* destination() const;

    signals:
        // Data reply signals

        // Data processing methods
    private slots:

    private:
        // Member data
        Container<Journey> mContainer;
        QDateTime mTimestamp;
        Station::Id mOrigin, mDestination;
    };
}

#endif // JOURNEYLIST_H
