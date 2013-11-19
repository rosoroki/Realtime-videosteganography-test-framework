#include "basicdistortion.h"
#include <opencv2/core/core.hpp>

using namespace cv;

BasicDistortion::BasicDistortion(std::string str):Distortion(str)
{
}

//пример применения искажения
void BasicDistortion::process(Mat &input, Mat &output)
{
    currentFrame = &input;
    modifiedFrame = &output;
    resize();
}
