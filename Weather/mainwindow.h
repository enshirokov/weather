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

#include <QSettings>

#include <QVector>

#include "downloadmanager.h"
#include "stationinfo.h"

#include "databasewidget.h"
#include "timerwidget.h"

static const int ICON_SIZE = 64;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

signals:
    void getTables(WeatherItem*);
    void init();

private slots:
    //void request();
    void addData(quint64);
   // void error(QNetworkReply::NetworkError);
    void quit();
    void openDataBase(bool);
    void openTimer(bool);
    void timeout();
    void store();
    void restore();
    void itemClicked(QTreeWidgetItem*,int);

private:
    void createActions();           // create actions
    void createMenus();             // create menus
    void createToolBar();           // create toolbar
    void createCentralWidget();     // create central widget
    void storeSettings();
    void restoreSettings();

private:
    QMenu* fileMenu;
    QMenu* toolMenu;
    QToolBar* toolBar;

    QAction* dbAct;
    QAction* timerAct;
    QAction* quitAct;

    //QNetworkAccessManager *manager;
    //QNetworkReply *response;

    QTextEdit *textEditData;
    QTreeWidget *treeWidgetFiles;

    QList<QTreeWidgetItem *> items;
    QTimer *timer;

    QVector<StationInfo> _stationInfoList;
    QMap<quint64, WeatherItem*> _weatherItemList;
    DownloadManager *downloadManager;

    QString path;


};

#endif // MAINWINDOW_H
