#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>
#include <QTreeWidget>
#include <QTimer>
#include <QAction>
#include <QMenu>
#include <QToolBar>

#include <QVector>

#include "downloadmanager.h"
#include "stationinfo.h"

static const int ICON_SIZE = 64;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

signals:
    void getTables(QVector<StationInfo*>);
    void init();

private slots:
    //void request();
    void getData();
   // void error(QNetworkReply::NetworkError);
    void quit();

private:
    void createActions();           // create actions
    void createMenus();             // create menus
    void createToolBar();           // create toolbar
    void createCentralWidget();     // create central widget

private:
    QMenu* fileMenu;
    QMenu* toolMenu;
    QToolBar* fileToolBar;

    QAction* openAct;
    QAction* saveAct;
    QAction* quitAct;

    //QNetworkAccessManager *manager;
    //QNetworkReply *response;

    QLineEdit *lineEditUrl;
    QTextEdit *textEditData;
    QPushButton *pushButtonGet;
    QTreeWidget *treeWidgetFiles;

    QList<QTreeWidgetItem *> items;
    QTimer *timer;

    QVector<StationInfo*> stationInfoList;
    DownloadManager *downloadManager;

};

#endif // MAINWINDOW_H
