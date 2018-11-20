#include "MainWindow.hpp"
#include "USBDataModel.hpp"
#include <string>
#include <QFrame>
#include <QDockWidget>
#include <QTreeView>
#include <QVBoxLayout>
#include <QHBoxLayout>

#include <QSizePolicy>

#include <QDebug>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    mp_mainSplitter = new QSplitter(this);
    mp_mainSplitter->setOrientation(Qt::Vertical);

    mp_mainScrollArea = new QScrollArea(mp_mainSplitter);


    mp_timeLineFrame = new QFrame(mp_mainScrollArea);
    mp_timeLineFrame->setLayout(new QVBoxLayout);
    mp_mainScrollArea->setWidget(mp_timeLineFrame);
    mp_mainScrollArea->setWidgetResizable(true);
    mp_mainSplitter->addWidget(mp_mainScrollArea);

    mp_listsFrame = new QFrame(mp_mainSplitter);
    mp_listsFrame->setLayout(new QHBoxLayout);

    mp_mainSplitter->addWidget(mp_listsFrame);

	addUsbDevice();

    this->setCentralWidget(mp_mainSplitter);
}

MainWindow::~MainWindow()
{

}

void MainWindow::addUsbDevice()
{
	UsbDeviceDataContainer *container = new UsbDeviceDataContainer;


    container->mp_timeLineWidget = new timeline::TimeLineWidget(mp_timeLineFrame);


    container->mp_timeLineWidget->show();
    mp_timeLineFrame->layout()->addWidget(container->mp_timeLineWidget);



    container->mp_dataView = new QTreeView(mp_listsFrame);
    mp_listsFrame->layout()->addWidget(container->mp_dataView);
	container->mp_dataView->setModel(new USBDataModel(nullptr));
    container->mp_dataView->setRootIsDecorated(false);
	
	m_usbContainers.append(container);
}

