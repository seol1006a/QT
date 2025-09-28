#ifndef WEBCAMTHREAD_H
#define WEBCAMTHREAD_H

#include <QThread>
#include <QLabel>
#include <opencv2/opencv.hpp>
#include <QTimer>
using namespace cv;
using namespace std;
class WebCamThread : public QThread
{
    Q_OBJECT
    void run();
    int cnt;
    string fname;
    QString strColor, strColorPre;
    Mat frame, frameQt;
    QImage qImage;
    QTimer *pQTimer;
    bool rgbClassifyFlag;
    void put_string(Mat &frame, string text, Point pt, int value = -1);

public:
    WebCamThread(QObject *parent = nullptr);
    bool camViewFlag;
    QLabel *pCamView;
    void snapShot();
    void rgbTimerStart();
    void rgbTimerStop();

private slots:
    void rgbClassifyslot();

signals:
    void socketSendDataSig(QString);
};

#endif // WEBCAMTHREAD_H
