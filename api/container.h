//
// Configuration
//

// Include guard
#ifndef CONTAINER_H
#define CONTAINER_H

// Includes
#include <QObject>
#include <QAbstractListModel>
#include <QHash>
#include "api/data.h"

namespace iRail
{
    class ContainerCache;

    class Container : public QAbstractListModel
    {
    Q_OBJECT
    private:
        // Construction and destruction
        Container(QObject* iParent = 0);
        ~Container();
        friend class ContainerCache;

    public:
        // Basic I/O

        // Model interface
        int rowCount(const QModelIndex& iParent = QModelIndex()) const;
        QVariant data(const QModelIndex& iIndex, int iRole = Qt::DisplayRole) const;
        QModelIndex indexFromItem(const Station* iStation) const;
        void mergeNarrow(QHash<Data::AbstractId, Data*>& iData);

        // Container interface
        virtual QHash<int, QByteArray> roleNames() const = 0;
        virtual QVariant data(Data* iData, int iRole = Qt::DisplayRole) const;
        virtual Data* cast(Data* iData) const;

    private:
        // Member data
        QHash<Data::AbstractId, Data*> mData;
        QList<Data::AbstractId> mDataIds;
    };
}

#endif // CONTAINER_H
