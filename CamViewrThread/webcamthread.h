#ifndef WEBCAMTHREAD_H
#define WEBCAMTHREAD_H

#include <QThread>
#include <QLabel>
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;
class WebCamThread : public QThread
{
    //private: 생략
    Q_OBJECT
    void run();     // thread는 run()
    int cnt;

    String fname;
    Mat frame;

    void put_string(Mat &frame, string text, Point pt, int value);



public:
    WebCamThread(QObject *parent = nullptr);
    bool camViewFlag;       // private 정의가 맞음
    QLabel *pCamView;       // private 정의가 맞음
    void snapShot();
};

#endif // WEBCAMTHREAD_H
