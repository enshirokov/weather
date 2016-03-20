#include "databasewidget.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QFileDialog>
#include <QDir>
#include <QDebug>

#include "stationinfowidget.h"


DataBaseWidget::DataBaseWidget(QString &path, QVector<StationInfo> &stationList, QDialog *parent)
    : _path(path), _stationList(stationList), QDialog(parent)
{
    setWindowTitle("Database editor");

    // 1) Path
    QLabel *labelPath = new QLabel("Path:");
    lineEditPath = new QLineEdit(_path);
    pushButtonEditPath = new QPushButton("Edit");
    connect(pushButtonEditPath, SIGNAL(clicked(bool)), this, SLOT(editPath(bool)));

    QHBoxLayout *layoutPath = new QHBoxLayout;
    layoutPath->addWidget(labelPath);
    layoutPath->addWidget(lineEditPath);
    layoutPath->addWidget(pushButtonEditPath);

    // 2) Table

    pushButtonAdd = new QPushButton("Add");
    connect(pushButtonAdd, SIGNAL(clicked(bool)), this, SLOT(addItem(bool)));
    pushButtonEdit = new QPushButton("Edit");
    pushButtonRemove = new QPushButton("Remove");

    QVBoxLayout *layoutButtons = new QVBoxLayout;
    layoutButtons->addWidget(pushButtonAdd);
    layoutButtons->addWidget(pushButtonEdit);
    layoutButtons->addWidget(pushButtonRemove);
    layoutButtons->addStretch();

    tableWidgetDataBase = new QTableWidget;
    tableWidgetDataBase->setRowCount(0);
    tableWidgetDataBase->setColumnCount(1);

    for(int i = 0; i < _stationList.size(); i++) {
        int row = tableWidgetDataBase->rowCount();
        row++;

        QTableWidgetItem *newItem = new QTableWidgetItem(_stationList[i].name);
        tableWidgetDataBase->setRowCount(row);
        tableWidgetDataBase->setItem(row - 1, 0, newItem);

    }

    QHBoxLayout *layoutDataBase = new QHBoxLayout;
    layoutDataBase->addWidget(tableWidgetDataBase);
    layoutDataBase->addLayout(layoutButtons);
    //layoutDataBase->addStretch();

    pushButtonOk = new QPushButton("Ok");
    connect(pushButtonOk, SIGNAL(clicked(bool)), this, SLOT(quit(bool)));
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(layoutPath);
    mainLayout->addLayout(layoutDataBase);
    mainLayout->addWidget(pushButtonOk, 0, Qt::AlignRight);
    mainLayout->addStretch();


    this->setLayout(mainLayout);
}

void DataBaseWidget::quit(bool value)
{
    this->close();
}

void DataBaseWidget::editPath(bool value)
{
    _path = QFileDialog::getExistingDirectory(this,
        tr("Open data base path"), QDir::homePath() );

    lineEditPath->setText(_path);
}

void DataBaseWidget::addItem(bool value)
{
    StationInfo station;
    StationInfoWidget stationInfoWidget(station);

    int result = stationInfoWidget.exec();
    if (result == QDialog::Rejected) {

    }
    else if(result == QDialog::Accepted) {

        _stationList.push_back(station);

        int row = tableWidgetDataBase->rowCount();
        row++;

        QTableWidgetItem *newItem = new QTableWidgetItem(station.name);
        tableWidgetDataBase->setRowCount(row);
        tableWidgetDataBase->setItem(row - 1, 0, newItem);

    }
}

//void DataBaseWidget::update()
//{

//    /*
//    int row = tableWidgetDataBase->rowCount();
//    row++;

//    QTableWidgetItem *newItem = new QTableWidgetItem(QString::number(row));
//    tableWidget->setItem(row, 0, newItem);

//    tableWidget->setItem(row, column, newItem);

//    tableWidgetDataBase->add
//            */
//}
