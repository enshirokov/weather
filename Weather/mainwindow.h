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


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void request();
    void getData();

private:
    QNetworkAccessManager *manager;
    QNetworkReply *response;

    QLineEdit *lineEditUrl;
    QTextEdit *textEditData;
    QPushButton *pushButtonGet;
};

#endif // MAINWINDOW_H
