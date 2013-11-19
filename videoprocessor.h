#ifndef VIDEOROCESSOR_H_
#define VIDEOROCESSOR_H_

#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>

#include <opencv/cv.h>
#include <opencv/highgui.h>

#include "frameprocessor.h"
#include "frameanalyzer.h"
#include "distortion.h"
#include "qualityreduction.h"
#include "comparativeanalyzer.h"
#include "blindanalyzer.h"

class VideoProcessor {

private:
    // Объект захвата видеo
    cv::VideoCapture capture;    
    // указатель на класс, реализующий интрефейс FrameProcessor
    FrameProcessor *frameProcessor;
    // указатель на класс, реализующий интрефейс FrameAnalyzer
    FrameAnalyzer *frameAnalyzer;
    //указатель на класс, реализующий интерфейс QualityReduction
    QualityReduction *frameQualityReduction;
    //указатель на класс, реализующий интерфейс Distortion
    Distortion *frameDistortion;
    //укащатель на класс, реализующий интерфейс ComparativeAnalyzer
    ComparativeAnalyzer *frameComparativeAnalyzer;
    //укащатель на класс, реализующий интерфейс BlindAnalyzer
    BlindAnalyzer *frameBlindAnalyzer;
    // будет ли вызван метод обработки
    bool callProc;
    // будет ли вызван метод анализа
    bool callAnal;
    //будет ли вызван метод искажения
    bool callDist;
    //будет ли вызван метод ухудшения качества
    bool callQuared;
    //будет ли вызван сравнительный анализатор
    bool callCompAnal;
    //будет ди вызван метод слепово анализаЫ
    bool callBlindAnal;
    // Имя окна вывода необработанного видео
    std::string windowNameInput;
    // Имя окна вывода обработанного видео
    std::string windowNameOutput;
    // Имя окна вывода видео без "потерь"
    std::string windowNameWithoutLosts;
    //Имя окна вывода результата работы анализатора
    std::string  windowNameAnalyzed;
    //Имя окна вывода исходной гистограммы
    std::string  windowNameInitialHistogram;
    //Имя окна вывода результирующей гистограммы
    std::string  windowNameFinalHistogram;
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
    void setFrameDistortion(Distortion* frameDistortionPtr);
    void setFrameQualityReduction(QualityReduction* frameQualityReductionPtr);
    void setFrameAnalyzer(FrameAnalyzer* frameAnalyzerPtr);
    void setFrameComparativeAnalyzer(ComparativeAnalyzer* frameComparativeAnalyzerPtr);
    void setFrameBlindAnalyzer(BlindAnalyzer* frameBlindAnalyzerPtr);
    void stopAtFrameNo(long frame);
    void callProcess();
    void callAnalyzer();
    void callDistortion();
    void callQualityReduction();
    void callComparativeAnalyzer();
    void callBlindAnalyzer();
    void dontCallProcess();
    void dontCallAnalyzer();
    void dontCallDistortion();
    void dontCallQualityReduction();    
    void dontCallComparativeAnalyzer();
    void dontCallBlindAnalyzer();
    void displayInput(std::string wn);
    void displayOutput(std::string wn);
    void displayWithoutLosts(std::string wn);
    void displayAnalyzed(std::string wn);
    void displayHistograms(std::string wn1, std::string wn2);
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
