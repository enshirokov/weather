#include "mainwindow.h"

#include <QGridLayout>
#include <QWidget>
#include <QTextCodec>
#include <QFile>
#include <QDir>
#include <QTreeWidgetItem>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    lineEditUrl = new QLineEdit("http://www.mosecom.ru/air/air-today/station/spirid/table.html");
    textEditData = new QTextEdit;
    pushButtonGet = new QPushButton("Get");
	pushButtonGet->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    connect(pushButtonGet, SIGNAL(clicked()), this, SLOT(request()));

    treeWidgetFiles = new QTreeWidget;
    treeWidgetFiles->setColumnCount(1);
   // treeWidgetFiles->insertTopLevelItems(0, items);

    manager = new QNetworkAccessManager();

    QGridLayout* layout = new QGridLayout;
    layout->addWidget(lineEditUrl, 0, 0, 1, 2);
    layout->addWidget(pushButtonGet, 0, 2, 1, 1);
    layout->addWidget(textEditData, 1, 0, 1, 2);
    layout->addWidget(treeWidgetFiles, 1, 2, 1, 2);

    QWidget* centralWgt = new QWidget;
    centralWgt->setLayout(layout);

    setCentralWidget(centralWgt);

    timer = new QTimer;
    connect(timer, SIGNAL(timeout()), this, SLOT(timeout()));

    timer->start(1000);


}

MainWindow::~MainWindow()
{
}

void MainWindow::request()
{
    QString url = lineEditUrl->text();
    response = manager->get(QNetworkRequest(QUrl(url)));
    connect(response,SIGNAL(finished()),this,SLOT(getData()));
    connect(response, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(error(QNetworkReply::NetworkError)));
}

void MainWindow::timeout()
{
    disconnect(timer, SIGNAL(timeout()), this, SLOT(timeout()));

    QString dateText = QDateTime::currentDateTime().date().toString("dd:MM:yyyy");

    QTreeWidgetItem *dateItem = new QTreeWidgetItem(treeWidgetFiles);
    dateItem->setText(0, dateText);

    treeWidgetFiles->addTopLevelItem(dateItem);

    request();
}

void MainWindow::getData()
{
    QString text = response->readAll();

    QTextCodec *codec = QTextCodec::codecForName("windows-1251");

    //textEditData->setPlainText(codec->toUnicode(text.toLocal8Bit()));
    textEditData->setHtml(text);
    //textEditData->setPlainText(text);

    QString timeText = QDateTime::currentDateTime().toString("HH:mm:ss");

    QString path = QDir::homePath() + "/Weather/" + timeText + ".weather";
    QFile file(path);
    if (!file.open(QIODevice::WriteOnly)) {
        qDebug() << "error open file";
            return;
    }

    file.write(text.toLocal8Bit().data());
    file.close();


    int index = treeWidgetFiles->topLevelItemCount();
    QTreeWidgetItem *dateItem = treeWidgetFiles->topLevelItem(index - 1);

    QTreeWidgetItem *timeItem = new QTreeWidgetItem();
    timeItem->setText(0, timeText);

    dateItem->addChild(timeItem);



    //items.append(osloItem);

}

void MainWindow::error(QNetworkReply::NetworkError code)
{
    qDebug() << QString("error %1").arg(code);
}
