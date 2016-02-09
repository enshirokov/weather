#include "mainwindow.h"

#include <QGridLayout>
#include <QWidget>
#include <QTextCodec>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    lineEditUrl = new QLineEdit("http://www.mosecom.ru/air/air-today/station/spirid/table.html");
    textEditData = new QTextEdit;
    pushButtonGet = new QPushButton("Get");
    connect(pushButtonGet, SIGNAL(clicked()), this, SLOT(request()));

    manager = new QNetworkAccessManager();



    QGridLayout* layout = new QGridLayout;
    layout->addWidget(lineEditUrl, 0, 0, 1, 2);
    layout->addWidget(pushButtonGet, 0, 2, 1, 1);
    layout->addWidget(textEditData, 1, 0, 1, 3);

    QWidget* centralWgt = new QWidget;
    centralWgt->setLayout(layout);

    setCentralWidget(centralWgt);


}

MainWindow::~MainWindow()
{
}

void MainWindow::request()
{
    QString url = lineEditUrl->text();
    response = manager->get(QNetworkRequest(QUrl(url)));
    connect(response,SIGNAL(finished()),this,SLOT(getData()));
}

void MainWindow::getData()
{
    QString text = response->readAll();

    QTextCodec *codec = QTextCodec::codecForName("windows-1251");

    textEditData->setPlainText(codec->toUnicode(text.toLocal8Bit()));
    //textEditData->setPlainText(text);

    int a = 1;
}
