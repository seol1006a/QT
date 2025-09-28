#include "webcamthread.h"

WebCamThread::WebCamThread(QObject *parent)
    : QThread(parent)
{
    cnt = 0;
    strColor="NONE";
    strColorPre = "NONE";
    camViewFlag = false;
    rgbClassifyFlag = false;
    pQTimer = new QTimer(this);
    connect(pQTimer, SIGNAL(timeout()), this, SLOT(rgbClassifyslot()));
}

void WebCamThread::run()
{
    VideoCapture  capture(0);
    int value = -1;
    if (!capture.isOpened())
    {
        cout << "카메라가 연결되지 않았습니다." << endl;
        exit(1);
    }
    while(camViewFlag) {

        capture.read(frame);

        // put_string(frame, "Count: ", Point(10, 40), cnt);
        fname = "cam_" + to_string(cnt++);
        fname += ".jpg";
        cvtColor(frame, frameQt, COLOR_BGR2RGB);
        int x = frameQt.cols/2;
        int y = frameQt.rows/2;
        if(rgbClassifyFlag)
        {
            Scalar meanHsv;
            Mat frameRoi, hsvImage;
            frameRoi = frame(Rect((x-32), (y-32), 64, 64));
            cvtColor(frameRoi, hsvImage, COLOR_BGR2HSV);
            meanHsv = mean(hsvImage);
            // qDebug() << " meanHSV H :" << meanHsv[0] << " meanHSV S :" << meanHsv[1] << " meanHSV V :" << meanHsv[2] ;  //색상

            if(170 <= meanHsv[0] || meanHsv[0] < 10) //Red
                strColor = "RED";
            else if(50 <= meanHsv[0] && meanHsv[0] < 70) //GREEN
                strColor ="GREEN";
            else if(110 <= meanHsv[0] && meanHsv[0] < 130) //BLUE
                strColor ="BLUE";
            else
                strColor = "NONE";
            rgbClassifyFlag = false;
            if(strColor != strColorPre)
            {
                emit socketSendDataSig("[KSH_LIN]COLOR@"+strColor);
                strColorPre = strColor;
            }
        }
        put_string(frameQt, strColor.toStdString(), Point(10, 40));
        qDebug() << strColor;
        line(frameQt,Point((x-32),y), Point((x+32), y), Scalar(255,0,0),2);
        line(frameQt,Point((x),y-32), Point((x), y+32), Scalar(255,0,0),2);
        rectangle(frameQt, Point((x-32),(y-32)), Point((x+32),(y+32)), Scalar(0,255,0),2);
        //        QImage qImage(frame.data, frame.cols, frame.rows, QImage::Format_BGR888);
        qImage = QImage(frameQt.data, frameQt.cols, frameQt.rows, QImage::Format_RGB888);
        pCamView->setPixmap(QPixmap::fromImage(qImage));
    }
    capture.release();
//    QPixmap pix("initDisplay.png");
//    QPixmap->setPixmap(pix)
    pCamView->setPixmap(QPixmap(":/Images/Images/display.jpg"));
}

// 문자열 출력 함수 - 그림자 효과
void WebCamThread::put_string(Mat &frame, string text, Point pt,  int value)
{
    Scalar colorScalar;
    if(value != -1)
        text += to_string(value);
    if(text == "RED")
        colorScalar ={255, 0, 0};
    else if(text == "GREEN")
        colorScalar ={0, 255, 0};
    else if(text == "BLUE")
        colorScalar ={0, 0, 255};
    else
        colorScalar = {128, 128, 128};
    Point shade = pt + Point(2, 2);
    int font = FONT_HERSHEY_SIMPLEX;
    putText(frame, text, shade, font, 0.7, Scalar(0, 0, 0), 2);     // 그림자 효과
    putText(frame, text, pt, font, 0.7, colorScalar, 2);// 작성 문자
}
void WebCamThread::snapShot()
{
//    imwrite(fname,frame);
    qImage.save(QString::fromStdString(fname),"JPG",80);
}

void WebCamThread::rgbTimerStart()
{
    if (!pQTimer->isActive()) {
        pQTimer->start(1000);
    }
}

void WebCamThread::rgbTimerStop()
{
    if (pQTimer->isActive())
    {
        pQTimer->stop();
    }
}

void WebCamThread::rgbClassifyslot()
{
    rgbClassifyFlag = true;
}


