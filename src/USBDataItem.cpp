#include <QStringList>
#include "USBDataModel.hpp"
#include "USBDataItem.hpp"

USBDataItem::USBDataItem(const QString &Timestamp, unsigned char char_pid, const QString &Pid, const QString &Addr, const QString &Endpoint, const QString &CRC, const QString &FrameNumber, quint64 DataLen, const QString &Data,  USBDataModel *model)
{
	mp_model = model;
    m_Timestamp = Timestamp;
    m_Pid = Pid;
    m_Addr = Addr;
    m_Endpoint = Endpoint;
    m_CRC = CRC;
    m_FrameNumber = FrameNumber;
    m_DataLen = DataLen;
    m_Data = Data;
    m_charPid = char_pid;
}



USBDataItem::~USBDataItem()
{
}

int USBDataItem::columnCount() const
{
    return USBDataModel::m_columns.count();
}

QVariant USBDataItem::data(int column) const
{
	if (column == 0) {
        return m_Timestamp;
	}
	else if (column == 1) {
        return m_Pid;
	}
	else if (column == 2) {
        return m_Addr;
	}
	else if (column == 3) {
        return m_Endpoint;
	}
	else if (column == 4) {
        return m_CRC;
	}
	else if (column == 5) {
        return m_FrameNumber;
	}
    else if (column == 6) {
        return m_DataLen;
    }
    else if (column == 7) {
        return m_Data;
    }
	return QVariant();
}


int USBDataItem::row() const
{
    return 0;
}
