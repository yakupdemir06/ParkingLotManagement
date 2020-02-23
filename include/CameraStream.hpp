#ifndef CAMERAVEHICLEIN_HPP
#define CAMERAVEHICLEIN_HPP

#include <QThread>
#include <QImage>
#include <QPixmap>

#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>


class ThreadManager;

class CameraStream : public QThread
{
    Q_OBJECT

public:
    CameraStream(ThreadManager* app, unsigned int cameraIndex);

    int getFPS() const;
    void setFPS(int value);
    void run() override;

public slots:
    void stopCameraStream();
    void startThread();

signals:
    void updateCameraDisplay(QPixmap);
    void captureLicensePlate(cv::Mat);
    void updateCamStatusText(QString,QString);

private:
    ThreadManager* m_tmanager;
    cv::VideoCapture m_vidcap;

    unsigned int m_camIndex;
    unsigned int m_MaxFPS = 50;
    bool m_keepStreaming = true;

    cv::Mat frame;
    QImage qt_image;

};

#endif // CAMERAVEHICLEIN_HPP