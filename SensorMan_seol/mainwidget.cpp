#include "mainwidget.h"
#include "ui_mainwidget.h"

MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainWidget)
{
    ui->setupUi(this);
    pTab1Socket = new Tab1Socket(ui->Socket);
    ui->Socket->setLayout(pTab1Socket->layout());

    pTab2Sensor = new Tab2Sensor(ui->Sensor);
    ui->Sensor->setLayout(pTab2Sensor->layout());

    pTab3sqlite = new Tab3sqlite(ui->sqlite);
    ui->sqlite->setLayout(pTab3sqlite->layout());

    ui->ptabWidget->setCurrentIndex(0);

    connect(pTab1Socket, SIGNAL(Tab2SensorRecvDataSig(QString)), pTab2Sensor, SLOT(Tab2SensorRecvDataSlot(QString)));
    connect(pTab1Socket, SIGNAL(Tab3sqliteRecvDataSig(QString)), pTab3sqlite, SLOT(Tab3sqliteRecvDataSlot(QString)));

}

MainWidget::~MainWidget()
{
    delete ui;
}
