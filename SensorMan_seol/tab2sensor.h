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
class Tab2Sensor;
}

class Tab2Sensor : public QWidget
{
    Q_OBJECT

public:
    explicit Tab2Sensor(QWidget *parent = nullptr);
    ~Tab2Sensor();

private:
    Ui::Tab2Sensor *ui;
    QChart *pQChart;
    QChartView *pQChartView;
    QDateTimeAxis *pQDateTimeAxisX;
    QDateTime firstDateTime;
    QDateTime lastDateTime;

    QLineSeries *illuLine;
    QLineSeries *tempLine;
    QLineSeries *humiLine;

    void updateLastDateTime(bool bFlag);

private slots:
    void Tab2SensorRecvDataSlot(QString);
    void on_pPBClearChart_3_clicked();
};

#endif // TAB2SENSOR_H
