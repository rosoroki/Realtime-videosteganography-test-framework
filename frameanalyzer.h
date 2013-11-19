#ifndef FRAMEANALYZER_H
#define FRAMEANALYZER_H

#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <QList>

using namespace cv;

class FrameAnalyzer
{
public:
    FrameAnalyzer();  //конструктор
    virtual ~FrameAnalyzer(); //деструктор

    virtual void analyze(Mat &input, Mat &output)=0; //метод анализа
    virtual Mat& getMat(int index); //метод получения кадра с номером index

    Mat currentFrame; //текущий кадр
    Mat lastFrame; //предпоследний добавленный кадр

    QList<Mat> frameList; //список кадров    
};

#endif // FRAMEANALYZER_H
