#ifndef FRAMEANALYZERHISTOGRAM_H
#define FRAMEANALYZERHISTOGRAM_H

#include "frameanalyzer.h"

class FrameAnalyzerHistogram : public FrameAnalyzer
{
public:
    FrameAnalyzerHistogram();    
    virtual void analyze(Mat &input);
    virtual void histogram();
    virtual void saveList();
};

#endif // FRAMEANALYZERHISTOGRAM_H
