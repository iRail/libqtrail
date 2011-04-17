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

        // Auxiliary structures
        enum Roles {
          IdRole = Qt::UserRole+1,
          LocatableRole,
          LocationRole
        };

        // Construction and destruction
        Vehicle(QString iId);
        ~Vehicle();

        // Basic I/O
        QString id() const;
        const Location* location() const;
        bool locatable() const;
        void setLocation(const Location& iLocation);

        // Operators
        friend bool operator==(const Vehicle& lhs, const Vehicle& rhs);
        friend bool operator||(const Vehicle& lhs, const Vehicle& rhs);
        friend QDataStream& operator<<(QDataStream& iStream, const Vehicle& iVehicle);
        friend QDataStream& operator>>(QDataStream& iStream, Vehicle& iVehicle);

    private:
        Q_DISABLE_COPY(Vehicle);
        QString mId;
        bool mLocatable;
        Location* mLocation;
    };

    bool operator==(const Vehicle& lhs, const Vehicle& rhs);
    bool operator||(const Vehicle& lhs, const Vehicle& rhs);
    QDataStream& operator<<(QDataStream& iStream, const Vehicle& iVehicle);
    QDataStream& operator>>(QDataStream& iStream, Vehicle& iVehicle);
}

Q_DECLARE_METATYPE(iRail::Vehicle)

#endif // STATION_H
