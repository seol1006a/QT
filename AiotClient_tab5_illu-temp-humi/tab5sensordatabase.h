#ifndef TAB5SENSORDATABASE_H
#define TAB5SENSORDATABASE_H

#include <QWidget>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSQlError>
#include <QDateTime>
#include <QChartView>
#include <QLineSeries>
#include <QDateTimeAxis>  //좌표활용
#include <QDebug>

namespace Ui {
class Tab5SensorDatabase;
}

class Tab5SensorDatabase : public QWidget
{
    Q_OBJECT

public:
    explicit Tab5SensorDatabase(QWidget *parent = nullptr);
    ~Tab5SensorDatabase();

private:
    Ui::Tab5SensorDatabase *ui;
    QSqlDatabase qSqlDatabase;
    QLineSeries *illuLine;
    QChart *pQChart;
    QChartView *pQChartView;
    QDateTimeAxis *pQDateTimeAxisX;
    QDateTime firstDateTime;
    QDateTime lastDateTime;

    QLineSeries *tempLine;
    QLineSeries *humiLine;

    void updateLastDateTime(bool Flag);
private slots:
    void tab5RecvDataSlot(QString);
    void on_pPOdeleteDB_2_clicked();
    void on_pPBsearchDB_clicked();
    void on_pPOdeleteDB_clicked();
};

#endif // TAB5SENSORDATABASE_H
