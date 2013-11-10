#ifndef VIDEOROCESSOR_H_
#define VIDEOROCESSOR_H_

#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>
#include <cv.h>
#include <highgui.h>

#include "frameprocessor.h"
#include "frameanalyzer.h"

class VideoProcessor {

private:
    // Объект захвата видео
    cv::VideoCapture capture;    
    // указатель на класс, реализующий интрефейс FrameProcessor
    FrameProcessor *frameProcessor;
    // указатель на класс, реализующий интрефейс FrameAnalyzer
    FrameAnalyzer *frameAnalyzer;
    // будет ли вызван метод обработки
    bool callProc;
    // будет ли вызван метод анализа
    bool callAnal;
    // Имя окна вывода необработанного видео
    std::string windowNameInput;
    // Имя окна вывода обработанного видео
    std::string windowNameOutput;
    // задержка между кадрами
    int delay;
    // количество обработанных кадров
    long fnumber;
    // оставновка на этом кадре
    long frameToStop;
    // остановка выполнения
    bool stop;
    // вебкамера?
    bool webcam;

    // вектор имен файлов, используемый для ввода
    std::vector<std::string> images;
    // итератор вектора изображений
    std::vector<std::string>::const_iterator itImg;

    // объект записи видео OpenCV
    cv::VideoWriter writer;
    //имя файла для записи
    std::string outputFile;

    // текущий индекс для записываемых изображений
    int currentIndex;
    // количество цифр в именах записываемых файлов
    int digits;
    // расширение записываемых изображений
    std::string extension;


    bool readNextFrame(cv::Mat& frame);
    void writeNextFrame(cv::Mat& frame);

public:
    VideoProcessor();
    bool setInput(std::string filename);
    bool setInput(int id);
    bool setInput(const std::vector<std::string>& imgs);
    bool setOutput(const std::string &filename, int codec = 0, double framerate = 0.0, bool isColor = true);
    bool setOutput(const std::string &filename, const std::string &ext, int numberOfDigits = 3, int startIndex = 0);
    void setFrameProcessor(void (*frameProcessingCallback)(cv::Mat&, cv::Mat&));
    void setFrameProcessor(FrameProcessor* frameProcessorPtr);
    void setFrameAnalyzer(FrameAnalyzer* frameAnalyzerPtr);
    void stopAtFrameNo(long frame);
    void callProcess();
    void callAnalyzer();
    void dontCallProcess();
    void dontCallAnalyzer();
    void displayInput(std::string wn);
    void displayOutput(std::string wn);
    void dontDisplay();
    void setDelay(int d);
    long getNumberOfProcessedFrames();
    cv::Size getFrameSize();
    long getFrameNumber();
    double getPositionMS();
    double getFrameRate();
    long getTotalFrameCount();
    int getCodec(char codec[4]);
    bool setFrameNumber(long pos);    
    void stopIt();
    bool isStopped() ;
    bool isOpened();
    void run();
};

#endif
