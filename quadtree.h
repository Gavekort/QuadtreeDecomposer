/*
 * Pseudo-Quadtree implementation
 */

#ifndef QUADTREE_H
#define QUADTREE_H

#include <vector>
#include <iostream>
#include "cvtools.h"

struct AABB
{
    short x, y; //Centerpoint of segment
    short width, height;

    AABB(){}
    AABB(short x, short y, short width, short height) : x(x), y(y), width(width), height(height) {}
};

class Quadtree
{
    private:
        Quadtree(cv::Mat* frame, cv::Mat* canvas, int* quantization, AABB boundary, int level);

        std::unique_ptr<Quadtree> nw;
        std::unique_ptr<Quadtree> ne;
        std::unique_ptr<Quadtree> sw;
        std::unique_ptr<Quadtree> se;

        AABB boundary;

        cv::Vec3b avgColor;

        cv::Mat* frame; //pointer to unmodified frame
        cv::Mat* canvas; //frame that will be modified

        int level = 1;
        int* quantization;
    public:
        Quadtree() = delete;
        Quadtree(cv::Mat* frame, cv::Mat* canvas, int* quantization);

        cv::Mat* output();
        void process();
        void subdivide();
        void debug();
        void paint(cv::Vec3b color, AABB segment);
        cv::Vec3b segmentAverage(AABB segment);
};

Quadtree::Quadtree(cv::Mat* frame, cv::Mat* canvas, int* quantization) : frame(frame), canvas(canvas), quantization(quantization)
{
    nw = NULL;
    ne = NULL;
    sw = NULL;
    se = NULL;
    this->boundary = AABB(frame->rows/2, frame->cols/2, frame->rows, frame->cols);
    //std::cout << "QuadTree created with: " << boundary.x << " " << boundary.y << " " << boundary.width << " " << boundary.height << std::endl;
    process();
}

Quadtree::Quadtree(cv::Mat* frame, cv::Mat* canvas, int* quantization, AABB boundary, int level) : frame(frame), canvas(canvas), quantization(quantization)
{
    nw = NULL;
    ne = NULL;
    sw = NULL;
    se = NULL;
    this->level = level;
    this->boundary = boundary;
    //std::cout << "QuadTree created with: " << boundary.x << " " << boundary.y << " " << boundary.width << " " << boundary.height << std::endl;
    process();
}


void Quadtree::debug(){
   // subdivide();
}

void Quadtree::process(){
    avgColor = segmentAverage(boundary);
    paint(avgColor, boundary);
    if(level <= *quantization){
        //std::cout << "Level: " << level << " " << boundary.x << " " << boundary.y << std::endl;
        subdivide();
    }
}

void Quadtree::subdivide()
{
    //std::cout << "Subdividing to level: " << level + 1 << std::endl;
    int quantized = frame->rows/boundary.width; // Calculate how far we have split the image
    int offsetx = frame->rows/(4*quantized);
    int offsety = frame->cols/(4*quantized);

    std::unique_ptr<Quadtree> nw(new Quadtree(frame, canvas, quantization,
                                              AABB(boundary.x - offsetx, boundary.y - offsety, boundary.width/2, boundary.height/2),
                                              level + 1));
    std::unique_ptr<Quadtree> ne(new Quadtree(frame, canvas, quantization,
                                              AABB(boundary.x + offsetx, boundary.y - offsety, boundary.width/2, boundary.height/2),
                                              level + 1));
    std::unique_ptr<Quadtree> sw(new Quadtree(frame, canvas, quantization,
                                              AABB(boundary.x - offsetx, boundary.y + offsety, boundary.width/2, boundary.height/2),
                                              level + 1));
    std::unique_ptr<Quadtree> se(new Quadtree(frame, canvas, quantization,
                                              AABB(boundary.x + offsetx, boundary.y + offsety, boundary.width/2, boundary.height/2),
                                              level + 1));
}

void Quadtree::paint(cv::Vec3b color, AABB segment){
    //std::cout << "Painting from: " << segment.y - segment.height/2 << ":" << segment.x - segment.width/2
    //          << " to " << segment.x + segment.width/2 << ":" << segment.y + segment.height/2 << std::endl;
    for (int y = segment.y - segment.height/2; y < segment.y + segment.height/2; ++y) {
            for (int x = segment.x - segment.width/2; x < segment.x + segment.width/2; ++x) {
                    canvas->at<Vec3b>(x, y) = color;
            }
    }
}

cv::Vec3b Quadtree::segmentAverage(AABB segment){
    int count = 0;
    cv::Vec3i avg;
    //std::cout << "Analyzing from: " << segment.y - segment.height/2 << ":" << segment.x - segment.width/2
    //          << " to " << segment.x + segment.width/2 << ":" << segment.y + segment.height/2 << std::endl;
    for (int y = segment.y - segment.height/2; y < segment.y + segment.height/2; y += 2) {
            for (int x = segment.x - segment.width/2; x < segment.x + segment.width/2; x += 2) {
                    avg += frame->at<Vec3b>(x, y);
                    count++;
            }
    }
    return avg/count; //Is automatically casted to cv::Vec3b by specification
}

#endif // QUADTREE_H
