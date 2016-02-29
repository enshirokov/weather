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

void DownloadManager::getTables(QVector<StationInfo*> list)
{
    stationInfoList = list;
    stationInfoIter = list.begin();

    QString timeText = QDateTime::currentDateTime().toString("dd:MM:yyyy");
    dateText = timeText;

    request();
}

void DownloadManager::request()
{
    if(stationInfoIter == stationInfoList.end()){
        emit done();
        return;
    }

    QUrl url = QUrl((*stationInfoIter)->url);
    response = manager->get(QNetworkRequest(url));
    connect(response,SIGNAL(finished()),this,SLOT(getData()));
    connect(response, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(error(QNetworkReply::NetworkError)));
}

void DownloadManager::getData()
{
    QByteArray rawData = response->readAll();

    QString text = QTextCodec::codecForName("cp1251")->toUnicode(rawData);

    QString path = QDir::homePath() + "/Weather/" + dateText + "/" + (*stationInfoIter)->name + ".weather";

    QFile file(path);
    if (!file.open(QIODevice::WriteOnly)) {
        QString error = "error open file";
        (*stationInfoIter)->error = error;
        return;
    }

    file.write(text.toLocal8Bit().data());
    file.close();

    (*stationInfoIter)->path = path;

    request();
}

void DownloadManager::error(QNetworkReply::NetworkError code)
{
    QString error = QString("error %1").arg(code);
    (*stationInfoIter)->error = error;
}

