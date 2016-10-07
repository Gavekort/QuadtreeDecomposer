#include "videoprocessing.h"
#include "quadtree.h"
#include <iostream>


VideoProcessing::VideoProcessing(QObject *parent) : QThread(parent)
{
    stop = true;
    std::cout << quantization << std::endl;
}

VideoProcessing::~VideoProcessing()
{
    mutex.lock();
    stop = true;
    capture.release();
    condition.wakeOne();
    mutex.unlock();
    wait();
}
void VideoProcessing::Stop()
{
    stop = true;
}
void VideoProcessing::msleep(int ms){
    struct timespec ts = { ms / 1000, (ms % 1000) * 1000 * 1000 };
    nanosleep(&ts, NULL);
}
bool VideoProcessing::isStopped() const{
    return this->stop;
}

bool VideoProcessing::loadVideo(int* q) {
    capture.open(0);
    if (capture.isOpened())
    {
        //frameRate = (int) capture.get(CV_CAP_PROP_FPS);
        frameRate = 0;
        quantization = q;

        return true;
    }
    else
        return false;
}
void VideoProcessing::Play()
{
    if (!isRunning()) {
        if (isStopped()){
            stop = false;
        }
        start(LowPriority);
    }
}

void VideoProcessing::run()
{
    std::cout << "RUN" << std::endl;
    int delay = (1000/30);
    while(!stop){
        //std::cout << *quantization << std::endl;
        if (!capture.read(frame))
        {
            stop = true;
        }
        cv::Mat canvas = frame.clone();
        std::unique_ptr<Quadtree> q(new Quadtree(&frame, &canvas, quantization));
        frame = canvas;
        if (frame.channels()== 3){
            cv::cvtColor(frame, RGBframe, CV_BGR2RGB);
            img = QImage((const unsigned char*)(RGBframe.data),
                              RGBframe.cols,RGBframe.rows,QImage::Format_RGB888);
        }
        else
        {
            img = QImage((const unsigned char*)(frame.data),
                                 frame.cols,frame.rows,QImage::Format_Indexed8);
        }
        //applyQuadTree(img);
        //q->debug();
        emit processedImage(img);
        this->msleep(delay);
    }
}

QImage quadTreeSegment(QImage input){ //Do I want to do a deep copy?
    return input;
}
