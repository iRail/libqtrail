//
// Configuration
//

// Include guard
#ifndef STATION_H
#define STATION_H

// Includes
#include <QObject>
#include <QMetaType>
#include <QString>
#include <QPair>
#include <QHash>
#include "auxiliary/location.h"
#include "api/data.h"

namespace iRail
{
    class Station : public Data
    {
    Q_OBJECT
    Q_PROPERTY(QString name READ name WRITE setName)
    Q_PROPERTY(Location location READ location WRITE setLocation)
    public:
        // Auxiliary structures
        struct Id : AbstractId
        {
            QString guid;

            // Operator implementation
            bool equals(const AbstractId& id) const;
            unsigned int hash() const;

            // Operators
            friend QDataStream& operator<<(QDataStream& iStream, const Station::Id& iStationId);
            friend QDataStream& operator>>(QDataStream& iStream, Station::Id& iStationId);
        };
        enum Roles
        {
            GUIDRole = Qt::UserRole+1,
            NameRole,
            LocationRole
        };

        // Construction and destruction
        Station(Id iId);
        ~Station();

        // Basic I/O
        Id const* id() const;
        QString name() const;
        void setName(const QString& iName);
        Location const* location() const;
        void setLocation(const Location& iLocation);

        // Operator implementation
        bool equals(const Data& data) const;
        Data& assign(const Data& data);
        friend QDataStream& operator<<(QDataStream& iStream, const Station& iStation);
        friend QDataStream& operator>>(QDataStream& iStream, Station& iStation);

    private:
        Id mId;
        QString mName;
        Location mLocation;
    };

    QDataStream& operator<<(QDataStream& iStream, const Station& iStation);
    QDataStream& operator>>(QDataStream& iStream, Station& iStation);
    QDataStream& operator<<(QDataStream& iStream, const Station::Id& iStationId);
    QDataStream& operator>>(QDataStream& iStream, Station::Id& iStationId);
}

Q_DECLARE_METATYPE(const iRail::Station*)

#endif // STATION_H
