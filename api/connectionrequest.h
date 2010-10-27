//
// Configuration
//

// Include guard
#ifndef CONNECTIONREQUEST_H
#define CONNECTIONREQUEST_H

// Includes
#include <QObject>
#include <QSharedPointer>
#include <QMetaType>
#include <QString>
#include <QDateTime>
#include <QDebug>

namespace iRail
{
    // TODO: use constCast()'s
    // TODO typeoftransport
    class ConnectionRequest : public QObject
    {
    Q_OBJECT
    Q_PROPERTY(QString origin READ origin CONSTANT)
    Q_PROPERTY(QString destination READ destination CONSTANT)
    // TODO: howto handle optional properties (DateTime)?
    Q_ENUMS(TimeType)
    public:
        // Construction and destruction
        ConnectionRequest(const QString& iOrigin, const QString& iDestination);
        ~ConnectionRequest();

        enum TimeType
        {
            Departure,
            Arrival
        };

        struct Time
        {
            TimeType type;
            QDateTime datetime;
        };

        // Basic I/O
        QString origin() const;  // TODO: these should be StationPointers...
        QString destination() const;
        bool timed() const;
        const Time* time() const;
        void setTime(const Time& iTime);
        void setTime(const TimeType& iTimeType, const QDate& iDate, const QTime& iTime);

        // Debugging
        friend QDebug operator<<(QDebug dbg, const ConnectionRequest &iConnectionRequest);

    private:
        QString mOrigin, mDestination;
        bool mTimed;
        const Time *mTime;
    };

    typedef QSharedPointer<ConnectionRequest> ConnectionRequestPointer;
}

Q_DECLARE_METATYPE(iRail::ConnectionRequestPointer)

#endif // CONNECTIONREQUEST_H
