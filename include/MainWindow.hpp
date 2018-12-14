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
#include <QMouseEvent>
#include "USBDataModel.hpp"
#include "TimeLineWidget.h"

#include "ruler.h"
#include "zoomer.h"


class TimeLineMouseEventFilter : public QObject {
    Q_OBJECT
    public:
        TimeLineMouseEventFilter(QObject *parent = nullptr) : QObject(parent) {

        }

    protected:
        bool eventFilter(QObject *obj, QEvent *ev) {
            if (ev->type() == QEvent::MouseButtonPress)
             {
               QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(ev);
               emit indexClicked(mouseEvent->pos().x()-1);
             }
            return QObject::eventFilter(obj, ev);
        }

    signals:
        void indexClicked(int index);

};


class UsbDeviceDataContainer
{
public:
	USBDataModel *mp_model = nullptr;
	QTreeView *mp_dataView = nullptr;
 //   timeline::TimeLineWidget *mp_timeLineWidget = nullptr;
    QLabel *mp_timeLineWidget = nullptr;
    TimeLineMouseEventFilter m_timeLineEf;

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

