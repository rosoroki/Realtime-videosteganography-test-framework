#ifndef QRPROCESSOR_H_
#define QRPROCESSOR_H_

#include <opencv2/highgui/highgui.hpp>
#include "frameprocessor.h"
#include <qrencode.h>
#include <opencv2/core/core.hpp>

using namespace cv;

class QRprocessor : public FrameProcessor {    
    std::string message; // сообщение подлежащее зашифровыванию
    QRcode *qr;  // qr код секретного сообщения
    int height,width; //параметры кадра
    int start_position; //абсцисса левого нижнего угла QR кода
    int sqr_length; //размер квадратика QR кода в пикселях
    int color; //цвет изменяемого канала (0-R,1-G,2-B)
    int intensity; //интенсивность изменения цвета канала
public:
    QRprocessor(std::string str, std::string color, std::string intensity);
    virtual void process(Mat &input, Mat &output);            
};
#endif /* QRPROCESSOR_H_ */
