//
// Configuration
//

// Include guard
#ifndef LOCATION_H
#define LOCATION_H

// Includes
#include <QObject>
#include <QMetaType>
#include <QString>
#include <QPair>

namespace iRail
{
    class Location : public QObject
    {
    Q_OBJECT
    Q_PROPERTY(qreal longitude READ longitude WRITE setLongitude)
    Q_PROPERTY(qreal latitude READ latitude WRITE setLatitude)
    Q_PROPERTY(bool valid READ valid CONSTANT)
    public:
        // Construction and destruction
        Location(qreal iLongitude, qreal iLatitude);
        Location();
        ~Location();

        // Basic I/O
        qreal longitude() const;
        void setLongitude(qreal iLongitude);
        qreal latitude() const;
        void setLatitude(qreal iLatitude);
        bool valid() const;

        // Operators
        friend bool operator==(const Station& lhs, const Location& rhs);
        friend QDataStream& operator<<(QDataStream& iStream, const Location& iLocation);
        friend QDataStream& operator>>(QDataStream& iStream, Location& iLocation);

    private:
        Q_DISABLE_COPY(Location);
        qreal mLongitude, mLatitude;
        bool mLongitudeValid, mLatitudeValid;
    };

    bool operator==(const Station& lhs, const Location& rhs);
    QDataStream& operator<<(QDataStream& iStream, const Location& iLocation);
    QDataStream& operator>>(QDataStream& iStream, Location& iLocation);
}

Q_DECLARE_METATYPE(iRail::Location)

#endif // LOCATION_H
