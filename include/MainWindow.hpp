#pragma once
#include <QMainWindow>
#include <QAbstractItemModel>
#include <QScrollArea>
#include <QTreeView>
#include "USBDataModel.hpp"

#include "ruler.h"
#include "zoomer.h"

class UsbDeviceDataContainer
{
public:
	USBDataModel *mp_model = nullptr;
	QTreeView *mp_dataView = nullptr;
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
	void addUsbDevice();


private:
    timeline::Ruler *mp_ruler = nullptr;
	timeline::Zoomer *mp_zoomer = nullptr;
	QVector<UsbDeviceDataContainer *> m_usbContainers;
	QScrollArea *mp_mainScrollArea = nullptr;
	QFrame *mp_mainFrame = nullptr;

};

