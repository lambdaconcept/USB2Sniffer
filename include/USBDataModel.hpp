#pragma once
#include <QAbstractItemModel>
#include <QModelIndex>
#include <QVariant>

class USBDataItem;

class USBDataModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    explicit USBDataModel(QObject *parent = nullptr);
    ~USBDataModel();

    QVariant data(const QModelIndex &index, int role) const override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const override;
    QModelIndex index(int row, int column,
                      const QModelIndex &parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex &index) const override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;


private:
	QStringList m_columns = { "Transfer",
							  "Time",
							  "Device",
							  "Length",
							  "Setup",
							  "Data" };
	QVector<USBDataItem *> m_items;
};
