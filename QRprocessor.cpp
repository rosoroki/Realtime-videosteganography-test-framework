#include "QRprocessor.h"
#include "qrencode.h"

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

    //cv::VideoWriter output_cap("/home/srj/Documents/QRprocessor.avi",1,25,//input_cap.get(CV_CAP_PROP_FPS),
        //             cv::Size(width,height));
    output_cap = new VideoWriter("/home/srj/QRprocessor.avi",
                              //CV_FOURCC('P','I','M','1'),
                              //CV_FOURCC('I', 'Y', 'U', 'V'),
                              CV_FOURCC('M', 'J', 'P', 'G'),
                              15, cv::Size(640,480), true);
}
//-----------------------------------------------------------------------------------------------------


//метод добавления QR кода к кадру---------------------------------------------------------------------
void QRprocessor::process(cv::Mat &input, cv::Mat &output) {

    output = input;
    //идем сверху вниз по кадру слева направо
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
                      output.at<Vec3b>(offset_y,offset_x)[color]-=intensity;

                  }
              }
          }
       }
    }
}
//-----------------------------------------------------------------------------------------------------


// записать обработанный кадр--------------------------------------------------------------------------
void QRprocessor::write(cv::Mat &input) {
     output_cap->write(input);
}
//-----------------------------------------------------------------------------------------------------


QRprocessor::~QRprocessor() {
    delete output_cap;
}








/*




    for (int j = 0; j < qr->; j++) {
        for (int i = 0; i < width; i++) {
            //intensity = output.at<Vec3f>(j, i);
            //if (i<j)
            output.at<Vec3b>(j,i)[0]+=20;; //R
            //output.atec3b>(x,y)[1] += 20; //G
            //output.at<Vec3b>(x,y)[2] == 255; //B

            //std::cout << output.at<float>(j, i) << std::endl;
            //Soutput.at<float>(j, i) = input.at<float>(j, i) + 1.80615e-27;
            //intensity.val[0]++;
            //intensity.val[1]++;
            //intensity.val[2]++;
            //intensity.val[0]++;
            //intensity.val[1]++;
            //intensity.val[2]++;


        }
    }






    // Convert to gray
    //cv::cvtColor(input, output, CV_BGR2GRAY);
    //cv::resize(input, input, cv::Size(w, h), );

    //cv::resize(input, input, cv::Size(200,300), 1.5, 2.5, 1);
    //cv::cvtColor(input, input, 2);

    //cv::cvtColor(input, output, CV_BGR2HSV);
    //cv::Mat hsv, H;
    //int planes[] = { 0, 1 }, hsize[] = { 480, 640 };
    //cvtColor(input, hsv, CV_BGR2HSV);
    //calcHist(&hsv, 1, planes, cv::Mat(), H, 2, hsize, 0);

    //printHistograms(input, output);

    //alphaCompose(first, first, output);



    int i_qr, j_qr;
    for (i_qr = 0; i_qr < qr->width; i_qr++) {
       for (j_qr = 0; j_qr < qr->width; j_qr++) {
         if (qr->data[(i_qr * qr->width) + j_qr] & 0x1)
            printf("*");
         else
            printf(" ");
       }
           printf("\n");
    }





    output = input;



    //vector<Mat> bgr_planes;
    //split(input, bgr_planes);

    //Vec3f intensity;
    //uchar blue, green, red;

    //vector<Point2f> points;

    for (int j = 0; j < 480; j++) {
        for (int i = 0; i < 640; i++) {
            //intensity = output.at<Vec3f>(j, i);
            //if (i<j)
            output.at<Vec3b>(j,i)[0]+=20;; //R
            //output.atec3b>(x,y)[1] == 255; //G
            //output.at<Vec3b>(x,y)[2] == 255; //B

            //std::cout << output.at<float>(j, i) << std::endl;
            //Soutput.at<float>(j, i) = input.at<float>(j, i) + 1.80615e-27;
            //intensity.val[0]++;
            //intensity.val[1]++;
            //intensity.val[2]++;
            //intensity.val[0]++;
            //intensity.val[1]++;
            //intensity.val[2]++;


        }
    }

   //this->write(output);



    printHistograms(output, output);































    //cv::merge(bgr_planes,output);

    /*
     // Compute Canny edges
     cv::Canny(output, output, 100, 200);
     // Invert the image
     cv::threshold(output, output, 128, 255, cv::THRESH_BINARY_INV);
     */




