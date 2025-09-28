#include "mainwidget.h"
#include "ui_mainwidget.h"

MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainWidget)
{

    ui->setupUi(this);
    ptab1Socket = new tab1Socket(ui->pTab1);
    ui->pTab1->setLayout(ptab1Socket->layout());

    ptab2Sensor = new tab2Sensor(ui->pTab2);
    ui->pTab2->setLayout(ptab2Sensor->layout());

    ptab3Sqlite = new tab3Sqlite(ui->pTab3);
    ui->pTab3->setLayout(ptab3Sqlite->layout());

    ui->pTabWidgets->setCurrentIndex(2);


    connect(ptab1Socket, SIGNAL(tab2RecvDataSig(QString)), ptab2Sensor, SLOT(tab2RecvDataSlot(QString)));
    connect(ptab1Socket, SIGNAL(tab3RecvDataSig(QString)), ptab3Sqlite, SLOT(tab3RecvDataSlot(QString)));
}

MainWidget::~MainWidget()
{
    delete ui;
}
