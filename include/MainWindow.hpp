#pragma once
#include <QMainWindow>
#include <QAbstractItemModel>
#include <QScrollArea>
#include <QTreeView>
#include <QSplitter>

#include "USBDataModel.hpp"
#include "TimeLineWidget.h"

#include "ruler.h"
#include "zoomer.h"

class UsbDeviceDataContainer
{
public:
	USBDataModel *mp_model = nullptr;
	QTreeView *mp_dataView = nullptr;
    timeline::TimeLineWidget *mp_timeLineWidget = nullptr;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
	void addUsbDevice();


private:
	QVector<UsbDeviceDataContainer *> m_usbContainers;
	QScrollArea *mp_mainScrollArea = nullptr;
    QSplitter *mp_mainSplitter = nullptr;
    QFrame *mp_timeLineFrame = nullptr;
    QFrame *mp_listsFrame = nullptr;

};

