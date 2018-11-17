#pragma once
#include <QList>
#include <QVariant>
class USBDataModel;
class USBDataItem
{
public:
    explicit USBDataItem(const QString &Transfer, const QString &Time, unsigned int Device, const QString &Length, const QString &Setup, const QString &Data, USBDataModel *model);
    ~USBDataItem();


    int columnCount() const;
    QVariant data(int column) const;
    int row() const;

private:

	USBDataModel *mp_model = nullptr;
	QString m_Transfer;
	QString m_Time;
	unsigned int m_Device = 0;
	QString m_Length;
	QString m_Setup;
	QString m_Data;
};
