#ifndef STATIONINFO
#define STATIONINFO

#include <QString>
#include <QVector>

struct StationInfo
{
    QString name;    // название станции (будет отображено в дереве истории)
    QString url;     // url откуда брать таблицу
    QString path;    // путь к файлу с сохраненной таблицей
    QString error;   // ошибка
};

struct WeatherItem
{
    quint64 id;
    QString date;
    QVector<StationInfo> stations;
};

#endif // STATIONINFO

