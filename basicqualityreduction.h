#ifndef BASICQUALITYREDUCTION_H
#define BASICQUALITYREDUCTION_H

#include "qualityreduction.h"

class BasicQualityReduction : public QualityReduction
{
public:
    BasicQualityReduction(std::string str);
    virtual void process(cv::Mat &input, cv::Mat &output); //метод покадрового искажения    
};

#endif // BASICQUALITYREDUCTION_H
