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
    setWindowState(Qt::WindowMaximized);
    restoreSettings();

    restore();

    QThread *thread = new QThread;
    downloadManager = new DownloadManager;
    downloadManager->moveToThread(thread);

    qRegisterMetaType<QVector<StationInfo*> >("QVector<StationInfo*>");
    connect(this, SIGNAL(getTables(WeatherItem*)), downloadManager, SLOT(getTables(WeatherItem*)), Qt::QueuedConnection);
    connect(this, SIGNAL(init()), downloadManager, SLOT(init()));
    connect(downloadManager, SIGNAL(done(quint64)), this, SLOT(addData(quint64)));

    thread->start();

    emit init();
/*
    StationInfo *info1 = new StationInfo;
    info1->name = "Name 1";
    info1->url = "http://www.mosecom.ru/air/air-today/station/spirid/table.html";
    _stationInfoList.push_back(info1);

    StationInfo *info2 = new StationInfo;
    info2->name = "Name 2";
    info2->url = "http://www.mosecom.ru/air/air-today/station/spirid/table.html";
    _stationInfoList.push_back(info2);

    emit getTables(_stationInfoList);
*/
    textEditData = new QTextEdit;
    //connect(pushButtonGet, SIGNAL(clicked()), this, SLOT(request()));

    treeWidgetFiles = new QTreeWidget;
    treeWidgetFiles->setColumnCount(1);
    treeWidgetFiles->setHeaderLabel("History");
   // treeWidgetFiles->insertTopLevelItems(0, items);
    connect(treeWidgetFiles, SIGNAL(itemClicked(QTreeWidgetItem*,int)), this, SLOT(itemClicked(QTreeWidgetItem*,int)));

    //manager = new QNetworkAccessManager();

    QGridLayout* layout = new QGridLayout;
    layout->addWidget(textEditData, 1, 0, 1, 4);
    layout->addWidget(treeWidgetFiles, 1, 4, 1, 2);

    QWidget* centralWgt = new QWidget;
    centralWgt->setLayout(layout);

    setCentralWidget(centralWgt);

    timer = new QTimer;
    connect(timer, SIGNAL(timeout()), this, SLOT(timeout()));

    //timer->start(1000);

    createActions();
    createMenus();
    createToolBar();    

    //timeout();
}

MainWindow::~MainWindow()
{
    storeSettings();
    store();

    /*
    QThread *thread = downloadManager->thread();

    if(thread != this->thread()) {
        thread->quit();
        thread->wait();


       delete thread;
    }
    */

    //delete downloadManager;


}

void MainWindow::createActions()
{
    dbAct = new QAction(QIcon(":/images/database.png"), tr("&Database"), this);
    dbAct->setShortcuts(QKeySequence::New);
    dbAct->setStatusTip(tr("Open database editor"));
    connect(dbAct, SIGNAL(triggered(bool)), this, SLOT(openDataBase(bool)));

    timerAct = new QAction(QIcon(":/images/timer.png"), tr("&Timer"), this);
    timerAct->setShortcuts(QKeySequence::New);
    timerAct->setStatusTip(tr("Open timer editor"));
    connect(timerAct, SIGNAL(triggered(bool)), this, SLOT(openTimer(bool)));

    quitAct = new QAction(tr("&Quit"), this);
    quitAct->setShortcuts(QKeySequence::Quit);
    quitAct->setStatusTip(tr("Quit"));
    connect(quitAct, SIGNAL(triggered()), this, SLOT(quit()));

}

void MainWindow::createMenus()
{
    this->menuBar()->setNativeMenuBar(false);
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addSeparator();
    fileMenu->addAction(quitAct);

    toolMenu = menuBar()->addMenu(tr("&Tools"));
    toolMenu->addAction(dbAct);
    toolMenu->addAction(timerAct);
}

void MainWindow::createToolBar()
{
    QList<QToolBar *> allToolBars = this->findChildren<QToolBar *>();
    foreach(QToolBar *tb, allToolBars) {
        // This does not delete the tool bar.
        this->removeToolBar(tb);
    }

    toolBar = addToolBar(tr("Tool Bar"));
    toolBar->setIconSize(QSize(ICON_SIZE, ICON_SIZE));
    toolBar->addAction(dbAct);
    toolBar->addAction(timerAct);
    toolBar->addSeparator();


}

