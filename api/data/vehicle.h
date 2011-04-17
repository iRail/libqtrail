//
// Configuration
//

// Include guard
#ifndef VEHICLE_H
#define VEHICLE_H

// Includes
#include <QObject>
#include <QSharedPointer>
#include <QMetaType>
#include <QString>
#include <QPair>
#include <QDebug>
#include <QDateTime>
#include "station.h"

namespace iRail
{
    class Vehicle : public QObject
    {
    Q_OBJECT
    Q_PROPERTY(QString id READ id CONSTANT)
    Q_PROPERTY(bool locatable READ locatable)
    Q_PROPERTY(Location location READ location WRITE setLocation)
    public:
        // Auxiliary types
        typedef QPair<qreal, qreal> Location;

        // Construction and destruction
        Vehicle(QString iId);
        ~Vehicle();

        // Basic I/O
        QString id() const;
        const Location* location() const;
        bool locatable() const;
        void setLocation(const Location& iLocation);

        // Operators
        friend QDataStream &operator<<(QDataStream& iStream, const Vehicle& iVehicle);
        friend QDataStream &operator>>(QDataStream& iStream, Vehicle& iVehicle);

    private:
        QString mId;
        bool mLocatable;
        Location* mLocation;
    };

    QDataStream &operator<<(QDataStream& iStream, const Vehicle& iVehicle);
    QDataStream &operator>>(QDataStream& iStream, Vehicle& iVehicle);
}

Q_DECLARE_METATYPE(iRail::Vehicle)

#endif // STATION_H
