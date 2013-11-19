#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>

#include "comparativeanalyzer.h"

ComparativeAnalyzer::ComparativeAnalyzer(std::string color, std::string intensity)
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


ComparativeAnalyzer::ComparativeAnalyzer()
{
    this->color=2; //red
    channel1=0;
    channel2=1;
    this->intensity=10;
}


void ComparativeAnalyzer::analyze(Mat &input, Mat &output)
{    
    for (int y=0; y < 480; y++) {
       for (int x = 0; x < 640; x++) {          
           output.at<Vec3b>(y,x)[color]-=input.at<Vec3b>(y,x)[color];
           output.at<Vec3b>(y,x)[channel1]=0;
           output.at<Vec3b>(y,x)[channel2]=0;

           if (output.at<Vec3b>(y,x)[color]>220)
           {
                output.at<Vec3b>(y,x)[color]=255;
                output.at<Vec3b>(y,x)[channel1]=255;
                output.at<Vec3b>(y,x)[channel2]=255;
            } else
            {
                 output.at<Vec3b>(y,x)[color]=0;
                 output.at<Vec3b>(y,x)[channel1]=0;
                 output.at<Vec3b>(y,x)[channel2]=0;
             }
       }
    }
}
