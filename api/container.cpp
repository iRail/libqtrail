//
// Configuration
//

// Includes
#include "container.h"

// Namespaces
using namespace iRail;


//
// Construction and destruction
//


Container::Container(QObject *iParent) : QAbstractListModel(iParent)
{
    setRoleNames(roleNames());
}


//
// Model interface
//

int Container::rowCount(const QModelIndex& iParent) const
{
    Q_UNUSED(iParent);
    return mDataIds.size();
}

QVariant Container::data(const QModelIndex& iIndex, int iRole) const
{
    if (!iIndex.isValid())
        return QVariant();
    if (iIndex.row() > (mDataIds.size()-1) )
        return QVariant();

    Data::AbstractId tDataId = mDataIds.at(iIndex.row());
    Data* tData = mData.value(tDataId);

    return data(tData, iRole);
}

QModelIndex Container::indexFromItem(const Data* iData) const
{
    Q_ASSERT(iData);
    for(int tRow = 0; tRow < mDataIds.size(); ++tRow)
    {
      if(mDataIds.at(tRow) == iData->id())
          return index(tRow);
    }
    return QModelIndex();
}

void Container::mergeNarrow(QHash<Data::AbstractId, Data*>& iDataNew)
{
    // Process the new data
    QList<Station::Id> tDataRemoved = mDataIds, tDataAdded;
    foreach (Data::AbstractId tId, iDataNew.keys())
    {
        // Item already present, check if we need to update it
        if (mDataIds.contains(tId))
        {
            if (mData[tId] != iDataNew[tId])
            {
                (*mData[tId]) = *(iDataNew[tId]);

                // TODO: we only can change objects through fetches. Maybe make them all immutable?
                QModelIndex tIndex = indexFromItem(mData[tId]);
                if(tIndex.isValid())
                  emit dataChanged(tIndex, tIndex);
            }
            tDataRemoved.removeOne(tId);
        }

        // Station not yet present, add it later in a batch
        else
            tDataAdded << tId;
    }

    // Add new items
    beginInsertRows(QModelIndex(), rowCount(), rowCount()+tDataAdded.size()-1);
    foreach (Data::AbstractId tId, tDataAdded)
    {
        mDataIds.append(tId);
        mData.insert(tId, iDataNew.take(tId));
    }
    endInsertRows();

    // Delete used or removed items
    foreach (Data::AbstractId tId, iDataNew.keys())
        delete iDataNew.take(tId);
    foreach (Data::Id tId, tDataRemoved)
    {
        QModelIndex tIndex = indexFromItem(mStations[tId]);
        beginRemoveRows(QModelIndex(), tIndex.row(), tIndex.row());
        delete mData.take(tId);
        endRemoveRows();
    }
}
