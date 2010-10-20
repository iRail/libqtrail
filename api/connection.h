//
// Configuration
//

// Include guard
#ifndef CONNECTION_H
#define CONNECTION_H

// Includes
#include <QObject>
#include <QSharedPointer>
#include <QMetaType>
#include <QString>
#include <QPair>
#include <QDateTime>
#include <QDebug>

namespace iRail
{
    // TODO: use constCast()'s

    class Connection : public QObject
    {
    Q_OBJECT
    Q_PROPERTY(Transfer transfer READ transfer CONSTANT)
    // TODO: howto handle optional properties (location)?
    // TODO: howto handle lists?
    public:
        // Auxiliary types
        enum POIType
        {
            Arrival,
            Departure
        };
        struct POI
        {
            POIType type;
            QString station;    // TODO: StationPointer, but we must have an ApiCache for this
            QString vehicle;    // TODO: VehiclePointer?
            unsigned int platform;
            unsigned int delay;

            QDateTime datetime;
        };
        struct Transfer
        {
            POI arrival;
            POI departure;
        };

        // Construction and destruction
        Connection(const Transfer& iTransfer);
        ~Connection();

        // Basic I/O
        Transfer transfer() const;
        QList<Transfer> transfers() const;
        void setTransfers(const QList<Transfer>& iTransfers);

        // Debugging
        friend QDebug operator<<(QDebug dbg, const Connection &iConnection);

    private:
        Transfer mTransfer;
        QList<Transfer> mTransfers;
    };

    typedef QSharedPointer<Connection> ConnectionPointer;
}

Q_DECLARE_METATYPE(iRail::ConnectionPointer)

#endif // CONNECTION_H
