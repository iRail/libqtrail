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
#include "api/data/stop.h"
#include "api/data/journey.h"
#include "api/containercache.h"

namespace iRail
{
    class JourneyList : public QAbstractListModel
    {
    Q_OBJECT
    private:
        // Construction and destruction
        Connection(const Stop& iDeparture, const Stop& iArrival, QObject* iParent = 0);
        ~Connection();
        friend class ContainerCache;

        // Basic I/O
    public:
        const Stop& departure() const;
        const Stop& arrival() const;

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
        const Stop& mDeparture;
        const Stop& mArrival;
        QList<Journey*> mJourneys;
    };

    typedef QSharedPointer<JourneyList> JourneyListPointer;

    QDataStream &operator<<(QDataStream& iStream, const JourneyList& iJourneyList);
    QDataStream &operator>>(QDataStream& iStream, JourneyList& iJourneyList);
}

Q_DECLARE_METATYPE(iRail::JourneyList)
Q_DECLARE_METATYPE(iRail::JourneyListPointer)

#endif // JOURNEYLIST_H
