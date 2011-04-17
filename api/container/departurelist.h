//
// Configuration
//

// Include guard
#ifndef LIVEBOARD_H
#define LIVEBOARD_H

// Includes
#include <QObject>
#include <QMetaType>
#include <QString>
#include <QDateTime>
#include <QAbstractListModel>
#include "api/exception.h"
#include "api/requesthelper.h"
#include "api/data/station.h"
#include "api/data/departure.h"

namespace iRail
{
    class DepartureList : public QAbstractListModel
    {
    Q_OBJECT
    public:
        // Construction and destruction
        DepartureList(const Station& iStation, QObject* iParent = 0);

        // Basic I/O
        const Station& station() const;

        // Model interface
        int rowCount(const QModelIndex& iParent = QModelIndex()) const;
        QVariant data(const QModelIndex& iIndex, int iRole = Qt::DisplayRole) const;

        // Data request methods
        void fetch();
        void fetch(const QDateTime& iDatetime);

        // Operators
        friend QDataStream &operator<<(QDataStream& iStream, const DepartureList& iDepartureList);
        friend QDataStream &operator>>(QDataStream& iStream, DepartureList& iDepartureList);

    signals:
        // Data reply signals
        void success();
        void failure(const Exception& iException);

        // Data processing methods
    private slots:
        void process();

    private:
        Q_DISABLE_COPY(DepartureList);

        // Member data
        RequestHelper mRequestHelper;
        QDateTime mTimestamp;
        const Station& mStation;
        QList<Departure*> mDepartures;
    };

    QDataStream &operator<<(QDataStream& iStream, const DepartureList& iDepartureList);
    QDataStream &operator>>(QDataStream& iStream, DepartureList& iDepartureList);
}

Q_DECLARE_METATYPE(iRail::DepartureList)

#endif // LIVEBOARD_H
