#include "tab5sensordatabase.h"
#include "ui_tab5sensordatabase.h"

Tab5SensorDatabase::Tab5SensorDatabase(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Tab5SensorDatabase)
{
    ui->setupUi(this);
    qSqlDatabase = QSqlDatabase::addDatabase("QSQLITE");
    qSqlDatabase.setDatabaseName("aiot.db");
    if(qSqlDatabase.open())
        qDebug() << "Success DB Connection";
    else
        qDebug() << "Fail DB Connection";
    QString strQuery = "create table sensor_tb ("
                       "name varchar(10),"
                       "date DATETIME primary key,"
                       "illu varchar(10),"
                       "temp varchar(10),"
                       "humi varchar(10))";

    QSqlQuery sqlQuery;
    if(sqlQuery.exec(strQuery))
        qDebug() << "Create Table";


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

void Tab5SensorDatabase::updateLastDateTime(bool bFlag)
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

void Tab5SensorDatabase::tab5RecvDataSlot(QString recvData)
{

    QDateTime dateTime = QDateTime::currentDateTime();
    QStringList strList = recvData.split("@");   //recvData : [SENSIRID]SENSOR@조도@온도@습도
    QString name = strList[1];
    QString illu  = strList[3];     //조도
    illuLine->append(dateTime.toMSecsSinceEpoch(),illu.toInt());
    qDebug() << illu ;

    QString temp  = strList[4];     //온도
    tempLine->append(dateTime.toMSecsSinceEpoch(),temp.toDouble());
    qDebug() << temp ;

    QString humi  = strList[5];     //습도
    humiLine->append(dateTime.toMSecsSinceEpoch(),humi.toDouble());
    qDebug() << humi ;

    QString strQuery = "insert into sensor_tb(name, date, illu, temp, humi) values('" +
                       name + "', '" + dateTime.toString("yyyy/MM/dd hh:mm:ss") + "' , '" +
                       illu + "', '" + temp + "', '" + humi + "')";
    QSqlQuery sqlQuery;
    if(sqlQuery.exec(strQuery))
        qDebug() << "Insert Query Ok";

}

Tab5SensorDatabase::~Tab5SensorDatabase()
{
    delete ui;
}

void Tab5SensorDatabase::on_pPBClearChart_clicked()
{
    illuLine->clear();
    tempLine->clear();
    humiLine->clear();
    updateLastDateTime(0);
}

void Tab5SensorDatabase::on_pPBsearchDB_clicked()
{
    QDateTime fromDateTime = ui->pDateTimeEditFrom->dateTime();
    QString strFromDateTime = fromDateTime.toString("yyyy/MM/dd hh:mm:ss");
    QDateTime toDateTime = ui->pDateTimeEditTo->dateTime();
    QString strToDateTime = toDateTime.toString("yyyy/MM/dd hh:mm:ss");

//    ui->pTBsensor->clearContents();
//    on_pPBClearChart_clicked();
    updateLastDateTimeSql(0);
    illuLine->clear();
    tempLine->clear();
    humiLine->clear();

    QString strQuery = "select * from sensor_tb where '" + strFromDateTime + "'  <= date and date <= '" + strToDateTime + "' ";
    QSqlQuery sqlQuery;
    if(sqlQuery.exec(strQuery))
    {
        int rowCount=0;
        qDebug() << "Select Query Ok";
        while(sqlQuery.next())
            rowCount++;

        if (pQTableWidgetItemId != nullptr)
        {
            delete[] pQTableWidgetItemId;
            delete[] pQTableWidgetItemDate;
            delete[] pQTableWidgetItemIllu;
            delete[] pQTableWidgetItemTemp;
            delete[] pQTableWidgetItemHumi;
        }

        pQTableWidgetItemId = new QTableWidgetItem[rowCount];
        pQTableWidgetItemDate = new QTableWidgetItem[rowCount];
        pQTableWidgetItemIllu = new QTableWidgetItem[rowCount];
        pQTableWidgetItemTemp = new QTableWidgetItem[rowCount];
        pQTableWidgetItemHumi = new QTableWidgetItem[rowCount];


        rowCount=0;
        sqlQuery.first();
        while(sqlQuery.next())
        {
            ui->pTBsensor->setRowCount(rowCount+1);

            (pQTableWidgetItemId+rowCount)->setText(sqlQuery.value("name").toString());
            (pQTableWidgetItemDate+rowCount)->setText(sqlQuery.value("date").toString());
            (pQTableWidgetItemIllu+rowCount)->setText(sqlQuery.value("illu").toString());
            (pQTableWidgetItemTemp + rowCount)->setText(sqlQuery.value("temp").toString());
            (pQTableWidgetItemHumi + rowCount)->setText(sqlQuery.value("humi").toString());

            ui->pTBsensor->setItem(rowCount,0, (pQTableWidgetItemId+rowCount));
            ui->pTBsensor->setItem(rowCount,1, (pQTableWidgetItemDate+rowCount));
            ui->pTBsensor->setItem(rowCount,2, (pQTableWidgetItemIllu+rowCount));
            ui->pTBsensor->setItem(rowCount,3, (pQTableWidgetItemTemp + rowCount));
            ui->pTBsensor->setItem(rowCount,4, (pQTableWidgetItemHumi + rowCount));

            QDateTime xValue = QDateTime::fromString((pQTableWidgetItemDate+rowCount)->text(), "yyyy/MM/dd hh:mm:ss");
            illuLine->append(xValue.toMSecsSinceEpoch(),(pQTableWidgetItemIllu+rowCount)->text().toInt());
            tempLine->append(xValue.toMSecsSinceEpoch(), (pQTableWidgetItemTemp + rowCount)->text().toDouble());
            humiLine->append(xValue.toMSecsSinceEpoch(), (pQTableWidgetItemHumi + rowCount)->text().toDouble());
            rowCount++;
        }
        ui->pTBsensor->resizeColumnToContents(0);
        ui->pTBsensor->resizeColumnToContents(1);
        ui->pTBsensor->resizeColumnToContents(2);
    }
}


void Tab5SensorDatabase::on_pPBdeleteDB_clicked()
{
    QDateTime fromDateTime = ui->pDateTimeEditFrom->dateTime();
    QString strFromDateTime = fromDateTime.toString("yyyy/MM/dd hh:mm:ss");
    QDateTime toDateTime = ui->pDateTimeEditTo->dateTime();
    QString strToDateTime = toDateTime.toString("yyyy/MM/dd hh:mm:ss");

    QString strQuery = "delete from sensor_tb where '" + strFromDateTime + "' <= date AND date <= '" + strToDateTime + "'";
    QSqlQuery sqlQuery;
    if(!sqlQuery.exec(strQuery))
        qDebug() << "Delete Query Ok";
\
//  ui->pTBsensor->clearContents();
    illuLine->clear();
    tempLine->clear();
    humiLine->clear();
}

void Tab5SensorDatabase::updateLastDateTimeSql(bool bFlag)
{
    QDateTime fromDateTime = ui->pDateTimeEditFrom->dateTime();
    QString strFromDateTime = fromDateTime.toString("yyyy/MM/dd hh:mm:ss");
    QDateTime toDateTime = ui->pDateTimeEditTo->dateTime();
    QString strToDateTime = toDateTime.toString("yyyy/MM/dd hh:mm:ss");

    QString strQuery = "select * from sensor_tb where '" + strFromDateTime + "' <= date AND date <= '" + strToDateTime + "'";
    QSqlQuery sqlQuery;
    if(sqlQuery.exec(strQuery))
    {
            sqlQuery.first();
            firstDateTime = QDateTime::fromString(sqlQuery.value("date").toString(), "yyyy/MM/dd hh:mm:ss");
            sqlQuery.last();
            lastDateTime = QDateTime::fromString(sqlQuery.value("date").toString(), "yyyy/MM/dd hh:mm:ss");
    }
    if(!firstDateTime.isValid())
        firstDateTime = QDateTime::fromString(strFromDateTime, "yyyy/MM/dd hh:mm:ss");
    if(!lastDateTime.isValid())
        lastDateTime = QDateTime::fromString(strToDateTime, "yyyy/MM/dd hh:mm:ss");
    pQDateTimeAxisX->setRange(firstDateTime,lastDateTime);
}
