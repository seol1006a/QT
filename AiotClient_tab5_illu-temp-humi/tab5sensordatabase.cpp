#include "tab5sensordatabase.h"
#include "ui_tab5sensordatabase.h"

Tab5SensorDatabase::Tab5SensorDatabase(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Tab5SensorDatabase)
{
    ui->setupUi(this);
    qSqlDatabase = QSqlDatabase::addDatabase("QSQLITE");  //싱글톤 : 시간,등은 프로젝트 내에서 한번만 생성
    qSqlDatabase.setDatabaseName("aiot.db");
    if(qSqlDatabase.open()) //db가 정상적으로 열렸는지 확인
        qDebug() << "Success DB Connection";
    else
        qDebug() << "Fail DB Connection";
    QString strQuery = "create table sensor_tb (" //SQL문 입력(sensor_tb 생성, 초기값 설정)
                        "name varchar(10),"
                        "date DATETIME primary key,"
                       "illu varchar(10))";
    QSqlQuery sqlQuery;
    if(sqlQuery.exec(strQuery)) //성공하면 true 리턴
        qDebug() << "Create Table";


    illuLine = new QLineSeries(this);
    illuLine->setName("조도");
    tempLine = new QLineSeries(this);
    tempLine->setName("온도");
    humiLine = new QLineSeries(this);
    humiLine->setName("습도");

    QPen pen;  //속성 지정
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
    pQChart->axes(Qt::Vertical).constFirst()->setRange(0, 100); //세로축

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
    // qDebug() << ">>> tab5RecvDataSlot called!";
/*    QDate date = QDate::currentDate();
    QTime time = QTime::currentTime();
    QDateTime xValue;
    xValue.setDate(date);
    xValue.setTime(time);*/

    QDateTime dateTime = QDateTime::currentDateTime(); //한번에 시간날짜 가져오기

    QStringList strList = recvData.split("@");   //recvData : [SENSIRID]SENSOR@조도@온도@습도
    QString name = strList[1]; //ID ex)HM_CON
    QString illu  = strList[3];     //조도
    illuLine->append(dateTime.toMSecsSinceEpoch(),illu.toInt());
    qDebug() << illu ;

    QString temp  = strList[4];     //온도
    tempLine->append(dateTime.toMSecsSinceEpoch(),temp.toDouble());
    qDebug() << temp ;

    QString humi  = strList[5];     //습도
    humiLine->append(dateTime.toMSecsSinceEpoch(),humi.toDouble());
    qDebug() << humi ;


    //받아온 illu값을 table에 저장하기
    QString strQuery = "insert into sensor_tb(name, date, illu) values('" + name + "', '" + dateTime.toString("yyyy/MM/dd hh:mm:ss") + "','" + illu + "')";
    QSqlQuery sqlQuery;
    if(sqlQuery.exec(strQuery)) //성공하면 true 리턴
        qDebug() << "Insert Query OK";
}


Tab5SensorDatabase::~Tab5SensorDatabase()
{
    delete ui;
}



void Tab5SensorDatabase::on_pPOdeleteDB_2_clicked()
{
    illuLine->clear();
    tempLine->clear();
    humiLine->clear();
    updateLastDateTime(0);
}


void Tab5SensorDatabase::on_pPBsearchDB_clicked() //조회 클릭(시작, 끝)
{

    QDateTime fromDateTime = ui->pDateTimeEditFrom->dateTime();
    QString strFromDateTime = fromDateTime.toString("yyyy/MM/dd hh:mm:ss");
    QDateTime toDateTime = ui->pDateTimeEditTo->dateTime();
    QString strToDateTime = toDateTime.toString("yyyy/MM/dd hh:mm:ss");

    ui->pTBsensor->clearContents(); //이전의 데이터를 지우기
    on_pPOdeleteDB_2_clicked(); //시간 업데이트

    QString strQuery = "select * from sensor_tb where '" + strFromDateTime + "' <= date and date <= '" + strToDateTime + "'";

    QSqlQuery sqlQuery;
    if(sqlQuery.exec(strQuery)) //성공하면 true 리턴
    {
        int rowCount=0;

        qDebug() << "Select Query OK";
        while(sqlQuery.next())
        {
            rowCount++;
            ui->pTBsensor->setRowCount(rowCount); //1번부터 지정(1번 레코드 테이블 위젯), 행 지정
            QTableWidgetItem * pQTableWidgetItemId = new QTableWidgetItem(); //필드선택을 위함(ID, 날짜, 조도)
            QTableWidgetItem * pQTableWidgetItemDate = new QTableWidgetItem();
            QTableWidgetItem * pQTableWidgetItemIllu = new QTableWidgetItem();

            pQTableWidgetItemId->setText(sqlQuery.value("name").toString());
            pQTableWidgetItemDate->setText(sqlQuery.value("date").toString());
            pQTableWidgetItemIllu->setText(sqlQuery.value("illu").toString());


            ui->pTBsensor->setItem(rowCount-1, 0,pQTableWidgetItemId );
            ui->pTBsensor->setItem(rowCount-1, 1,pQTableWidgetItemDate );
            ui->pTBsensor->setItem(rowCount-1, 2,pQTableWidgetItemIllu );


            QString illu = sqlQuery.value("illu").toString();
            QDateTime dateTime = sqlQuery.value("date").toDateTime();
            QString strPdateTime = dateTime.toString(("hh:mm"));

            illuLine->append(dateTime.toMSecsSinceEpoch(),illu.toInt());
            qDebug() << illu ;
            qDebug() << dateTime;
            qDebug() << rowCount;
        }
    }
}




void Tab5SensorDatabase::on_pPOdeleteDB_clicked()
{
    QDateTime fromDateTime = ui->pDateTimeEditFrom->dateTime();
    QString strFromDateTime = fromDateTime.toString("yyyy/MM/dd hh:mm:ss");
    QDateTime toDateTime = ui->pDateTimeEditTo->dateTime();
    QString strToDateTime = toDateTime.toString("yyyy/MM/dd hh:mm:ss");

    ui->pTBsensor->clearContents(); //이전의 데이터를 지우기
    on_pPOdeleteDB_2_clicked(); //시간 업데이트

    QString strQuery = "DELETE from sensor_tb where '" + strFromDateTime + "' <= date and date <= '" + strToDateTime + "'";

    QSqlQuery sqlQuery;
    if(sqlQuery.exec(strQuery)) //성공하면 true 리턴
        qDebug() << "Delete Query OK";
}

