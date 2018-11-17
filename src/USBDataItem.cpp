#include <QStringList>

#include "USBDataItem.hpp"

USBDataItem::USBDataItem(const QString &Transfer, const QString &Time, unsigned int Device, const QString &Length, const QString &Setup, const QString &Data, USBDataItem *parent)
{
    m_parentItem = parent;
	m_Transfer = Transfer;
    m_Time = Time;
	m_Device = Device;
	m_Length = Length;
	m_Setup = Setup;
	m_Data = Data;
}

USBDataItem::~USBDataItem()
{
    qDeleteAll(m_childItems);
}

void USBDataItem::appendChild(USBDataItem *item)
{
    m_childItems.append(item);
}

USBDataItem *USBDataItem::child(int row)
{
    return m_childItems.value(row);
}

int USBDataItem::childCount() const
{
    return m_childItems.count();
}

int USBDataItem::columnCount() const
{
    return 6;
}

QVariant USBDataItem::data(int column) const
{
	if (column == 0) {
		return m_Transfer;
	}
	else if (column == 1) {
		return m_Time;
	}
	else if (column == 2) {
		return m_Device;
	}
	else if (column == 3) {
		return m_Length;
	}
	else if (column == 4) {
		return m_Setup;
	}
	else if (column == 5) {
		return m_Data;
	}
	return QVariant();
}

USBDataItem *USBDataItem::parentItem()
{
    return m_parentItem;
}

int USBDataItem::row() const
{
    if (m_parentItem)
        return m_parentItem->m_childItems.indexOf(const_cast<USBDataItem *>(this));

    return 0;
}