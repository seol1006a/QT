#include "tab1socket.h"
#include "ui_tab1socket.h"

tab1Socket::tab1Socket(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::tab1Socket)
{
    ui->setupUi(this);
    pKeyBoard = new Keyboard();
    ui->pPBSend->setEnabled(false);
    pSocketClient = new SocketClient(this);
    connect(pSocketClient, SIGNAL(socketRecvDataSig(QString)),this, SLOT(updateRecvDataSlot(QString)));
}

tab1Socket::~tab1Socket()
{
    delete ui;
}


void tab1Socket::on_pPBServerConnect_toggled(bool checked)
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

void tab1Socket::updateRecvDataSlot(QString strRecvData)
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
        emit tab2RecvDataSig(strRecvData);
        emit tab3RecvDataSig(strRecvData);

    }

}

void tab1Socket::on_pPBDataClear_clicked()
{
    ui->pTErecvData->clear();
}


void tab1Socket::socketSendToLinux(int keyNo)
{
    pSocketClient->socketWriteDataSlot("[SEOL_LIN]KEY@"+QString::number(keyNo));
}

void tab1Socket::on_pPBSend_clicked()
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


void tab1Socket::on_pLErecvId_selectionChanged()
{
    QLineEdit *pQLineEdit = (QLineEdit *)sender();
    pKeyBoard->setLineEdit(pQLineEdit);
    pKeyBoard->show();
}


void tab1Socket::on_pLEsendData_selectionChanged()
{
    QLineEdit *pQLineEdit = (QLineEdit *)sender();
    pKeyBoard->setLineEdit(pQLineEdit);
    pKeyBoard->show();
}

