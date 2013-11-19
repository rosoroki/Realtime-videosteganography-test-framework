#ifndef BLINDANALYZER_H
#define BLINDANALYZER_H

#include "opencv2/core/core.hpp"
#include "frameanalyzer.h"

using namespace cv;

class BlindAnalyzer : public FrameAnalyzer
{
public:
    int color; //цвет изменяемого канала (0-R,1-G,2-B)
    int intensity; //интенсивность изменения цвета канала
    int channel1, channel2;
    BlindAnalyzer(std::string color, std::string intensity);
    BlindAnalyzer();
    virtual void analyze(Mat &input, Mat &output); //метод анализа    
};

#endif // BLINDANALYZER_H
