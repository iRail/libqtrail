//
// Configuration
//

// Include guard
#ifndef LIVEBOARDREQUEST_H
#define LIVEBOARDREQUEST_H

// Includes
#include <QDebug>
#include <QObject>
#include <QString>
#include <QDateTime>
#include <QMetaEnum>
#include <QSharedPointer>
#include <QMetaType>

namespace iRail
{
    // TODO: use constCast()'s
    class LiveboardRequest : public QObject
    {
    Q_OBJECT
    Q_PROPERTY(QString station READ station CONSTANT)
    Q_PROPERTY(bool timed READ timed)
    Q_PROPERTY(QDateTime time READ time WRITE setTime)
    public:
        // Construction and destruction
        LiveboardRequest(const QString& iStation);
        ~LiveboardRequest();

        // Basic I/O
        QString station() const;
        bool timed() const;
        const QDateTime* time() const;
        void setTime(const QDateTime& iTime);
        void setTime(const QDate& iDate, const QTime& iTime);

        // Operators
        friend QDebug &operator<<(QDebug dbg, const LiveboardRequest& iLiveboardRequest);
        friend QDataStream &operator<<(QDataStream& iStream, const LiveboardRequest& iLiveboardRequest);
        friend QDataStream &operator>>(QDataStream& iStream, LiveboardRequest& iLiveboardRequest);

    private:
        QString mStation;
        bool mTimed;
        QDateTime *mTime;
    };

    typedef QSharedPointer<LiveboardRequest> LiveboardRequestPointer;

    QDebug &operator<<(QDebug dbg, const LiveboardRequest& iLiveboardRequest);
    QDataStream &operator<<(QDataStream& iStream, const LiveboardRequest& iLiveboardRequest);
    QDataStream &operator>>(QDataStream& iStream, LiveboardRequest& iLiveboardRequest);
    QDataStream &operator<<(QDataStream& iStream, const LiveboardRequestPointer& iLiveboardRequest);
    QDataStream &operator>>(QDataStream& iStream, LiveboardRequestPointer& iLiveboardRequest);
}

Q_DECLARE_METATYPE(iRail::LiveboardRequestPointer)

#endif // LIVEBOARDREQUEST_H
