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
#include "api/data/poi.h"
#include "api/data/journey.h"

namespace iRail
{
    class JourneyList : public QAbstractListModel
    {
    Q_OBJECT
    public:
        // Construction and destruction
        Connection(const POI& iDeparture, const POI& iArrival, QObject* iParent = 0);
        ~Connection();

        // Basic I/O
        POI departure() const;
        POI arrival() const;

        // Model interface
        int rowCount(const QModelIndex& iParent = QModelIndex()) const;
        QVariant data(const QModelIndex& iIndex, int iRole = Qt::DisplayRole) const;

        // Operators
        friend QDataStream &operator<<(QDataStream& iStream, const JourneyList& iJourneyList);
        friend QDataStream &operator>>(QDataStream& iStream, JourneyList& iJourneyList);

    private:
        Q_DISABLE_COPY(JourneyList);
        QDateTime mTimestamp;
        POI mDeparture, mArrival;
        QList<Journey*> mJourneys;
    };

    QDataStream &operator<<(QDataStream& iStream, const JourneyList& iJourneyList);
    QDataStream &operator>>(QDataStream& iStream, JourneyList& iJourneyList);
}

Q_DECLARE_METATYPE(iRail::JourneyList)

#endif // JOURNEYLIST_H
