#include "blindanalyzer.h"

BlindAnalyzer::BlindAnalyzer(std::string color, std::string intensity)
{
    if (color=="B") {
        this->color=0; //blue
        channel1=1;
        channel2=2;
    } else {
        if (color=="G") {
            this->color=1; //green
            channel1=0;
            channel2=2;
        } else {
            this->color=2; //red
            channel1=0;
            channel2=1;
        }
    }
    this->intensity=atoi(intensity.c_str());
}


BlindAnalyzer::BlindAnalyzer()
{
    this->color=2; //red
    channel1=0;
    channel2=1;
    this->intensity=10;
}


void BlindAnalyzer::analyze(Mat &input, Mat &output)
{
    for (int y=0; y < 480; y++) {
       for (int x = 0; x < 640; x++) {
           output.at<Vec3b>(y,x)[color]+=intensity;
           output.at<Vec3b>(y,x)[channel1]=0;
           output.at<Vec3b>(y,x)[channel2]=0;
       }
    }
}
