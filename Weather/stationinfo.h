#ifndef STATIONINFO
#define STATIONINFO

#include <QString>
#include <QVector>
#include <QDataStream>

struct StationInfo
{
    QString name;    // название станции (будет отображено в дереве истории)
    QString url;     // url откуда брать таблицу
    QString path;    // путь к файлу с сохраненной таблицей
    QString error;   // ошибка

    void read(QDataStream &dataStream)
    {
        dataStream >> name;
        dataStream >> url;
        dataStream >> path;
        dataStream >> error;
    }

    void write(QDataStream &dataStream)
    {
        dataStream << name;
        dataStream << url;
        dataStream << path;
        dataStream << error;
    }

};

struct WeatherItem
{
    quint64 id;
    QString date;
    QVector<StationInfo> stations;
};

#endif // STATIONINFO

