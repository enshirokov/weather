#include "downloadmanager.h"
#include <QUrl>
#include <QTextCodec>
#include <QDir>
#include <QDateTime>

DownloadManager::DownloadManager(QObject *parent) : QObject(parent)
{

}

DownloadManager::~DownloadManager()
{
    if(manager != NULL)
        delete manager;

    if(response != NULL)
        delete response;
}

void DownloadManager::init()
{
    manager = new QNetworkAccessManager();
}

void DownloadManager::getTables(WeatherItem* item)
{
    _item = item;
    _index = 0;

    _item->date = QDateTime::currentDateTime().toString("dd:MM:yyyy");

    request();
}

void DownloadManager::request()
{
    if(_index >= _item->stations.size()){
        emit done(_item->id);
        return;
    }

    QUrl url = QUrl(_item->stations[_index].url);
    response = manager->get(QNetworkRequest(url));
    connect(response,SIGNAL(finished()),this,SLOT(getData()));
    connect(response, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(error(QNetworkReply::NetworkError)));
}

void DownloadManager::getData()
{
    QByteArray rawData = response->readAll();

    QString text = QTextCodec::codecForName("cp1251")->toUnicode(rawData);

    QString path = QDir::homePath() + "/Weather/" + _item->date + "/" + _item->stations[_index].name + ".weather";

    QFile file(path);
    if (!file.open(QIODevice::WriteOnly)) {
        QString error = "error open file";
        _item->stations[_index].error = error;
        return;
    }

    file.write(text.toLocal8Bit().data());
    file.close();

    _item->stations[_index].path = path;

    _index++;

    request();
}

void DownloadManager::error(QNetworkReply::NetworkError code)
{
    QString error = QString("error %1").arg(code);
    _item->stations[_index].error = error;
}

