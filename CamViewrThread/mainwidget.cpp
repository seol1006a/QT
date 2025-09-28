#include "mainwidget.h"
#include "ui_mainwidget.h"

MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainWidget)
{
    ui->setupUi(this);
    setWindowTitle("CamViewer");
    ui->pPBsnapShot->setEnabled(false);
    pWebCamThread = new WebCamThread(this);
    pWebCamThread->pCamView = ui->plabelCamView;
}

MainWidget::~MainWidget()
{
    delete ui;
}


void MainWidget::on_pPBcamStart_clicked(bool checked)
{
    if(checked)
    {
        pWebCamThread->camViewFlag = true;
        if(!pWebCamThread->isRunning())
        {
            pWebCamThread->start();
            ui->pPBcamStart->setText("CamStop");
            ui->pPBsnapShot->setEnabled(true);
        }
    }
    else
    {
        pWebCamThread->camViewFlag = false;
        ui->pPBcamStart->setText("CamStart");
        ui->pPBsnapShot->setEnabled(false);
    }
}


void MainWidget::on_pPBsnapShot_clicked()
{
    pWebCamThread->snapShot();
}

