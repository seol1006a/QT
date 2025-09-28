#ifndef TAB3SQLITE_H
#define TAB3SQLITE_H


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
class tab3Sqlite;
}

class tab3Sqlite : public QWidget
{
    Q_OBJECT

public:
    explicit tab3Sqlite(QWidget *parent = nullptr);
    ~tab3Sqlite();

private:
    Ui::tab3Sqlite *ui;
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
    void tab3RecvDataSlot(QString);
    void on_pPOdeldeteDB_clicked();
    void on_pPBsertchDB_clicked();
};

#endif // TAB3SQLITE_H
