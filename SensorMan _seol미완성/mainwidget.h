#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QWidget>
#include "tab1socket.h"
#include "tab2sensor.h"
#include "tab3sqlite.h"

namespace Ui {
class MainWidget;
}

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MainWidget(QWidget *parent = nullptr);
    ~MainWidget();

private:
    Ui::MainWidget *ui;
    SocketClient *psocketClient;
    tab1Socket *ptab1Socket;
    tab2Sensor *ptab2Sensor;
    tab3Sqlite *ptab3Sqlite;
};

#endif // MAINWIDGET_H
