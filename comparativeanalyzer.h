#ifndef COMPARATIVEANALYZER_H
#define COMPARATIVEANALYZER_H

#include "opencv2/core/core.hpp"
#include "frameanalyzer.h"

using namespace cv;

class ComparativeAnalyzer : public FrameAnalyzer
{
public:
    int color; //цвет изменяемого канала (0-R,1-G,2-B)
    int intensity; //интенсивность изменения цвета канала
    int channel1, channel2;
    ComparativeAnalyzer(std::string color, std::string intensity);
    ComparativeAnalyzer();
    virtual void analyze(Mat &input, Mat &output); //метод анализа
};

#endif // COMPARATIVEANALYZER_H