//-----------------------------------------------------------------------------------------------------





void QRprocessor::alphaCompose(cv::Mat &rgba1, cv::Mat &rgba2,
        cv::Mat &rgba_dest) {
    Mat a1(rgba1.size(), rgba1.type()), ra1;
    Mat a2(rgba2.size(), rgba2.type());
    int mixch[] = { 3, 0, 3, 1, 3, 2, 3, 3 };
    mixChannels(&rgba1, 1, &a1, 1, mixch, 4);
    mixChannels(&rgba2, 1, &a2, 1, mixch, 4);
    subtract(Scalar::all(255), a1, ra1);
    bitwise_or(a1, Scalar(0, 0, 0, 255), a1);
    bitwise_or(a2, Scalar(0, 0, 0, 255), a2);
    multiply(a2, ra1, a2, 1. / 255);
    multiply(a1, rgba1, a1, 1. / 255);
    multiply(a2, rgba2, a2, 1. / 255);
    add(a1, a2, rgba_dest);
}

void QRprocessor::printHistograms(cv::Mat &input, cv::Mat &output) {

    //Mat src, dst;

    /// Separate the image in 3 places ( B, G and R )
    vector<Mat> bgr_planes;
    split(input, bgr_planes);

    // Установка количества бинов:
    int histSize = 256;

    // Установка граничных значений ( for B,G,R) )
    float range[] = { 0, 256 };
    const float* histRange = { range };

    bool uniform = true;
    bool accumulate = false;

    Mat b_hist, g_hist, r_hist;

    // Вычислить гистограммы:
    calcHist(&bgr_planes[0], 1, 0, Mat(), b_hist, 1, &histSize, &histRange,
            uniform, accumulate);
    calcHist(&bgr_planes[1], 1, 0, Mat(), g_hist, 1, &histSize, &histRange,
            uniform, accumulate);
    calcHist(&bgr_planes[2], 1, 0, Mat(), r_hist, 1, &histSize, &histRange,
            uniform, accumulate);

    // Отрисовать гистограммы для B, G и R
    int hist_w = 640;
    int hist_h = 480;
    int bin_w = cvRound((double) hist_w / histSize);

    Mat histImage(hist_h, hist_w, CV_8UC3, Scalar(0, 0, 0));

    // Normalize the result to [ 0, histImage.rows ]
    normalize(b_hist, b_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());
    normalize(g_hist, g_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());
    normalize(r_hist, r_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());

    // Отрисовать для каждого канала
    for (int i = 1; i < histSize; i++) {
        line(histImage,
                Point(bin_w * (i - 1),
                        hist_h - cvRound(b_hist.at<float>(i - 1))),
                Point(bin_w * (i), hist_h - cvRound(b_hist.at<float>(i))),
                Scalar(255, 0, 0), 2, 8, 0);
        line(histImage,
                Point(bin_w * (i - 1),
                        hist_h - cvRound(g_hist.at<float>(i - 1))),
                Point(bin_w * (i), hist_h - cvRound(g_hist.at<float>(i))),
                Scalar(0, 255, 0), 2, 8, 0);
        line(histImage,
                Point(bin_w * (i - 1),
                        hist_h - cvRound(r_hist.at<float>(i - 1))),
                Point(bin_w * (i), hist_h - cvRound(r_hist.at<float>(i))),
                Scalar(0, 0, 255), 2, 8, 0);
    }
    output = histImage;
    /*
     /// Display
     namedWindow("calcHist Demo", CV_WINDOW_AUTOSIZE);
     imshow("calcHist Demo", histImage);
     */
}
