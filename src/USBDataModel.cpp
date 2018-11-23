#include "USBDataItem.hpp"
#include "USBDataModel.hpp"

#include <QStringList>
#include <QDebug>



QStringList USBDataModel::m_columns = { "TIMESTAMP",
                              "PID",
                              "ADDR",
                              "ENDPOINT",
                              "CRC",
                              "FRAME_NUMBER",
                              "DATA_LEN",
                              "DATA"};

USBDataModel::USBDataModel(QObject *parent) : QAbstractTableModel(parent)
{
}

USBDataModel::~USBDataModel()
{
}

int USBDataModel::columnCount(const QModelIndex &parent) const
{
	return m_columns.count();
}


QVariant USBDataModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role != Qt::DisplayRole)
        return QVariant();

    const USBDataItem *item = m_items.at(index.row());

    return item->data(index.column());
}

Qt::ItemFlags USBDataModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return 0;

    return QAbstractItemModel::flags(index);
}

QVariant USBDataModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
        return m_columns.at(section);

    return QVariant();
}

QModelIndex USBDataModel::index(int row, int column, const QModelIndex &parent)
            const
{
    if (!hasIndex(row, column, parent))
        return QModelIndex();

    return createIndex(row, column, nullptr);
}

QModelIndex USBDataModel::parent(const QModelIndex &index) const
{
	return QModelIndex();
}

int USBDataModel::rowCount(const QModelIndex &parent) const
{
    return m_items.count();
}
