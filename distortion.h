#ifndef DISTORTION_H
#define DISTORTION_H

#include <opencv/cv.h>
#include "losses.h"

class Distortion : public Losses
{
public:
    Distortion(std::string str);
    virtual void process(cv::Mat &input, cv::Mat &output)=0; //метод покадрового искажения
    void resize();
    ~Distortion();
};

#endif // DISTORTION_H
