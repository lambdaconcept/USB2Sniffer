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
#include <math.h>
#include <QDebug>
#include <QImage>
#include <QPixmap>
#include <QPainter>
#include <QPointF>
#include <QItemSelectionModel>


const QColor pid_colors[] = {
    QColor(255, 0,   0),
    QColor(255, 128, 0),
    QColor(255, 191, 0),
    QColor(191, 255, 0),
    QColor(64,  255, 0),
    QColor(0,   255, 64),
    QColor(0,   255, 191),
    QColor(0,   255, 255),
    QColor(0,   191, 255),
    QColor(0,   128, 255),
    QColor(0,   0,   255),
    QColor(128, 0,   255),
    QColor(191, 0,   255),
    QColor(255, 0,   255),
    QColor(255, 0,   128),
    QColor(255, 0,   0)
};

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
    //container->mp_timeLineWidget = new timeline::TimeLineWidget(mp_timeLineFrame);

    container->mp_timeLineWidget = new TimeLineLabel(mp_timeLineFrame);

    container->mp_timeLineWidget->installEventFilter(&container->m_timeLineEf);
    container->mp_timeLineWidget->show();
    mp_timeLineFrame->layout()->addWidget(container->mp_timeLineWidget);

    container->mp_dataView = new QTreeView(mp_listsFrame);
    container->mp_dataView->setSelectionBehavior (QAbstractItemView::SelectRows);
    mp_listsFrame->layout()->addWidget(container->mp_dataView);
    container->mp_dataView->setModel(mp_experimentalModel);
    container->mp_dataView->setRootIsDecorated(false);
   
	connect(&container->m_timeLineEf, &TimeLineMouseEventFilter::indexClicked, [&](int index) {
        m_usbContainers.at(0)->mp_dataView->selectionModel()->clearSelection();
        m_usbContainers.at(0)->mp_dataView->selectionModel()->select(mp_experimentalModel->index(index, 0), QItemSelectionModel::Select | QItemSelectionModel::Rows);
        m_usbContainers.at(0)->mp_dataView->scrollTo(mp_experimentalModel->index(index, 0));
    });

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
        QHash<double, int> hm;
        int count = 0;
        QVector<QPair<int, long long int>> packetsPerSec;
        long long int value = 0;
        int currentLastDigit = -1;
        while(!feof(in)){
            value++;
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

            const USBDataItem *item = new USBDataItem(QString::number(pkt.timestamp), pkt.pid, QString(pid_str[pkt.pid & 0xF]), QString(address), QString::number(pkt.ep), QString(crc), QString::number(pkt.frameno), pkt.dlen, qdata, mp_experimentalModel);
            items.append(item);
            free(buf);
            progress++;
            //m_usbContainers[0]->mp_timeLineWidget->appendTimeStampPid(pkt.timestamp/100000000.0f, pkt.pid & 0xF);
            mp_progressBar->setValue(1000*progress/(double)filesize + 5);

            int lastDigit = floor(pkt.timestamp/100000000.0f);
            if(lastDigit != currentLastDigit) {
                currentLastDigit = lastDigit;
                packetsPerSec.append(QPair<int, long long int>(lastDigit, value));
            }
        }


        QImage img(items.count() + 20, 50, QImage::Format_ARGB32_Premultiplied);

        for(int index = 0; index < items.count(); index++) {
            for(int h = 20; h < 50; h++) {
                img.setPixelColor(index, h, pid_colors[items[index]->pid()  & 0xF ]);
            }
        }


        if(packetsPerSec.count()) {
            for(int index = 1; index < packetsPerSec.count(); index++) {
                for(int h = 0; h < 20; h++) {
                    img.setPixelColor(packetsPerSec[index].second, h, Qt::black);
                }
            }
        }

        QPixmap pix;
        pix.convertFromImage(img);
		m_usbContainers[0]->mp_timeLineWidget->m_packetsPerSec = packetsPerSec;
        m_usbContainers[0]->mp_timeLineWidget->setPixmap(pix);


        mp_experimentalModel->setItems(items);

    });


    mp_fileMenu->addAction(mp_importSampleData);
    mp_menubar->addMenu(mp_fileMenu);
    mp_statusBar = new QStatusBar(this);
    mp_statusBar->addWidget(mp_progressBar = new QProgressBar(this));
    this->setMenuBar(mp_menubar);
    this->setStatusBar(mp_statusBar);

}

