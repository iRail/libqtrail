//
// Configuration
//

// Include guard
#ifndef CONTAINER_H
#define CONTAINER_H

// Includes
#include <QObject>
#include <QAbstractListModel>
#include <QList>
#include "data/station.h"

namespace iRail
{
    class ContainerCache;

    template <class Data>
    class Container : public QAbstractListModel
    {
    Q_OBJECT
    protected:
        // Construction and destruction
        Container(QObject* iParent = 0);
        virtual ~Container();
        friend class ContainerCache;

    public:
        // Basic I/O

        // Model interface
        int rowCount(const QModelIndex& iParent = QModelIndex()) const;
        QVariant data(const QModelIndex& iIndex, int iRole = Qt::DisplayRole) const;
        QModelIndex indexFromItem(const Data* iData) const;

        // Container interface
        virtual QHash<int, QByteArray> roleNames() const = 0;
        virtual QVariant data(Data* iData, int iRole = Qt::DisplayRole) const;
        virtual Data* cast(Data* iData) const;

        // Data handling
        //mergeData(QList<Data*> iData);
        void replaceData(QList<Data*> iData);

    private:
        // Member data
        QList<Data*> mData;
    };
}

#endif // CONTAINER_H
