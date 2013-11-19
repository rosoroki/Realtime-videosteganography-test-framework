#ifndef BASICDISTORTION_H
#define BASICDISTORTION_H

#include "distortion.h"

class BasicDistortion : public Distortion
{
public:
    BasicDistortion(std::string str);
    virtual void process(cv::Mat &input, cv::Mat &output); //метод покадрового искажения
};

#endif // BASICDISTORTION_H
