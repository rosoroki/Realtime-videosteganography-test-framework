#ifndef QUALITYREDUCTION_H
#define QUALITYREDUCTION_H

#include "losses.h"

using namespace cv;

class QualityReduction : public Losses
{
public:
    QualityReduction(std::string str);
    virtual void process(cv::Mat &input, cv::Mat &output)=0; //метод покадрового снижения качества
    //фильтры
    void medianBlur(); //медианный фильтр
    void GaussianBlur(); //гауссовый фильтр
    void boxFilter(); //размытие изображения
    ~QualityReduction();
};

#endif // QUALITYREDUCTION_H
