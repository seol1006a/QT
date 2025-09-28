#ifndef TAB1SOCKET_H
#define TAB1SOCKET_H

#include <QMainWindow>
#include <QWidget>
#include <QDebug>
#include <QTime>
#include <QLineEdit>
#include "socketclient.h"
#include "keyboard.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class tab1Socket;
}
QT_END_NAMESPACE

class tab1Socket : public QMainWindow
{
    Q_OBJECT

public:
    tab1Socket(QWidget *parent = nullptr);
    ~tab1Socket();
    SocketClient * getpSocketClient();

private slots:
    void  updateRecvDataSlot(QString);
    void on_pPBServerConnect_toggled(bool checked);

    void on_pPBDataClear_clicked();

    void on_pPBSend_clicked();

    void on_pLErecvId_selectionChanged();

    void on_pLEsendData_selectionChanged();
    void socketSendToLinux(int);

signals:
    void tab2RecvDataSig(QString);
    void tab3RecvDataSig(QString);

private:
    Ui::tab1Socket *ui;
    SocketClient *pSocketClient;
    Keyboard *pKeyBoard;

};
#endif // TAB1SOCKET_H
