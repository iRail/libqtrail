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
#include <QAbstractItemModel>
#include "api/data/poi.h"
#include "api/data/journey.h"

namespace iRail
{
    class JourneyList : public QAbstractItemModel
    {
    Q_OBJECT
    public:
        // Construction and destruction
        Connection(const POI& iDeparture, const POI& iArrival);
        ~Connection();

        // Basic I/O
        POI departure() const;
        POI arrival() const;

        // Operators
        friend QDataStream &operator<<(QDataStream& iStream, const JourneyList& iJourneyList);
        friend QDataStream &operator>>(QDataStream& iStream, JourneyList& iJourneyList);

    private:
        QDateTime mTimestamp;
        POI mDeparture, mArrival;
        QList<Journey> mJourneys;
    };

    QDataStream &operator<<(QDataStream& iStream, const JourneyList& iJourneyList);
    QDataStream &operator>>(QDataStream& iStream, JourneyList& iJourneyList);
}

Q_DECLARE_METATYPE(iRail::JourneyList)

#endif // JOURNEYLIST_H