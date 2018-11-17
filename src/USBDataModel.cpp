#include "USBDataItem.hpp"
#include "USBDataModel.hpp"

#include <QStringList>

USBDataModel::USBDataModel(QObject *parent)
    : QAbstractItemModel(parent)
{
    QList<QVariant> rootData;
    rootData << "Title" << "Summary";
    rootItem = new USBDataItem("", "", 0, "", "", "", nullptr);
}

USBDataModel::~USBDataModel()
{
    delete rootItem;
}

int USBDataModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return static_cast<USBDataItem*>(parent.internalPointer())->columnCount();
    else
        return rootItem->columnCount();
}

QVariant USBDataModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role != Qt::DisplayRole)
        return QVariant();

	USBDataItem *item = static_cast<USBDataItem *>(index.internalPointer());

    return item->data(index.column());
}

Qt::ItemFlags USBDataModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return 0;

    return QAbstractItemModel::flags(index);
}

QVariant USBDataModel::headerData(int section, Qt::Orientation orientation,
                               int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
        return rootItem->data(section);

    return QVariant();
}

QModelIndex USBDataModel::index(int row, int column, const QModelIndex &parent)
            const
{
    if (!hasIndex(row, column, parent))
        return QModelIndex();

	USBDataItem *parentItem;

    if (!parent.isValid())
        parentItem = rootItem;
    else
        parentItem = static_cast<USBDataItem *>(parent.internalPointer());

	USBDataItem *childItem = parentItem->child(row);
    if (childItem)
        return createIndex(row, column, childItem);
    else
        return QModelIndex();
}

QModelIndex USBDataModel::parent(const QModelIndex &index) const
{
    if (!index.isValid())
        return QModelIndex();

	USBDataItem *childItem = static_cast<USBDataItem *>(index.internalPointer());
	USBDataItem *parentItem = childItem->parentItem();

    if (parentItem == rootItem)
        return QModelIndex();

    return createIndex(parentItem->row(), 0, parentItem);
}

int USBDataModel::rowCount(const QModelIndex &parent) const
{
	USBDataItem *parentItem;
    if (parent.column() > 0)
        return 0;

    if (!parent.isValid())
        parentItem = rootItem;
    else
        parentItem = static_cast<USBDataItem *>(parent.internalPointer());

    return parentItem->childCount();
}

void USBDataModel::setupModelData(const QStringList &lines, USBDataItem *parent)
{
   
}