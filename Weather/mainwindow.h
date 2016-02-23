#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QtNetwork/QNetworkAccessManager>
#include <QUrl>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>

#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>
#include <QTreeWidget>
#include <QTimer>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void request();
    void getData();
    void error(QNetworkReply::NetworkError);
    void timeout();

private:
    QNetworkAccessManager *manager;
    QNetworkReply *response;

    QLineEdit *lineEditUrl;
    QTextEdit *textEditData;
    QPushButton *pushButtonGet;
    QTreeWidget *treeWidgetFiles;

     QList<QTreeWidgetItem *> items;
     QTimer *timer;

};

#endif // MAINWINDOW_H
