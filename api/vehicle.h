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
        struct Stop
        {
            Stop()
            {
                delay = 0;
                platform = 0;
            }

            QString station;
            unsigned int delay;
            QDateTime datetime;
            int platform;

            // Operators
            friend QDataStream &operator<<(QDataStream& iStream, const Stop& iStop);
            friend QDataStream &operator>>(QDataStream& iStream, Stop& iStop);
        };

        // Construction and destruction
        Vehicle(QString iId);
        ~Vehicle();

        // Basic I/O
        QString id() const;
        const Location* location() const;
        bool locatable() const;
        void setLocation(const Location& iLocation);
        QList<Stop> stops() const;
        void setStops(const QList<Stop>& iStops);

        // Operators
        friend QDebug &operator<<(QDebug dbg, const Vehicle& iVehicle);
        friend QDataStream &operator<<(QDataStream& iStream, const Vehicle& iVehicle);
        friend QDataStream &operator>>(QDataStream& iStream, Vehicle& iVehicle);

    private:
        QString mId;
        bool mLocatable;
        Location* mLocation;
        QList<Stop> mStops;
    };

    typedef QSharedPointer<Vehicle> VehiclePointer;

    QDebug &operator<<(QDebug dbg, const Vehicle& iVehicle);
    QDataStream &operator<<(QDataStream& iStream, const Vehicle& iVehicle);
    QDataStream &operator>>(QDataStream& iStream, Vehicle& iVehicle);
    QDataStream &operator<<(QDataStream& iStream, const VehiclePointer& iVehicle);
    QDataStream &operator>>(QDataStream& iStream, VehiclePointer& iVehicle);
}

Q_DECLARE_METATYPE(iRail::VehiclePointer)
Q_DECLARE_METATYPE(iRail::Vehicle::Stop)

#endif // STATION_H