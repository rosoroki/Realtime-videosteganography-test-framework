#include <opencv/cv.h>
#include "QRprocessor.h"
#include <qrencode.h>

using namespace cv;

//конструктор класса; установка вывода по умолчанию; принимаемая строка - секретное сообщение---------
QRprocessor::QRprocessor(std::string str, std::string color, std::string intensity) {
    message=str;
    if (color=="B") {
        this->color=0; //blue
    } else {
        if (color=="G") {
            this->color=1; //green
        } else {
            this->color=2; //red
        }
    }
    this->intensity=atoi(intensity.c_str());

    std::cout << this->color << std::endl;
    std::cout << this->intensity << std::endl;

    std::cout << message << std::endl;
    qr = QRcode_encodeString(message.c_str(), 0, QR_ECLEVEL_H, QR_MODE_8, 1);
    width=640;
    height=480;
    sqr_length = height/qr->width;
    start_position = (width-height)/2;
}
//-----------------------------------------------------------------------------------------------------


//метод добавления QR кода к кадру---------------------------------------------------------------------
void QRprocessor::process(cv::Mat &input, cv::Mat &output) {

    int y_qr, x_qr;
    int offset_x, offset_y;

    for (y_qr = 0; y_qr < qr->width; y_qr++) {
       for (x_qr = 0; x_qr < qr->width; x_qr++) {

          if (qr->data[(y_qr * qr->width) + x_qr] & 0x1)
          {
              for(offset_x=((x_qr*sqr_length)+start_position);
                  offset_x<=(x_qr*sqr_length)+start_position+sqr_length;
                  offset_x++)
              {
                  for(offset_y=(y_qr*sqr_length);
                      offset_y<=(y_qr*sqr_length)+sqr_length;
                      offset_y++)
                  {
                      output.at<Vec3b>(offset_y,offset_x)[color]=input.at<Vec3b>(offset_y,offset_x)[color]+intensity;

                  }
              }
          }
       }
    }
}
//-----------------------------------------------------------------------------------------------------
