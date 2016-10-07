#ifndef VIDEOPROCESSING_H
#define VIDEOPROCESSING_H

#include <QMutex>
#include <QThread>
#include <QImage>
#include <QWaitCondition>

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
using namespace cv;
class VideoProcessing : public QThread
{
    Q_OBJECT
private:
    bool stop;
    QMutex mutex;
    QWaitCondition condition;
    Mat frame;
    int frameRate;
    VideoCapture capture;
    Mat RGBframe;
    QImage img;

    int* quantization;
    int* threshold;

signals:
    void processedImage(const QImage &image);
protected:
    void run();
    void msleep(int ms);
public:

   //Constructor
   VideoProcessing(QObject *parent = 0);
   //Destructor
   ~VideoProcessing();
   //Load a video from memory
   bool loadVideo(int* q, int* t);
   //Play the video
   void Play();
   //Stop the video
   void Stop();
   //check if the player has been stopped
   bool isStopped() const;
};

#endif // VIDEOPROCESSING_H
