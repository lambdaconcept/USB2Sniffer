#pragma once
#include <QList>
#include <QVariant>

class USBDataItem
{
public:
    explicit USBDataItem(const QString &Transfer, const QString &Time, unsigned int Device, const QString &Length, const QString &Setup, const QString &Data, USBDataItem *parentItem = nullptr);
    ~USBDataItem();

    void appendChild(USBDataItem *child);

	USBDataItem *child(int row);
    int childCount() const;
    int columnCount() const;
    QVariant data(int column) const;
    int row() const;
	USBDataItem *parentItem();

private:
    QList<USBDataItem *> m_childItems;
	USBDataItem *m_parentItem;


	QString m_Transfer;
	QString m_Time;
	unsigned int m_Device = 0;
	QString m_Length;
	QString m_Setup;
	QString m_Data;
};
