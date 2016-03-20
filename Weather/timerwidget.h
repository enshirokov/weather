#ifndef TIMERWIDGET_H
#define TIMERWIDGET_H

#include <QDialog>
#include <QSpinBox>
#include <QDateTime>
#include <QPushButton>

class TimerWidget : public QDialog
{
    Q_OBJECT
public:
    explicit TimerWidget(QTime &dateTime, QDialog *parent = 0);

signals:

private slots:
    void accept(bool);
    void reject(bool);
    void now(bool);

private:
    QSpinBox *_spinBoxHours;
    QSpinBox *_spinBoxMinutes;
    QSpinBox *_spinBoxSeconds;

    QPushButton *_pushButtonOk;
    QPushButton *_pushButtonCancel;
    QPushButton *_pushButtonNow;

    QTime &_dateTime;
};

#endif // TIMERWIDGET_H
