#ifndef FRAMEPROCESSOR_H_
#define FRAMEPROCESSOR_H_

#include <opencv/cv.h>

class FrameProcessor {
public:
    FrameProcessor(); //конструктор
    virtual void process(cv::Mat &input, cv::Mat &output)=0; //метод покадровой обработки
    virtual ~FrameProcessor(); //деструктор
};

#endif /* FRAMEPROCESSOR_H_ */
