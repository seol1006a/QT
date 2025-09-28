#include "mainwidget.h"
#include "ui_mainwidget.h"

MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainWidget)
{
    ui->setupUi(this);
    pQWebEngineView1 = new QWebEngineView(this);
//    pQWebEngineView->load(QUrl("http://www.naver.com"));
    pQWebEngineView1->load(QUrl("http://192.168.0.4:8080/?action=stream"));
    ui->pVLCam1->addWidget(pQWebEngineView1);

    pQWebEngineView2 = new QWebEngineView(this);
    pQWebEngineView2->load(QUrl("http://192.168.0.73:8080/?action=stream"));
    ui->pVLCam2->addWidget(pQWebEngineView2);

    pQWebEngineView3 = new QWebEngineView(this);
    pQWebEngineView3->load(QUrl("http://192.168.0.94:8080/?action=stream"));
    ui->pVLCam3->addWidget(pQWebEngineView3);

    pQWebEngineView4 = new QWebEngineView(this);
    pQWebEngineView4->load(QUrl("http://192.168.0.82:8080/?action=stream"));
    ui->pVLCam4->addWidget(pQWebEngineView4);


}

MainWidget::~MainWidget()
{
    delete ui;
}
