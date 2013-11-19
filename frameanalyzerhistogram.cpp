#include "frameanalyzerhistogram.h"
#include <opencv/cv.h>
#include <opencv/highgui.h>


//-----------------------------------------------------------------------------------------------------
FrameAnalyzerHistogram::FrameAnalyzerHistogram()
{

}


//-----------------------------------------------------------------------------------------------------
void FrameAnalyzerHistogram::analyze(Mat &input, Mat &output) {
    lastFrame=currentFrame;
    currentFrame=input;
    frameList.append(input);
    std::cout << frameList.length() << std::endl;

    /// ----------------------------------------------------------------------
    vector<Mat> bgr_planes; /// Separate the image in 3 places ( B, G and R )
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

    // Нормализация результата к [ 0, histImage.rows ]
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


//-----------------------------------------------------------------------------------------------------
void FrameAnalyzerHistogram::histogram() {
    std::cout << "Histogram!" << std::endl;
}


//-----------------------------------------------------------------------------------------------------
void FrameAnalyzerHistogram::alphaCompose(cv::Mat &rgba1, cv::Mat &rgba2, cv::Mat &rgba_dest) {
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


//-----------------------------------------------------------------------------------------------------
void FrameAnalyzerHistogram::printHistograms(cv::Mat &input, cv::Mat &output) {

    vector<Mat> bgr_planes; /// Separate the image in 3 places ( B, G and R )
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

    // Нормализация результата к [ 0, histImage.rows ]
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
