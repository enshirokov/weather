#ifndef DATABASEWIDGET_H
#define DATABASEWIDGET_H

#include <QWidget>
#include <QLineEdit>
#include <QTableWidget>
#include <QPushButton>
#include <QDialog>

#include "stationinfo.h"

class DataBaseWidget : public QDialog
{
    Q_OBJECT
public:
    explicit DataBaseWidget(QString &path, QVector<StationInfo> &stationList, QDialog *parent = 0);

signals:

private slots:
    void quit(bool);
    void editPath(bool);
    void addItem(bool);

private:
    QLineEdit       *lineEditPath;          // путь к базе данных
    QTableWidget    *tableWidgetDataBase;   // таблица данных
    QPushButton     *pushButtonEditPath;
    QPushButton     *pushButtonAdd;         // кнопка "Добавить"
    QPushButton     *pushButtonRemove;      // кнопка "Удалить"
    QPushButton     *pushButtonEdit;        // кнопка "Изменить"
    QPushButton     *pushButtonOk;          // кнопка "Ok"

    QString                &_path;
    QVector<StationInfo>  &_stationList;

};

#endif // DATABASEWIDGET_H
