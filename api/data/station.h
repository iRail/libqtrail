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
        struct IId : Data::Id
        {
            QString guid;

            // Operator implementation
            bool equals(const Data::Id& id) const;
            unsigned int hash() const;
        };
        enum Roles
        {
            IdRole = Qt::UserRole+1,
            NameRole,
            LocationRole
        };

        // Construction and destruction
        Station(IId iId);
        ~Station();

        // Basic I/O
        Data::Id& id() const;
        QString name() const;
        void setName(const QString& iName);
        const Location& location() const;
        void setLocation(const Location& iLocation);

        // Operator implementation
        bool equals(const Data& data) const;
        Data& assign(const Data& data);
        friend QDataStream& operator<<(QDataStream& iStream, const Station& iStation);
        friend QDataStream& operator>>(QDataStream& iStream, Station& iStation);

    private:
        IId mId;
        QString mName;
        Location mLocation;
    };

    QDataStream& operator<<(QDataStream& iStream, const Station& iStation);
}

#endif // STATION_H
