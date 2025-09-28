#include "tab6webcamera.h"
#include "ui_tab6webcamera.h"

Tab6WebCamera::Tab6WebCamera(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Tab6WebCamera)
{
    ui->setupUi(this);
    webcamUrl = QUrl("http://192.168.0.52:8080/?action=stream");
    webcamUrl.setUserName("user");
    webcamUrl.setPassword("1234");
    pQProcess = new QProcess(this);
    pQWebEngineView = new QWebEngineView(this);

    QPixmap pixMap(":/Images/Images/display.jpg");
    QGraphicsScene* scene = new QGraphicsScene(ui->pGPView);
    scene->addPixmap(pixMap);
    ui->pGPView->setScene(scene);

    connect(ui->pPBCamStart,SIGNAL(clicked(bool)),this, SLOT(camStartSlot(bool)));
}

Tab6WebCamera::~Tab6WebCamera()
{
    delete ui;
}

void Tab6WebCamera::camStartSlot(bool bCheck)
{
    QString webcamProgrm = "/home/ubuntu/mjpg-streamer-master/mjpg_streamer";
    QStringList webcamArg = {"-i", "/home/ubuntu/mjpg-streamer-master/input_uvc.so","-o","/home/ubuntu/mjpg-streamer-master/output_http.so -w /home/ubuntu/mjpg-streamer-master/www -c user:1234"};

    if(bCheck)
    {
        pQProcess->start(webcamProgrm,webcamArg);
        if(pQProcess->waitForStarted())
        {
            QThread::msleep(200);
            pQWebEngineView->load(webcamUrl);
//            ui->pGPView->setLayout(pQWebEngineView->layout());
            ui->pPBCamStart->setText("CamStop");

            // pQWebEngineView를 pGPView의 자식으로 추가 및 보여주기
            pQWebEngineView->setParent(ui->pGPView);
            pQWebEngineView->setGeometry(ui->pGPView->rect());
            pQWebEngineView->show();
            // 만약 기존 씬이 있다면 제거
            if (ui->pGPView->scene())
            {
                ui->pGPView->setScene(nullptr);
            }
        }
    }
    else
    {
        pQProcess->kill();
        pQWebEngineView->stop();
        pQWebEngineView->hide();
        ui->pPBCamStart->setText("CamStart");

        // 기존 씬 제거 (메모리 관리 고려)
        QGraphicsScene* oldScene = ui->pGPView->scene();
        if (oldScene)
        {
            ui->pGPView->setScene(nullptr);
            delete oldScene;
        }
        // 새 씬 생성 및 이미지 추가
        QPixmap pixMap(":/Images/Images/display.jpg");
        QGraphicsScene* scene = new QGraphicsScene(ui->pGPView);
        scene->addPixmap(pixMap);
        ui->pGPView->setScene(scene);
    }
}

