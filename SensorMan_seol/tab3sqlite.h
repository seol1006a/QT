#ifndef TAB3SQLITE_H
#define TAB3SQLITE_H

#include <QWidget>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDateTime>
#include <QChartView>
#include <QLineSeries>
#include <QDateTimeAxis>
#include <QTableWidgetItem>
#include <QDebug>
namespace Ui {
class Tab3sqlite;
}

class Tab3sqlite : public QWidget
{
    Q_OBJECT

public:
    explicit Tab3sqlite(QWidget *parent = nullptr);
    ~Tab3sqlite();

private:
    Ui::Tab3sqlite *ui;
    QSqlDatabase qSqlDatabase;
    QChart *pQChart;
    QChartView *pQChartView;
    QDateTimeAxis *pQDateTimeAxisX;
    QDateTime firstDateTime;
    QDateTime lastDateTime;

    QLineSeries *illuLine;
    QLineSeries *tempLine;
    QLineSeries *humiLine;

    QTableWidgetItem* pQTableWidgetItemId = nullptr;
    QTableWidgetItem* pQTableWidgetItemDate = nullptr;
    QTableWidgetItem* pQTableWidgetItemIllu = nullptr;
    QTableWidgetItem* pQTableWidgetItemTemp = nullptr;
    QTableWidgetItem* pQTableWidgetItemHumi = nullptr;

    void updateLastDateTime(bool);
    void updateLastDateTimeSql(bool);
private slots:
    void Tab3sqliteRecvDataSlot(QString);

    void on_pPBsearchDB_clicked();
    void on_pPBdeleteDB_clicked();
    void on_pPBClearChart_clicked();
};

#endif // TAB3SQLITE_H
