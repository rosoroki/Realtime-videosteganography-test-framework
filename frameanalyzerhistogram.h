#ifndef FRAMEANALYZERHISTOGRAM_H
#define FRAMEANALYZERHISTOGRAM_H

#include "frameanalyzer.h"

class FrameAnalyzerHistogram : public FrameAnalyzer
{
protected:
    virtual void histogram();
    virtual void printHistograms(Mat &input, Mat &output);
    virtual void alphaCompose(cv::Mat &rgba1, cv::Mat &rgba2, cv::Mat &rgba_dest);
public:
    FrameAnalyzerHistogram();    
    virtual void analyze(Mat &input, Mat &output);    
};

#endif // FRAMEANALYZERHISTOGRAM_H
