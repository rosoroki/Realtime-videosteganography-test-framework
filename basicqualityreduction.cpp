#include "basicqualityreduction.h"

BasicQualityReduction::BasicQualityReduction(std::string str):QualityReduction(str)
{
}

void BasicQualityReduction::process(cv::Mat &input, cv::Mat &output)
{    
    currentFrame = &input;
    modifiedFrame = &output;
    medianBlur();
}
