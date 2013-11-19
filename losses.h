#ifndef LOSSES_H
#define LOSSES_H

#include <opencv/cv.h>
#include <QList>

using namespace cv;

class Losses
{
protected:    
    Mat *currentFrame; //текущий кадр
    Mat *modifiedFrame; //модифицированный кадр
    //Mat *lastFrame; //предпоследний добавленный кадр
    //QList<Mat> frameList; //список кадров
    std::string prms;
public:
    Losses(std::string str);
    virtual void process(cv::Mat &input, cv::Mat &output)=0;
    virtual ~Losses();
};

#endif // LOSSES_H
