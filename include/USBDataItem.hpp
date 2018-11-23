#pragma once
#include <QList>
#include <QVariant>
class USBDataModel;
class USBDataItem
{
public:
    explicit USBDataItem(const QString &Timestamp, const QString &Pid, const QString &Addr, const QString &Endpoint, const QString &CRC, const QString &FrameNumber, quint64 DataLen, const QString &Data, USBDataModel *model);
    ~USBDataItem();


    int columnCount() const;
    QVariant data(int column) const;
    int row() const;

private:

	USBDataModel *mp_model = nullptr;
    QString m_Timestamp;
    QString m_Pid;
    QString m_Addr;
    QString m_Endpoint;
    QString m_CRC;
    QString m_FrameNumber;
    quint64 m_DataLen = 0;
    QString m_Data;

};
