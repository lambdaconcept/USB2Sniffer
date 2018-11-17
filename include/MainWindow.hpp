#pragma once
#include <QMainWindow>
#include <QAbstractItemModel>
#include <QScrollArea>
#include <QListView>

#include "ruler.h"
#include "zoomer.h"


struct UsbData
{
	std::string Transfer;
	std::string Time;
	unsigned int Device;
	std::string Length;
	std::string Setup;
	std::string Data;
};

class UsbDataModel : public QAbstractItemModel
{
public:
	UsbDataModel(QObject *parent = nullptr) : QAbstractItemModel(parent)
	{

	}

	~UsbDataModel()
	{
	}


	QModelIndex index(int row, int column, const QModelIndex &parent) const
	{
		if (!parent.isValid())
			return QModelIndex();
		return createIndex(row, column, (void *)&m_data[row]);
	}


	QModelIndex parent(const QModelIndex &index) const
	{
		if (!index.isValid())
			return QModelIndex();

		return QModelIndex();
	}

	int rowCount(const QModelIndex &parent) const
	{
		return static_cast<int>(m_data.size());
	}

	int columnCount(const QModelIndex &parent) const
	{
		return m_columns.count();
	}

	QVariant data(const QModelIndex &index, int role) const
	{
		if (!index.isValid())
			return QVariant();

		if (role != Qt::DisplayRole)
			return QVariant();

		UsbData *item = static_cast<UsbData *>(index.internalPointer());

		if (index.column() == 0) {
			return QVariant(item->Transfer.c_str());
		}
		else if (index.column() == 1) {
			return QVariant(item->Time.c_str());
		}
		else if (index.column() == 2) {
			return QVariant(item->Device);
		}
		else if (index.column() == 3) {
			return QVariant(item->Length.c_str());
		}
		else if (index.column() == 4) {
			return QVariant(item->Setup.c_str());
		}
		else if (index.column() == 5) {
			return QVariant(item->Data.c_str());
		}
		return QVariant();
	}

	Qt::ItemFlags flags(const QModelIndex &index) const
	{
		if (!index.isValid())
			return Qt::ItemIsEnabled;

		return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
	}

	QVariant headerData(int section, Qt::Orientation orientation, int role) const
	{
		if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
			return m_columns.at(section);

		return QVariant();
	}

private:
	QStringList m_columns = { "Transfer", "Time", "Device", "Length", "Setup", "Data" };

	std::vector<UsbData> m_data = { { "Transfer", "Time", 1, "Length", "Setup", "Data" } };
};


class UsbDeviceDataContainer
{
public:
	UsbDataModel m_model;
	QListView *mp_dataView = nullptr;
	QDockWidget *mp_dockWidget = nullptr;
	timeline::Ruler *mp_ruler = nullptr;
	timeline::Zoomer *mp_zoomer = nullptr;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
	QScrollArea *addUsbDevice()
	{
		UsbDeviceDataContainer container;
		QScrollArea *area = new QScrollArea(mp_mainFrame);
		area->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

		timeline::Zoomer *mZoomer = new timeline::Zoomer(this);

		timeline::Ruler *mRuler = new timeline::Ruler(this);

		area->setWidget(mRuler);

		connect(mZoomer, &timeline::Zoomer::zoomerIn, mRuler, &timeline::Ruler::onZoomerIn);
		connect(mZoomer, &timeline::Zoomer::zoomerOut, mRuler, &timeline::Ruler::onZoomerOut);
		connect(mRuler, &timeline::Ruler::changeSliderPosition, mZoomer, &timeline::Zoomer::onChangeSliderPosition);
		return area;
	}


private:
    timeline::Ruler *mp_ruler = nullptr;
	timeline::Zoomer *mp_zoomer = nullptr;
	std::vector<UsbDeviceDataContainer> m_usbContainers;
	QScrollArea *mp_mainScrollArea = nullptr;
	QFrame *mp_mainFrame = nullptr;

};

