#include "mainwindow.h"

#include <QGridLayout>
#include <QWidget>
#include <QTextCodec>
#include <QFile>
#include <QDir>
#include <QTreeWidgetItem>
#include <QMenuBar>
#include <QThread>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    QThread *thread = new QThread;
    downloadManager = new DownloadManager;
    downloadManager->moveToThread(thread);

    qRegisterMetaType<QVector<StationInfo*> >("QVector<StationInfo*>");
    connect(this, SIGNAL(getTables(QVector<StationInfo*>)), downloadManager, SLOT(getTables(QVector<StationInfo*>)), Qt::QueuedConnection);
    connect(this, SIGNAL(init()), downloadManager, SLOT(init()));
    connect(downloadManager, SIGNAL(done()), this, SLOT(getData()));

    thread->start();

    emit init();

    StationInfo *info1 = new StationInfo;
    info1->name = "Name 1";
    info1->url = "http://www.mosecom.ru/air/air-today/station/spirid/table.html";
    stationInfoList.push_back(info1);

    StationInfo *info2 = new StationInfo;
    info2->name = "Name 2";
    info2->url = "http://www.mosecom.ru/air/air-today/station/spirid/table.html";
    stationInfoList.push_back(info2);

    emit getTables(stationInfoList);

    lineEditUrl = new QLineEdit("http://www.mosecom.ru/air/air-today/station/spirid/table.html");
    textEditData = new QTextEdit;
    pushButtonGet = new QPushButton("Get");
	pushButtonGet->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    //connect(pushButtonGet, SIGNAL(clicked()), this, SLOT(request()));

    treeWidgetFiles = new QTreeWidget;
    treeWidgetFiles->setColumnCount(1);
    treeWidgetFiles->setHeaderLabel("History");
   // treeWidgetFiles->insertTopLevelItems(0, items);

    //manager = new QNetworkAccessManager();

    QGridLayout* layout = new QGridLayout;
    layout->addWidget(lineEditUrl, 0, 0, 1, 2);
    layout->addWidget(pushButtonGet, 0, 2, 1, 1);
    layout->addWidget(textEditData, 1, 0, 1, 2);
    layout->addWidget(treeWidgetFiles, 1, 2, 1, 2);

    QWidget* centralWgt = new QWidget;
    centralWgt->setLayout(layout);

    setCentralWidget(centralWgt);

    //timer = new QTimer;
    //connect(timer, SIGNAL(timeout()), this, SLOT(timeout()));

    //timer->start(1000);

    createActions();
    createMenus();
    createToolBar();


}

MainWindow::~MainWindow()
{
    QThread *thread = downloadManager->thread();

    if(thread != this->thread()) {
        thread->quit();
        thread->wait();
        delete thread;
    }

    delete downloadManager;

}

void MainWindow::createActions()
{
    openAct = new QAction(QIcon(":/images/images/open.png"), tr("&Open"), this);
    openAct->setShortcuts(QKeySequence::New);
    openAct->setStatusTip(tr("Open file"));
    //connect(openAct, &QAction::triggered, this, &MainWindow::openFile);

    saveAct = new QAction(QIcon(":/images/images/save.png"), tr("&Save"), this);
    saveAct->setShortcuts(QKeySequence::New);
    saveAct->setStatusTip(tr("Open file"));
    //connect(saveAct, &QAction::triggered, this, &MainWindow::save);

    quitAct = new QAction(tr("&Quit"), this);
    quitAct->setShortcuts(QKeySequence::Quit);
    quitAct->setStatusTip(tr("Quit"));
    connect(quitAct, SIGNAL(triggered()), this, SLOT(quit()));

}

void MainWindow::createMenus()
{
    this->menuBar()->setNativeMenuBar(false);
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(openAct);
    fileMenu->addAction(saveAct);
    fileMenu->addSeparator();
    fileMenu->addAction(quitAct);

    toolMenu = menuBar()->addMenu(tr("&Tools"));
}

void MainWindow::createToolBar()
{
    QList<QToolBar *> allToolBars = this->findChildren<QToolBar *>();
    foreach(QToolBar *tb, allToolBars) {
        // This does not delete the tool bar.
        this->removeToolBar(tb);
    }

    fileToolBar = addToolBar(tr("File"));
    fileToolBar->setIconSize(QSize(ICON_SIZE, ICON_SIZE));
    fileToolBar->addAction(openAct);
    fileToolBar->addAction(saveAct);
    fileToolBar->addSeparator();


}

void MainWindow::createCentralWidget()
{

    QHBoxLayout* layout = new QHBoxLayout;
    //layout->addWidget(view, 1);
   //layout->addWidget(tabWidget);

    this->centralWidget()->setLayout(layout);

}

void MainWindow::quit()
{
    this->close();
}
//-----------------------------------


//void MainWindow::request()
//{
//    QString url = lineEditUrl->text();
//    response = manager->get(QNetworkRequest(QUrl(url)));
//    connect(response,SIGNAL(finished()),this,SLOT(getData()));
//    connect(response, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(error(QNetworkReply::NetworkError)));
//}


void MainWindow::getData()
{
    QTreeWidgetItem *dateItem = new QTreeWidgetItem(treeWidgetFiles);
    //dateItem->setText(0, stationInfoList[0]->date);

    treeWidgetFiles->addTopLevelItem(dateItem);

    /*
    int index = treeWidgetFiles->topLevelItemCount();
    QTreeWidgetItem *dateItem = treeWidgetFiles->topLevelItem(index - 1);

    QTreeWidgetItem *timeItem = new QTreeWidgetItem();
    //timeItem->setText(0, timeText);

    dateItem->addChild(timeItem);
    */


}

//void MainWindow::error(QNetworkReply::NetworkError code)
//{
//    qDebug() << QString("error %1").arg(code);
//}
