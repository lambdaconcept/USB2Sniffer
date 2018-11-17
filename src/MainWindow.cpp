#include "MainWindow.hpp"
#include "USBDataModel.hpp"
#include <string>
#include <QFrame>
#include <QDockWidget>
#include <QTreeView>
#include <QVBoxLayout>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
	mp_mainScrollArea = new QScrollArea(this);

	mp_mainFrame = new QFrame(mp_mainScrollArea);
	new QVBoxLayout(mp_mainFrame);
	
	mp_mainScrollArea->setWidget(mp_mainFrame);

	addUsbDevice();
	//addUsbDevice();
	//addUsbDevice();
	this->setCentralWidget(mp_mainScrollArea);

}

MainWindow::~MainWindow()
{

}

void MainWindow::addUsbDevice()
{
	UsbDeviceDataContainer *container = new UsbDeviceDataContainer;
	QScrollArea *area = new QScrollArea(mp_mainFrame);
	//area->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

	container->mp_zoomer = new timeline::Zoomer();
	container->mp_zoomer->show();
	container->mp_ruler = new timeline::Ruler();
	container->mp_ruler->show();
	
	//mp_mainFrame->layout()->addWidget(mp_zoomer);

	area->setWidget(container->mp_ruler);

	connect(container->mp_zoomer, &timeline::Zoomer::zoomerIn, container->mp_ruler, &timeline::Ruler::onZoomerIn);
	connect(container->mp_zoomer, &timeline::Zoomer::zoomerOut, container->mp_ruler, &timeline::Ruler::onZoomerOut);
	connect(container->mp_ruler, &timeline::Ruler::changeSliderPosition, container->mp_zoomer, &timeline::Zoomer::onChangeSliderPosition);
	

	container->mp_dockWidget = new QDockWidget(this);
	container->mp_dataView = new QTreeView(container->mp_dockWidget);

	container->mp_dataView->setModel(new USBDataModel(nullptr));
	container->mp_dockWidget->setWidget(container->mp_dataView);
	addDockWidget(Qt::BottomDockWidgetArea, container->mp_dockWidget);
	
	mp_mainFrame->layout()->addWidget(area);
	m_usbContainers.append(container);
}

