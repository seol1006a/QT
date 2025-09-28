#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QDebug>
#include "webcamthread.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWidget;
}
QT_END_NAMESPACE

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    MainWidget(QWidget *parent = nullptr);
    ~MainWidget();

private slots:


    void on_pPBcamStart_clicked(bool checked);

    void on_pPBsnapShot_clicked();

private:
    Ui::MainWidget *ui;
    WebCamThread *pWebCamThread;
};
#endif // MAINWIDGET_H
