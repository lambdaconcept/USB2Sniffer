#include "MainWindow.hpp"
#include <string>
#include <QFrame>
#include <QDockWidget>
#include <QListView>
#include <QVBoxLayout>
#include <QDebug>







void addUsbDevice()
{

}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
	mp_mainScrollArea = new QScrollArea(this);


	mp_mainFrame = new QFrame(mp_mainScrollArea);
	new QVBoxLayout(mp_mainFrame);


	
	mp_mainFrame->layout()->addWidget(addUsbDevice());
	mp_mainScrollArea->setWidget(mp_mainFrame);



    QDockWidget *dock1 = new QDockWidget(this);
	QListView *listView1 = new QListView(this);
	listView1->setModel(new UsbDataModel);
	dock1->setWidget(listView1);
	addDockWidget(Qt::BottomDockWidgetArea, dock1);

	QDockWidget *dock2 = new QDockWidget(this);
	QListView *listView2 = new QListView(this);
	dock2->setWidget(listView2);
	addDockWidget(Qt::BottomDockWidgetArea, dock2);
	setCentralWidget(mp_mainFrame);
}

MainWindow::~MainWindow()
{

}

