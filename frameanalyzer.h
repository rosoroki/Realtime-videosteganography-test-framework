#ifndef FRAMEANALYZER_H
#define FRAMEANALYZER_H

#include <cv.h>
#include <QList>

using namespace cv;

class FrameAnalyzer
{
public:
    FrameAnalyzer();  //конструктор
    virtual ~FrameAnalyzer(); //деструктор

    virtual void analyze(Mat &input)=0; //метод анализа
    virtual Mat& getMat(int index); //метод получения кадра с номером index

    Mat currentFrame; //текущий кадр
    Mat lastFrame; //предпоследний добавленный кадр

    QList<Mat> frameList; //список кадров
    virtual void saveList()=0;  //метод сохранения списка
};

#endif // FRAMEANALYZER_H
