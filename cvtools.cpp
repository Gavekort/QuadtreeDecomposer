#include "cvtools.h"

CvTools::CvTools()
{

}

/*
 * Convert OpenCV Matrix to QImage
 */
QImage CvTools::ConvertMatToQimage(const cv::Mat3b& input){
    QImage output(input.cols, input.rows, QImage::Format_ARGB32);
    for (int y = 0; y < input.rows; ++y) {
            const cv::Vec3b *inputrow = input[y];
            QRgb *outputrow = (QRgb*)output.scanLine(y);
            for (int x = 0; x < input.cols; ++x) {
                    outputrow[x] = qRgba(inputrow[x][2], inputrow[x][1],
                            inputrow[x][0], 255);
            }
    }
    return output;
}
