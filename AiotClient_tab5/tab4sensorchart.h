#ifndef TAB4SENSORCHART_H
#define TAB4SENSORCHART_H

#include <QWidget>
#include <QChartView>
#include <QLineSeries>
#include <QDateTimeAxis>
#include <QDate>
#include <QTime>
#include <QDebug>
#if QT_VERSION < QT_VERSION_CHECK(6,0,0)

#endif
namespace Ui {
class Tab4SensorChart;
}

class Tab4SensorChart : public QWidget
{
    Q_OBJECT

public:
    explicit Tab4SensorChart(QWidget *parent = nullptr);
    ~Tab4SensorChart();

private:
    Ui::Tab4SensorChart *ui;
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
    void tab4RecvDataSlot(QString);
    void on_pPBClearChart_clicked();
};

#endif // TAB4SENSORCHART_H
