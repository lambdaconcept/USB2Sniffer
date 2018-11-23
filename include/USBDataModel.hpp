#pragma once
#include <QAbstractTableModel>
#include <QModelIndex>
#include <QVariant>
#include <QtDebug>
class USBDataItem;

class USBDataModel : public QAbstractTableModel
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

    static QStringList m_columns;


    void setItems(const QVector<const USBDataItem *> &items) {
        beginInsertRows(QModelIndex(), 0, items.count()-1);
        m_items = items;
        endInsertRows();
    }

private:
    QVector<const USBDataItem *> m_items;
};
