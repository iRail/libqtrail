//
// Configuration
//

// Include guard
#ifndef CONTAINER_H
#define CONTAINER_H

// Includes
#include <QObject>
#include <QList>
#include <QAbstractListModel>

namespace iRail
{
    class ContainerCache;

    template <class Data>
    class Container
    {
    public:
        // Construction and destruction
        Container(QAbstractListModel* iModel, QObject* iParent = 0);
        virtual ~Container();

    public:
        // Basic I/O

        // Model interface
        int rowCount(const QModelIndex& iParent = QModelIndex()) const;
        QVariant data(const QModelIndex& iIndex, int iRole = Qt::DisplayRole) const;
        QModelIndex indexFromItem(const Data* iData) const;

        // Data handling
        //mergeData(QList<Data*> iData);
        void replaceData(QList<Data*> iData);

    private:
        // Member data
        QAbstractListModel* mModel;
        QList<Data*> mData;
    };
}

#endif // CONTAINER_H