void MainWindow::createCentralWidget()
{

    QHBoxLayout* layout = new QHBoxLayout;
    //layout->addWidget(view, 1);
   //layout->addWidget(tabWidget);

    this->centralWidget()->setLayout(layout);

}

void MainWindow::storeSettings()
{
     QSettings settings("MySoft", "Weater");

     settings.setValue("homePath", path);
}

void MainWindow::restoreSettings()
{
    QSettings settings("MySoft", "Weater");

    path = settings.value("homePath", QDir::homePath()).toString();
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


void MainWindow::addData(quint64 id)
{
    /*
    WeatherItem *weatherItem = _weatherItemList[id];

    if(weatherItem == nullptr){
        qDebug() << "incorrect id";
        return;
    }
    */

/*
    for(int i = 0; i < treeWidgetFiles->size(); i++) {

       QTreeWidgetItem *item = treeWidgetFiles->topLevelItem(i);
       delete item;
    }
    */

    treeWidgetFiles->clear();

    QList<quint64> keys = _weatherItemList.keys();

    for(int i = 0; i < keys.size(); i++) {
        WeatherItem *weatherItem = _weatherItemList[keys[i]];

        QTreeWidgetItem *dateItem = new QTreeWidgetItem(treeWidgetFiles);
        dateItem->setText(0, weatherItem->date);

        for(int j = 0; j < weatherItem->stations.size(); j++) {

            QTreeWidgetItem *stationItem = new QTreeWidgetItem;
            stationItem->setText(0, weatherItem->stations[j].name);

            dateItem->addChild(stationItem);
        }

        treeWidgetFiles->addTopLevelItem(dateItem);

    }


}

//void MainWindow::error(QNetworkReply::NetworkError code)
//{
//    qDebug() << QString("error %1").arg(code);
//}

void MainWindow::openDataBase(bool value)
{
    DataBaseWidget dbWidget(path, _stationInfoList);

    dbWidget.exec();
}

void MainWindow::openTimer(bool value)
{
    QTime time(0, 0, 0);

    TimerWidget timerWidget(time);
    int result = timerWidget.exec();

    if(result == QDialog::Accepted){
        if(timer->isActive())
            timer->stop();

        int mseconds = QTime(0, 0, 0).msecsTo(time);

        if(mseconds <= 0)
            timeout();
        else
            timer->start(mseconds);
    }

}

void MainWindow::timeout()
{
    qDebug() << "timeout()";

    WeatherItem *item = new WeatherItem;
    item->date = QDateTime::currentDateTime().toString("dd-MM-yyyy hh:mm:ss");
    item->stations = _stationInfoList;


    int id = _weatherItemList.size()+1;
    item->id = id;
    _weatherItemList[id] = item;

    emit getTables(item);
}

void MainWindow::store()
{
    QFile file(path + "/db");
    if(!file.open(QIODevice::WriteOnly)) {
        qDebug() << "error open db for write";
        return;
    }

    QDataStream stream(&file);

    quint32 size = _stationInfoList.size();
    stream << size;

    for(int i = 0; i < size; i++) {
        StationInfo info = _stationInfoList.at(i);
        info.write(stream);

    }

    _stationInfoList.clear();
}

void MainWindow::restore()
{
    QFile file(path + "/db");
    if(!file.open(QIODevice::ReadOnly)) {
        qDebug() << "error open db for write";
        return;
    }

    QDataStream stream(&file);

    quint32 size;
    stream >> size;

    for(int i = 0; i < size; i++) {
        StationInfo item;
        item.read(stream);

        _stationInfoList.push_back(item);
    }

}

void MainWindow::itemClicked(QTreeWidgetItem *item, int column)
{
    QTreeWidgetItem *parent = item->parent();

    if(parent == NULL)
        return;

    QList<quint64> keys = _weatherItemList.keys();

    int parentId = treeWidgetFiles->indexOfTopLevelItem(parent);

    if(parentId >= keys.size()) {
        qDebug() << "error id key parent";
        return;
    }

    quint64 key = keys[parentId];

    WeatherItem *weatherItem = _weatherItemList[key];

    int childId = treeWidgetFiles->currentIndex().row();

    if(childId >= weatherItem->stations.size()) {
        qDebug() << "error id key child";
        return;
    }

    QString filePath = weatherItem->stations[childId].path;

    QFile file(filePath);
    if(!file.open(QIODevice::ReadOnly)){
        qDebug() << "open file error";
        return;
    }

    QByteArray rawData = file.readAll();

    textEditData->setHtml(rawData);

}
