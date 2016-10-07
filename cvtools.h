#pragma once
#ifndef CVTOOLS_H
#define CVTOOLS_H
#include <QWidget>
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv/cv.h"


class CvTools
{
public:
    CvTools();
    QImage ConvertMatToQimage(const cv::Mat3b& input);
};

#endif // CVTOOLS_H
