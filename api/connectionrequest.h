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
    Q_PROPERTY(QString origin READ getOrigin CONSTANT)
    Q_PROPERTY(QString destination READ getDestination CONSTANT)
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

        struct DateTime
        {
            TimeType type;
            QDateTime datetime;
        };

        // Basic I/O
        QString getOrigin() const;  // TODO: these should be StationPointers...
        QString getDestination() const;
        bool hasDateTime() const;
        DateTime getDateTime() const;
        void setDateTime(const DateTime& iDateTime);
        void setDateTime(const TimeType& iTimeType, const QDate& iDate, const QTime& iTime);

        // Debugging
        friend QDebug operator<<(QDebug dbg, const ConnectionRequest &iConnectionRequest);

    private:
        QString mOrigin, mDestination;
        DateTime *mDateTime;
    };

    typedef QSharedPointer<ConnectionRequest> ConnectionRequestPointer;
}

Q_DECLARE_METATYPE(iRail::ConnectionRequestPointer)

#endif // CONNECTIONREQUEST_H
