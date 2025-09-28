#include "tab2sensor.h"
#include "ui_tab2sensor.h"

tab2Sensor::tab2Sensor(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::tab2Sensor)
{
    ui->setupUi(this);
    illuLine = new QLineSeries(this);
    illuLine->setName("조도");
    tempLine = new QLineSeries(this);
    tempLine->setName("온도");
    humiLine = new QLineSeries(this);
    humiLine->setName("습도");

    QPen pen;
    pen.setWidth(2);
    pen.setBrush(Qt::red);
    pen.setCapStyle(Qt::FlatCap);
    pen.setJoinStyle(Qt::MiterJoin);
    illuLine->setPen(pen);

    QPen pentemp;
    pentemp.setWidth(2);
    pentemp.setBrush(Qt::green);
    pentemp.setCapStyle(Qt::FlatCap);
    pentemp.setJoinStyle(Qt::MiterJoin);
    tempLine->setPen(pentemp);

    QPen penhumi;
    penhumi.setWidth(2);
    penhumi.setBrush(Qt::blue);
    penhumi.setCapStyle(Qt::FlatCap);
    penhumi.setJoinStyle(Qt::MiterJoin);
    humiLine->setPen(penhumi);

    pQChart = new QChart();
    pQChart->addSeries(illuLine);
    pQChart->addSeries(tempLine);
    pQChart->addSeries(humiLine);

    pQChart->createDefaultAxes();
    pQChart->axes(Qt::Vertical).constFirst()->setRange(0, 100);

    pQChartView = new QChartView(pQChart);
    pQChartView->setRenderHint(QPainter::Antialiasing);

    ui->pChartViewLayout->layout()->addWidget(pQChartView);
    pQDateTimeAxisX = new QDateTimeAxis;
    pQDateTimeAxisX->setFormat("hh:mm");
    //    pQDateTimeAxisX->setFormat("MM-dd hh:mm");

    updateLastDateTime(0);
    pQChartView->chart()->setAxisX(pQDateTimeAxisX,illuLine);
    pQChartView->chart()->setAxisX(pQDateTimeAxisX, tempLine);
    pQChartView->chart()->setAxisX(pQDateTimeAxisX, humiLine);

}





void tab2Sensor::updateLastDateTime(bool bFlag)
{
    QDate date = QDate::currentDate();
    QTime time = QTime::currentTime();

    firstDateTime.setDate(date);
    firstDateTime.setTime(time);

    lastDateTime.setDate(date);
    QTime tempTime = time.addSecs(10*60);  //10분
    lastDateTime.setTime(tempTime);

    pQDateTimeAxisX->setRange(firstDateTime,lastDateTime);
}
tab2Sensor::~tab2Sensor()
{
    delete ui;
}

void tab2Sensor::tab2RecvDataSlot(QString recvData)
{
    QDate date = QDate::currentDate();
    QTime time = QTime::currentTime();
    QDateTime xValue;
    xValue.setDate(date);
    xValue.setTime(time);

    QStringList strList = recvData.split("@");   //recvData : [SENSIRID]SENSOR@조도@온도@습도
    QString illu  = strList[3];     //조도
    illuLine->append(xValue.toMSecsSinceEpoch(),illu.toInt());
    // qDebug() << illu ;

    QString temp  = strList[4];     //온도
    tempLine->append(xValue.toMSecsSinceEpoch(),temp.toDouble());
    // qDebug() << temp ;

    QString humi  = strList[5];     //습도
    humiLine->append(xValue.toMSecsSinceEpoch(),humi.toDouble());
    // qDebug() << humi ;
}

void tab2Sensor::on_pPBClearChart_clicked()
{
    illuLine->clear();
    tempLine->clear();
    humiLine->clear();
    updateLastDateTime(0);
}

