#pragma once
#include <QMainWindow>
#include <QAbstractItemModel>
#include <QScrollArea>
#include <QListView>
#include "USBDataModel.hpp"

#include "ruler.h"
#include "zoomer.h"

class UsbDeviceDataContainer
{
public:
	USBDataModel m_model;
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

