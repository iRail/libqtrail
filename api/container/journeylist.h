//
// Configuration
//

// Include guard
#ifndef JOURNEYLIST_H
#define JOURNEYLIST_H

// Includes
#include <QObject>
#include <QMetaType>
#include <QSharedPointer>
#include <QString>
#include <QDateTime>
#include <QAbstractListModel>
#include "api/exception.h"
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
        const POI& departure() const;
        const POI& arrival() const;

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
        Q_DISABLE_COPY(JourneyList);

        // Member data
        QDateTime mTimestamp;
        const POI& mDeparture;
        const POI& mArrival;
        QList<Journey*> mJourneys;
    };

    typedef QSharedPointer<JourneyList> JourneyListPointer;

    QDataStream &operator<<(QDataStream& iStream, const JourneyList& iJourneyList);
    QDataStream &operator>>(QDataStream& iStream, JourneyList& iJourneyList);
}

Q_DECLARE_METATYPE(iRail::JourneyList)
Q_DECLARE_METATYPE(iRail::JourneyListPointer)

#endif // JOURNEYLIST_H
