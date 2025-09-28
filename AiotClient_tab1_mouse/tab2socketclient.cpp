#include "tab2socketclient.h"
#include "ui_tab2socketclient.h"

Tab2SocketClient::Tab2SocketClient(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Tab2SocketClient)
{
    ui->setupUi(this);
    pKeyBoard = new Keyboard();
    ui->pPBSend->setEnabled(false); //초기설정 송신버튼 비활성화
    pSocketClient = new SocketClient(this);
    connect(pSocketClient, SIGNAL(socketRecvDataSig(QString)), this, SLOT(updateRecvDataSlot(QString)));

    on_pPBserverConnect_toggled(true); //소켓 자동 연결
}

Tab2SocketClient::~Tab2SocketClient()
{
    delete ui;
}

void Tab2SocketClient::on_pPBserverConnect_toggled(bool checked)
{
    bool bFlag;
    // qDebug() << "on_pPBserverConnect_toggled()";
    if(checked)
    {
        pSocketClient->connectToServerSlot(bFlag);
        if(bFlag)
        {
            ui->pPBserverConnect->setText("서버 해제");
            ui->pPBSend->setEnabled(true); //송신버튼 활성화
        }
    }
    else {
        pSocketClient->socketClosedServerSlot();
        ui->pPBserverConnect->setText("서버 연결");
        ui->pPBSend->setEnabled(false); //송신버튼 비활성화
    }
}

void Tab2SocketClient::updateRecvDataSlot(QString strRecvData)
{
    strRecvData.chop(1); //끝문자 한개 "\n" 제거
    QTime time = QTime::currentTime(); // 현재 시간 가져오기
    QString strTime = time.toString(); //문자열로 변환(시간을)
    strTime = strTime + " " + strRecvData;
    ui->pTErecvData->append(strTime);

    //[SEOL_QT]LED@0xff ==> @SEOL_QT@LED@0xff 로 치환
    strRecvData.replace("[","@"); //문자 치환
    strRecvData.replace("]","@"); //문자 치환
    QStringList strList = strRecvData.split("@");  //@로
    if(strList[2].indexOf("LED") == 0)
    {
        bool bFlag;
        int ledNo = strList[3].toInt(&bFlag,16); //16진수 값을 int형으로 변환
        if(bFlag)
            emit ledWriteSig(ledNo);
    }
    else if(strList[2].indexOf("LAMP") == 0)//Tab3의 LAMP 제어
    {
        emit tab3RecvDataSig(strRecvData);
    }
    else if(strList[2].indexOf("PLUG") == 0)
    {
        emit tab3RecvDataSig(strRecvData);
    }
    else if(strList[2].indexOf("SENSOR") ==0)
    {
        emit tab4RecvDataSig(strRecvData);
    }
}

void Tab2SocketClient::on_pPBrecvDataClear_clicked()
{
    ui->pTErecvData->clear();
}


void Tab2SocketClient::on_pPBSend_clicked() //send 버튼 누르면 실행
{
    QString strRecvId = ui->pLErecvId->text(); //문자열 가져오기
    QString strSendData = ui->pLEsendData->text();
    if(strRecvId.isEmpty()) //만약 비어있다면
    {
        strSendData = "[ALLMSG]" + strSendData; //모든 수신자에게 보내기
    }
    else
    {
        strSendData = "["+strRecvId+"]" + strSendData;
    }
    pSocketClient->socketWriteDataSlot(strSendData);
    ui->pLEsendData->clear(); //송신데이터를 보냈다면 clear
}

void Tab2SocketClient::socketSendToLinux(int keyNo) //키값을 lin에게 전달
{
    pSocketClient->socketWriteDataSlot("[SEOL_LIN]KEY@"+QString::number(keyNo));
}

SocketClient* Tab2SocketClient::getpSocketClient()
{
    return pSocketClient;
}



void Tab2SocketClient::on_pLErecvId_selectionChanged()
{
    QLineEdit *pQLineEdit = (QLineEdit *)sender();
    pKeyBoard->setLineEdit(pQLineEdit);
    pKeyBoard->show();
}


void Tab2SocketClient::on_pLEsendData_selectionChanged()
{
    QLineEdit *pQLineEdit = (QLineEdit *)sender();
    pKeyBoard->setLineEdit(pQLineEdit);
    pKeyBoard->show();
}

