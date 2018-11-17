#include <QStringList>

#include "USBDataItem.hpp"

USBDataItem::USBDataItem(const QString &Transfer, const QString &Time, unsigned int Device, const QString &Length, const QString &Setup, const QString &Data, USBDataModel *model)
{
	mp_model = model;
	m_Transfer = Transfer;
    m_Time = Time;
	m_Device = Device;
	m_Length = Length;
	m_Setup = Setup;
	m_Data = Data;
}

USBDataItem::~USBDataItem()
{
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


int USBDataItem::row() const
{
    return 0;
}