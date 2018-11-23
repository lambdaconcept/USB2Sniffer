#include "MainWindow.hpp"
#include "USBDataModel.hpp"
#include "USBDataItem.hpp"
#include <string>
#include <QFrame>
#include <QDockWidget>
#include <QTreeView>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "decode.h"

#include <QSizePolicy>

#include <QDebug>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    setupMenubar();
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
    container->mp_dataView->setModel(mp_experimentalModel);
    container->mp_dataView->setRootIsDecorated(false);
	
	m_usbContainers.append(container);
}

void MainWindow::setupMenubar() {
    mp_menubar = new QMenuBar(this);
    mp_fileMenu = new QMenu("File", mp_menubar);
    mp_importSampleData = new QAction("Import Sample Data", mp_fileMenu);
    connect(mp_importSampleData, &QAction::triggered, [&](){
        QString file = QFileDialog::getOpenFileName(this, "Import Sample Data", QString::null, "*.bin", nullptr);

        QFile file_handle(file);
        int64_t filesize = file_handle.size()/sizeof(int);

        FILE *in;
        int len;
        char *buf;
        int64_t progress = 1;
        in = fopen(file.toUtf8().constData(), "rb");
        QVector<const USBDataItem *> items;
        char address[32];
        char crc[32];
        char pdata[3];
        QString qdata;
        while(!feof(in)){
            fread(&len, 1, sizeof(int), in);
            buf = static_cast<char *>(malloc(len));
            fread(buf, 1, len, in);

            struct usb_packet_s pkt = decode_usb(buf, len);
            sprintf(address,"%02X",pkt.addr);
            sprintf(crc,"%04X",pkt.crc);
            qdata.clear();
            qdata.reserve(pkt.dlen);
            if(pkt.dlen){
              for(int index = 0; index < pkt.dlen; index++){
                sprintf(pdata, "%02x ",pkt.data[index]);
                qdata.append(pdata);
              }
            }

            const USBDataItem *item = new USBDataItem(QString::number(pkt.timestamp), QString(pid_str[pkt.pid & 0xF]), QString(address), QString::number(pkt.ep), QString(crc), QString::number(pkt.frameno), pkt.dlen, qdata, mp_experimentalModel);
            items.append(item);
            free(buf);
            progress++;
            mp_progressBar->setValue(1000*progress/(double)filesize + 5);
        }
        mp_experimentalModel->setItems(items);

    });


    mp_fileMenu->addAction(mp_importSampleData);
    mp_menubar->addMenu(mp_fileMenu);
    mp_statusBar = new QStatusBar(this);
    mp_statusBar->addWidget(mp_progressBar = new QProgressBar(this));
    this->setMenuBar(mp_menubar);
    this->setStatusBar(mp_statusBar);

}

