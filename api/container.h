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

namespace iRail
{
    class ContainerCache;

    template <class Data>
    class Container : public QAbstractListModel
    {
    protected:
        // Construction and destruction
        Container(QObject* iParent = 0);
        virtual ~Container();

    public:
        // Basic I/O
        void append(Data* iData);

    public:
        // Model interface
        int rowCount(const QModelIndex& iParent = QModelIndex()) const;
        Data* object(const QModelIndex& iIndex) const;
        QVariant data(const QModelIndex& iIndex, int iRole = Qt::DisplayRole) const;
        QModelIndex indexFromItem(const Data* iData) const;

        // Data handling
        void clear();
        //mergeData(QList<Data*> iData);
        void replaceData(QList<Data*> iData);

    protected:
        // Member data
        QList<Data*> mData;
    };
}

#endif // CONTAINER_H
