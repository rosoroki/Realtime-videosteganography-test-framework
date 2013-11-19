#include "qualityreduction.h"
#include <opencv2/core/core.hpp>

using namespace cv;

QualityReduction::QualityReduction(std::string str):Losses(str)
{
}

void QualityReduction::medianBlur()
{
    //медианный фильтр
    cv::medianBlur(*currentFrame, *modifiedFrame, 7);
}

void QualityReduction::boxFilter()
{
    //боксфильтр
    cv::boxFilter(*currentFrame,*modifiedFrame, -1, Size(7,7), Point(-1,-1), true, BORDER_DEFAULT);
}

void QualityReduction::GaussianBlur()
{
    //Гауссово размытие
    cv::GaussianBlur(*currentFrame,*modifiedFrame,Size(7,5),5,7,2);
}

QualityReduction::~QualityReduction(){
}
