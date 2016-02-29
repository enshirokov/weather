#ifndef DOWNLOADMANAGER_H
#define DOWNLOADMANAGER_H

#include <QObject>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QVector>


#include "stationinfo.h"

class DownloadManager : public QObject
{
    Q_OBJECT
public:
    explicit DownloadManager(QObject *parent = 0);
    ~DownloadManager();

signals:
    void done();

public slots:
   void getTables(QVector<StationInfo*>);
   void init();

private slots:
    void request();
    void getData();
    void error(QNetworkReply::NetworkError);

private:
    QNetworkAccessManager *manager;
    QNetworkReply *response;

    QVector<StationInfo*> stationInfoList;
    QVector<StationInfo*>::iterator stationInfoIter;

    QString dateText;


};

#endif // DOWNLOADMANAGER_H
