#include "distortion.h"

Distortion::Distortion(std::string str):Losses(str)
{
}

void Distortion::resize()
{
   cv::resize(*currentFrame, *modifiedFrame, cv::Size(120,500), 0, 0, INTER_CUBIC);
}

Distortion::~Distortion()
{
}
