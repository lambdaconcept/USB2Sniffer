#include "MainWindow.hpp"
#include <QFrame>
#include <QDockWidget>
#include <QListView>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
	QFrame *mainFrame = new QFrame(this);
	QDockWidget *dock1 = new QDockWidget(tr("Customers1"), this);
	QListView *listView1 = new QListView(this);
	dock1->setWidget(listView1);
	addDockWidget(Qt::BottomDockWidgetArea, dock1);

	QDockWidget *dock2 = new QDockWidget(tr("Customers2"), this);
	QListView *listView2 = new QListView(this);
	dock2->setWidget(listView2);
	addDockWidget(Qt::BottomDockWidgetArea, dock2);
	setCentralWidget(mainFrame);
}

MainWindow::~MainWindow()
{

}

