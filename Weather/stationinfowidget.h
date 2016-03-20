#ifndef STATIONINFOWIDGET_H
#define STATIONINFOWIDGET_H

#include <QDialog>
#include <QLineEdit>
#include <QPushButton>

#include "stationinfo.h"

class StationInfoWidget : public QDialog
{
    Q_OBJECT
public:
    explicit StationInfoWidget(StationInfo& station, QDialog *parent = 0);

signals:
    void updated();

private slots:
    void accept(bool);
    void reject(bool);

private:
    QLineEdit *lineEditName;
    QLineEdit *lineEditUrl;

    QPushButton *pushButtonOk;
    QPushButton *pushButtonCancel;

    StationInfo& _station;

};

#endif // STATIONINFOWIDGET_H
