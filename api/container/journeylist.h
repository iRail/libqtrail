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
#include <QAbstractListModel>
#include <QHash>
#include "api/exception.h"
#include "api/data/stop.h"
#include "api/data/journey.h"

namespace iRail
{
    class ContainerCache;

    class JourneyList : public QAbstractListModel
    {
    Q_OBJECT
    private:
        // Construction and destruction
        JourneyList(const Station::Id& iOrigin, const Station::Id& iDestination, QObject* iParent = 0);
        ~JourneyList();
        friend class ContainerCache;

        // Basic I/O
    public:
        const Stop& origin() const;
        const Stop& destination() const;

        // Model interface
        int rowCount(const QModelIndex& iParent = QModelIndex()) const;
        QVariant data(const QModelIndex& iIndex, int iRole = Qt::DisplayRole) const;

        // Operators
        friend QDataStream &operator<<(QDataStream& iStream, const JourneyList& iJourneyList);
        friend QDataStream &operator>>(QDataStream& iStream, JourneyList& iJourneyList);

    signals:
        // Data reply signals

        // Data processing methods
    private slots:

    private:
        // Member data
        QDateTime mTimestamp;
        Station::Id mOrigin, mDestination;
        QHash<Journey::Id, Journey*> mJourneys;
    };
}

#endif // JOURNEYLIST_H
