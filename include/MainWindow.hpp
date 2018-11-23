#pragma once
#include <QMainWindow>
#include <QAbstractItemModel>
#include <QScrollArea>
#include <QTreeView>
#include <QSplitter>
#include <QMenu>
#include <QMenuBar>
#include <QFileDialog>
#include <QProgressBar>
#include <QStatusBar>

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

    void setupMenubar();


private:
	QVector<UsbDeviceDataContainer *> m_usbContainers;
	QScrollArea *mp_mainScrollArea = nullptr;
    QSplitter *mp_mainSplitter = nullptr;
    QFrame *mp_timeLineFrame = nullptr;
    QFrame *mp_listsFrame = nullptr;

    QMenuBar *mp_menubar = nullptr;
    QMenu *mp_fileMenu = nullptr;
    QAction *mp_importSampleData = nullptr;
    QStatusBar *mp_statusBar = nullptr;
    QProgressBar *mp_progressBar = nullptr;
    USBDataModel *mp_experimentalModel = new USBDataModel;
};

