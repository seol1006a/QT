#ifndef TAB2SENSOR_H
#define TAB2SENSOR_H

#include <QWidget>
#include <QChartView>
#include <QLineSeries>
#include <QDateTimeAxis>
#include <QDate>
#include <QTime>
#include <QDebug>

namespace Ui {
class tab2Sensor;
}

class tab2Sensor : public QWidget
{
    Q_OBJECT

public:
    explicit tab2Sensor(QWidget *parent = nullptr);
    ~tab2Sensor();

private:
    Ui::tab2Sensor *ui;
    QLineSeries *illuLine;
    QChart *pQChart;
    QChartView *pQChartView;
    QDateTimeAxis *pQDateTimeAxisX;
    QDateTime firstDateTime;
    QDateTime lastDateTime;

    QLineSeries *tempLine;
    QLineSeries *humiLine;

    void updateLastDateTime(bool bFlag);
private slots:
    void tab2RecvDataSlot(QString);
    void on_pPBClearChart_clicked();
};

#endif // TAB2SENSOR_H
