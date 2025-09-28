#ifndef TAB1SOCKET_H
#define TAB1SOCKET_H

#include <QWidget>
#include <QDebug>
#include <QTime>
#include <QLineEdit>
#include "socketclient.h"
#include "keyboard.h"

namespace Ui {
class Tab1Socket;
}

class Tab1Socket : public QWidget
{
    Q_OBJECT

public:
    explicit Tab1Socket(QWidget *parent = nullptr);
    ~Tab1Socket();
    SocketClient * getpSocketClient();


private slots:
    void on_pPBserverConnect_toggled(bool checked);
    void updateRecvDataSlot(QString);
    void on_pPBrecvDataClear_clicked();
    //void on_pPBSend_clicked();
    //void on_pLErecvId_selectionChanged();

    //void on_pLEsendData_selectionChanged();

    //void on_pPBserverConnect_clicked();

signals:
    void ledWriteSig(int);
    void Tab2SensorRecvDataSig(QString);
    void Tab3sqliteRecvDataSig(QString);
private:
    Ui::Tab1Socket *ui;
    SocketClient *pSocketClient;
    Keyboard *pKeyBoard;
};


#endif // TAB1SOCKET_H
