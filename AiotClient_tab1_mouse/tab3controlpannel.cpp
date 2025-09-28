#include "tab3controlpannel.h"
#include "ui_tab3controlpannel.h"

Tab3ControlPannel::Tab3ControlPannel(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Tab3ControlPannel)
{
    ui->setupUi(this);
    paletteOn.setColor(ui->pPBlamp->backgroundRole(), QColor(255,0,0));
    paletteOff.setColor(ui->pPBlamp->backgroundRole(), QColor(0,255,0));
    ui->pPBlamp->setPalette(paletteOff);
    ui->pPBplug->setPalette(paletteOff);
}

Tab3ControlPannel::~Tab3ControlPannel()
{
    delete ui;
}

void Tab3ControlPannel::on_pPBlamp_clicked(bool checked)
{
    if(checked)
    {
        emit socketSendDataSig("[SEOL_LIN]LAMPON");
        ui->pPBlamp->setChecked(false);
    }
    else
    {
        emit socketSendDataSig("[SEOL_LIN]LAMPOFF");
        ui->pPBlamp->setChecked(true);
    }
}

void Tab3ControlPannel::on_pPBplug_clicked(bool checked)
{
    if(checked)
    {
        emit socketSendDataSig("[SEOL_LIN]PLUGON");
        ui->pPBplug->setChecked(false);
    }
    else
    {
        emit socketSendDataSig("[SEOL_LIN]PLUGOFF");
        ui->pPBplug->setChecked(true);
    }
}

void Tab3ControlPannel::tab3RecvDataSlot(QString recvData)
{
    qDebug() << recvData;
    QStringList strList = recvData.split("@");
    if(strList[2] == "LAMPON")
    {
        ui->pPBlamp->setChecked(true);
        ui->pPBlamp->setPalette(paletteOn);
    }
    else if(strList[2] == "LAMPOFF")
    {
        ui->pPBlamp->setChecked(false);
        ui->pPBlamp->setPalette(paletteOff);
    }
    if(strList[2] == "PLUGON")
    {
        ui->pPBplug->setChecked(true);
        ui->pPBplug->setPalette(paletteOn);
    }
    else if(strList[2] == "PLUGOFF")
    {
        ui->pPBplug->setChecked(false);
        ui->pPBplug->setPalette(paletteOff);
    }
}

