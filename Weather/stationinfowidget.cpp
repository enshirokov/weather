#include "stationinfowidget.h"
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QMessageBox>

StationInfoWidget::StationInfoWidget(StationInfo& station, QDialog *parent)
    : _station(station), QDialog(parent)
{
    setWindowTitle("Station");
    setWindowFlags(Qt::Window | Qt::WindowTitleHint | Qt::CustomizeWindowHint);

    QLabel *labelName = new QLabel("Name:");
    lineEditName = new QLineEdit;

    QLabel *labelUrl = new QLabel("Url:");
    lineEditUrl = new QLineEdit("http://");

    QGridLayout *layoutData = new QGridLayout;
    layoutData->addWidget(labelName, 0, 0, 1, 1);
    layoutData->addWidget(lineEditName, 0, 1, 1, 10);
    layoutData->addWidget(labelUrl, 1, 0, 1, 1);
    layoutData->addWidget(lineEditUrl, 1, 1, 1, 10);


    pushButtonOk = new QPushButton("Ok");
    connect(pushButtonOk, SIGNAL(clicked(bool)), this, SLOT(accept(bool)));

    pushButtonCancel = new QPushButton("Cancel");
    connect(pushButtonCancel, SIGNAL(clicked(bool)), this, SLOT(reject(bool)));

    QHBoxLayout *layoutButtons = new QHBoxLayout;
    layoutButtons->addWidget(pushButtonOk);
    layoutButtons->addWidget(pushButtonCancel);
    layoutButtons->addStretch();

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(layoutData);
    mainLayout->addLayout(layoutButtons, 0);
    mainLayout->addStretch();

    this->setLayout(mainLayout);
}

void StationInfoWidget::accept(bool value)
{
    if(lineEditName->text().isEmpty()) {
        QMessageBox messageBox;
        messageBox.setWindowTitle("Error");
        messageBox.setText("Input station name");
        messageBox.exec();

        return;
    }


    _station.name = lineEditName->text();
    _station.url = lineEditUrl->text();

    QDialog::accept();

    this->close();
}

void StationInfoWidget::reject(bool value)
{
    QDialog::reject();

    this->close();
}

