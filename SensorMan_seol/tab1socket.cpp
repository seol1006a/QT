#include "tab1socket.h"
#include "ui_tab1socket.h"

Tab1Socket::Tab1Socket(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Tab1Socket)
{
    ui->setupUi(this);
    pKeyBoard = new Keyboard();
    ui->pPBSend->setEnabled(false);
    pSocketClient = new SocketClient(this);
    connect(pSocketClient, SIGNAL(socketRecvDataSig(QString)),this, SLOT(updateRecvDataSlot(QString)));
}

Tab1Socket::~Tab1Socket()
{
    delete ui;
}

void Tab1Socket::on_pPBserverConnect_toggled(bool checked)
{
    bool bFlag;
    //    qDebug() << "on_pPBserverConnect_toggled()";
    if(checked)
    {
        pSocketClient->connectToServerSlot(bFlag);
        if(bFlag)
        {
            ui->pPBserverConnect->setText("서버 해제");
            ui->pPBSend->setEnabled(true);
        }
    }
    else {
        pSocketClient->socketClosedServerSlot();
        ui->pPBserverConnect->setText("서버 연결");
        ui->pPBSend->setEnabled(false);
    }
}

void Tab1Socket::updateRecvDataSlot(QString strRecvData)
{
    strRecvData.chop(1);   //끝문자 한개 "\n" 제거
    QTime time = QTime::currentTime();
    QString strTime = time.toString();
    strTime = strTime + " " + strRecvData;
    ui->pTErecvData->append(strTime);

    //[KSH_QT]@LED@0xff  ==> @KSH_QT@LED@0xff
    strRecvData.replace("[","@");
    strRecvData.replace("]","@");
    QStringList strList = strRecvData.split("@");

    if(strList[2].indexOf("SENSOR") == 0)
    {
        emit Tab2SensorRecvDataSig(strRecvData);
        emit Tab3sqliteRecvDataSig(strRecvData);
    }
}


void Tab1Socket::on_pPBrecvDataClear_clicked()
{
    QString strRecvId = ui->pLErecvId->text();
    QString strSendData = ui->pLEsendData->text();
    if(strRecvId.isEmpty())
    {
        strSendData = "[ALLMSG]" + strSendData;
    }
    else
    {
        strSendData = "["+strRecvId+"]" + strSendData;
    }
    pSocketClient->socketWriteDataSlot(strSendData);
    ui->pLEsendData->clear();
}

SocketClient * Tab1Socket::getpSocketClient()
{
    return pSocketClient;
}
