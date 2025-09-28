#include "tab7camopencv.h"
#include "ui_tab7camopencv.h"

Tab7CamOpencv::Tab7CamOpencv(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Tab7CamOpencv)
{
    ui->setupUi(this);
    setWindowTitle("CamViewer");
    ui->pPBsnapShot->setEnabled(false);
    ui->pCBrgb->setEnabled(false);
    pWebCamThread = new WebCamThread(this);
    pWebCamThread->pCamView = ui->plabelCamView;
}

Tab7CamOpencv::~Tab7CamOpencv()
{
    delete ui;
}

void Tab7CamOpencv::on_pPBsnapShot_clicked()
{
    pWebCamThread->snapShot();
}

void Tab7CamOpencv::on_pPBcamStart_clicked(bool checked)
{

    if(checked)
    {
        pWebCamThread->camViewFlag = true;
        //       qDebug() << "on_pPBcamStart_clicked 1 ";
        if(!pWebCamThread->isRunning())
        {
            pWebCamThread->start();
            ui->pPBcamStart->setText("CamStop");
            ui->pPBsnapShot->setEnabled(true);
        }
    }
    else
    {
        //            qDebug() << "on_pPBcamStart_clicked 2";
        pWebCamThread->camViewFlag = false;
        ui->pPBcamStart->setText("CamStart");
        ui->pPBsnapShot->setEnabled(false);
    }
    ui->pCBrgb->setEnabled(true);
}


void Tab7CamOpencv::on_pCBrgb_clicked(bool checked)
{
    if(checked)
        pWebCamThread->rgbTimerStart();
    else
        pWebCamThread->rgbTimerStop();
}


WebCamThread* Tab7CamOpencv::getpWebCamThread()
{
    return pWebCamThread;
}
