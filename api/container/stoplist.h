//
// Configuration
//

// Include guard
#ifndef STOPLIST_H
#define STOPLIST_H

// Includes
#include <QObject>
#include <QMetaType>
#include <QSharedPointer>
#include <QString>
#include <QDateTime>
#include <QAbstractListModel>
#include "api/exception.h"
#include "api/data/vehicle.h"
#include "api/data/connection.h"
#include "api/data/poi.h"

namespace iRail
{
    class StopList : public QAbstractListModel
    {
    Q_OBJECT
    public:
        // Construction and destruction
        StopList(const Vehicle& iVehicle, QObject* iParent = 0);
        ~StopList();

        // Basic I/O
        Vehicle vehicle() const;

        // Model interface
        int rowCount(const QModelIndex& iParent = QModelIndex()) const;
        QVariant data(const QModelIndex& iIndex, int iRole = Qt::DisplayRole) const;

        // Operators
        friend QDataStream &operator<<(QDataStream& iStream, const StopList& iStopList);
        friend QDataStream &operator>>(QDataStream& iStream, StopList& iStopList);

    signals:
        // Data reply signals

        // Data processing methods
    private slots:

    private:
        Q_DISABLE_COPY(StopList);

        // Member data
        const Vehicle& mVehicle;
        QList<POI*> mStops;
    };

    typedef QSharedPointer<StopList> StopListPointer;

    QDataStream &operator<<(QDataStream& iStream, const StopList& iStopList);
    QDataStream &operator>>(QDataStream& iStream, StopList& iStopList);
}

Q_DECLARE_METATYPE(iRail::StopList)
Q_DECLARE_METATYPE(iRail::StopListPointer)

#endif // STOPLIST_H
