#include "downloadmanager.h"
#include <QUrl>

DownloadManager::DownloadManager(QObject *parent) : QObject(parent)
{
    manager = new QNetworkAccessManager();
}

void DownloadManager::request()
{
    QString url = lineEditUrl->text();
    response = manager->get(QNetworkRequest(QUrl(url)));
    connect(response,SIGNAL(finished()),this,SLOT(getData()));
    connect(response, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(error(QNetworkReply::NetworkError)));
}

void DownloadManager::getData()
{
    QString text = response->readAll();

    QString timeText = QDateTime::currentDateTime().toString("HH:mm:ss");

    QString path = QDir::homePath() + "/Weather/" + timeText + ".weather";
    QFile file(path);
    if (!file.open(QIODevice::WriteOnly)) {
        qDebug() << "error open file";
            return;
    }

    file.write(text.toLocal8Bit().data());
    file.close();
}

void DownloadManager::error(QNetworkReply::NetworkError code)
{
    qDebug() << QString("error %1").arg(code);
}

