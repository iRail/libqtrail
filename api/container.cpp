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
    return mData.size();
}

QVariant Container::data(const QModelIndex& iIndex, int iRole) const
{
    if (!iIndex.isValid())
        return QVariant();
    if (iIndex.row() > (mData.size()-1) )
        return QVariant();

    Data* tData = mData.at(iIndex.row());

    return data(tData, iRole);
}

QModelIndex Container::indexFromItem(const Data* iData) const
{
    Q_ASSERT(iData);
    for(int tRow = 0; tRow < mData.size(); ++tRow)
    {
      if(*mData.at(tRow)->id() == *iData->id())
          return index(tRow);
    }
    return QModelIndex();
}
