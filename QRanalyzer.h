#ifndef QRANALYZER_H
#define QRANALYZER_H

#include "frameanalyzer.h"
#include "cv.h"
#include <highgui.h>

class QRanalyzer : public FrameAnalyzer
{
    std::string message; // расшифрованное сообщение
    int height,width; //параметры кадра
    int start_position; //абсцисса левого нижнего угла QR кода
    //int sqr_length; //размер квадратика QR кода в пикселях
    int color; //цвет изменяемого канала (0-R,1-G,2-B)
    int intensity; //интенсивность изменения цвета канала
public:
    QRanalyzer();
    void analyze(Mat &input);

};

#endif // QRANALYZER_H
