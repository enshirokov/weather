#include "timerwidget.h"
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>

TimerWidget::TimerWidget(QTime &dateTime, QDialog *parent)
    : QDialog(parent),
      _dateTime(dateTime)
{
    setWindowTitle("Timer");
    setWindowFlags(Qt::Window | Qt::WindowTitleHint | Qt::CustomizeWindowHint);

    QLabel *labelTime = new QLabel("Time:");
    QLabel *labelSplitterH = new QLabel(":");
    QLabel *labelSplitterM = new QLabel(":");

    _spinBoxHours = new QSpinBox;
    _spinBoxHours->setMinimum(0);
    _spinBoxHours->setMaximum(23);

    _spinBoxMinutes = new QSpinBox;
    _spinBoxMinutes->setMinimum(0);
    _spinBoxMinutes->setMaximum(59);

    _spinBoxSeconds = new QSpinBox;
    _spinBoxSeconds->setMinimum(0);
    _spinBoxSeconds->setMaximum(59);

    QHBoxLayout *layoutTimer = new QHBoxLayout;
    layoutTimer->addWidget(labelTime);
    layoutTimer->addWidget(_spinBoxHours);
    layoutTimer->addWidget(labelSplitterH);
    layoutTimer->addWidget(_spinBoxMinutes);
    layoutTimer->addWidget(labelSplitterM);
    layoutTimer->addWidget(_spinBoxSeconds);

    _pushButtonOk = new QPushButton("Ok");
    connect(_pushButtonOk, SIGNAL(clicked(bool)), this, SLOT(accept(bool)));

    _pushButtonCancel = new QPushButton("Cancel");
    connect(_pushButtonCancel, SIGNAL(clicked(bool)), this, SLOT(reject(bool)));

    _pushButtonNow = new QPushButton("Now");
    connect(_pushButtonNow, SIGNAL(clicked(bool)), this, SLOT(now(bool)));

    QHBoxLayout *layoutButtons = new QHBoxLayout;
    layoutButtons->addWidget(_pushButtonOk);
    layoutButtons->addWidget(_pushButtonCancel);
    layoutButtons->addWidget(_pushButtonNow);
    layoutButtons->addStretch();

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(layoutTimer);
    mainLayout->addLayout(layoutButtons);
    mainLayout->addStretch();

    this->setLayout(mainLayout);
}

void TimerWidget::accept(bool value)
{
    int hours = _spinBoxHours->value();
    int minutes = _spinBoxMinutes->value();
    int seconds = _spinBoxSeconds->value();

    _dateTime = QTime(hours, minutes, seconds);
    int mseconds = QTime(0, 0, 0).msecsTo(_dateTime);

    if(!_dateTime.isValid() || mseconds < 60000) {
        QMessageBox messageBox;
        messageBox.setWindowTitle("Error");
        messageBox.setText("incorrect time (must be over 1 minute)");
        messageBox.exec();

        return;
    }

    QDialog::accept();

    this->close();
}

void TimerWidget::reject(bool value)
{
    QDialog::reject();

    this->close();
}

void TimerWidget::now(bool value)
{
    _dateTime = QTime(0, 0, 0);

    QDialog::accept();

    this->close();
}

