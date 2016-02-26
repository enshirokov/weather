#ifndef DOWNLOADMANAGER_H
#define DOWNLOADMANAGER_H

#include <QObject>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>

class DownloadManager : public QObject
{
    Q_OBJECT
public:
    explicit DownloadManager(QObject *parent = 0);

signals:

public slots:
    void request();

private slots:
    void getData();
    void error(QNetworkReply::NetworkError);

private:
    QNetworkAccessManager *manager;
    QNetworkReply *response;
};

#endif // DOWNLOADMANAGER_H
