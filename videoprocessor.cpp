#if !defined VIDEO

#define VIDEOPROCESSOR

#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>
#include <cv.h>
#include <highgui.h>

#include "videoprocessor.h"
#include "frameprocessor.h"
#include "QRprocessor.h"


// переход на следующий кадр--------------------------------------------------------------
bool VideoProcessor::readNextFrame(cv::Mat& frame) {

    if (images.size() == 0)
        return capture.read(frame);
    else {

        if (itImg != images.end()) {

            frame = cv::imread(*itImg);
            itImg++;
            return frame.data != 0;
        }
    }
}
//----------------------------------------------------------------------------------------


//запись кадра----------------------------------------------------------------------------
void VideoProcessor::writeNextFrame(cv::Mat& frame) {
    /*

    if (extension.length()) { // then we write images

        std::stringstream ss;
        ss << outputFile << std::setfill('0') << std::setw(digits)
                << currentIndex++ << extension;
        cv::imwrite(ss.str(), frame);

    } else { // then write video file

        writer.write(frame);
    }
    */
}
//----------------------------------------------------------------------------------------


// конструктор; устанавливает значения по умолчанию---------------------------------------
VideoProcessor::VideoProcessor() :
        callProc(false), delay(40), fnumber(0), stop(false), digits(0), frameToStop(-1), frameProcessor(0) {
}
//----------------------------------------------------------------------------------------


// установка имени видеофайла-------------------------------------------------------------
bool VideoProcessor::setInput(std::string filename) {

    fnumber = 0;
    webcam = false;
    //Если ресурс уже был связан с объектом захвата видео
    capture.release();
    images.clear();

    //Открытие видеофайла
    return capture.open(filename);
}
//----------------------------------------------------------------------------------------


//установка ввода по идентефикатору-------------------------------------------------------
bool VideoProcessor::setInput(int id) {

    fnumber = 0;
    webcam = true;
    //Если ресурс уже был связан с объектом захвата видео
    capture.release();
    images.clear();

    //открытие устройства захвата
    return capture.open(id);
}
//----------------------------------------------------------------------------------------


//установка видеофайла для записи---------------------------------------------------------
// по умолчанию будут использованы те же параметры, что и для входящего видеопотока
bool VideoProcessor::setOutput(const std::string &filename, int codec, double framerate, bool isColor) {
    outputFile = filename;
    extension.clear();

    if (framerate == 0.0)
        framerate = getFrameRate(); //так же как и во входном потоке

    char c[4];
    //использовать тот же коде, что и во входном потоке
    if (codec == 0) {
        codec = getCodec(c);
    }

    //Открыть поток записи
    return writer.open(outputFile, // имя файла
            1, //CV_FOURCC('D','I','V','X'), //CV_FOURCC('X','V','I','D'),//CV_FOURCC ('D','I','V','3'), //используемый кодек
            framerate,      //кадры в секунду
            getFrameSize(), // размер кадра
            1);       // цветное ли видео?
}
//----------------------------------------------------------------------------------------


// установка вывода - набор изображений---------------------------------------------------
// расширение должно быть ".jpg", ".bmp" ...
bool VideoProcessor::setOutput(const std::string &filename,
        const std::string &ext, int numberOfDigits, int startIndex) { // start index
    // количество цифр должно быть положительным
    if (numberOfDigits < 0)
        return false;

    // имена файлов и их общие расширения
    outputFile = filename;
    extension = ext;

    // количество цифр в схеме нумерования файлов
    digits = numberOfDigits;
    // начинать нумерование с данного индекса
    currentIndex = startIndex;

    return true;
}
//----------------------------------------------------------------------------------------


// установка объекта класса, который реализует интерфейс FrameProcessor
void VideoProcessor::setFrameProcessor(FrameProcessor* frameProcessorPtr) {

    // объект обработки кадров, который будет использоваться
    frameProcessor = frameProcessorPtr;
    callProcess();
}
//----------------------------------------------------------------------------------------


// установка объекта класса, который реализует интерфейс FrameAnalyzer
void VideoProcessor::setFrameAnalyzer(FrameAnalyzer* frameAnalyzerPtr) {
    frameAnalyzer = frameAnalyzerPtr;
    callAnalyzer();
}
//----------------------------------------------------------------------------------------


// остановка обработки в определенном месте-----------------------------------------------
void VideoProcessor::stopAtFrameNo(long frame) {

    frameToStop = frame;
}
//----------------------------------------------------------------------------------------


// вызывать метод обработки---------------------------------------------------------------
void VideoProcessor::callProcess() {

    callProc = true;
}
//----------------------------------------------------------------------------------------


// вызывать метод анализа-----------------------------------------------------------------
void VideoProcessor::callAnalyzer() {
    callAnal = true;
}
//----------------------------------------------------------------------------------------


// не вызывать метод обработки------------------------------------------------------------
void VideoProcessor::dontCallProcess() {

    callProc = false;
}
//----------------------------------------------------------------------------------------


// не вызывать метод анализа--------------------------------------------------------------
void VideoProcessor::dontCallAnalyzer() {
    callAnal = false;
}
//----------------------------------------------------------------------------------------


// выводить необработанные кадры----------------------------------------------------------
void VideoProcessor::displayInput(std::string wn) {

    windowNameInput = wn;
    cv::namedWindow(windowNameInput);
}
//----------------------------------------------------------------------------------------


// выводить обработанные кадры------------------------------------------------------------
void VideoProcessor::displayOutput(std::string wn) {

    windowNameOutput = wn;
    cv::namedWindow(windowNameOutput);
}
//----------------------------------------------------------------------------------------


// не выводить обработанные кадры---------------------------------------------------------
void VideoProcessor::dontDisplay() {

    cv::destroyWindow(windowNameInput);
    cv::destroyWindow(windowNameOutput);
    windowNameInput.clear();
    windowNameOutput.clear();
}
//----------------------------------------------------------------------------------------


// установка задержки между каждый кадром-------------------------------------------------
// 0 - ждать следующего кадра
// отрицательное - без зедержки
void VideoProcessor::setDelay(int d) {
    delay = d;
}
//----------------------------------------------------------------------------------------


// получить количество обработанных кадров
long VideoProcessor::getNumberOfProcessedFrames() {

    return fnumber;
}
//----------------------------------------------------------------------------------------


// получение размера кадра
cv::Size VideoProcessor::getFrameSize() {

    if (images.size() == 0) {

        // получением размера от устройства захвата
        int w = static_cast<int>(capture.get(CV_CAP_PROP_FRAME_WIDTH));
        int h = static_cast<int>(capture.get(CV_CAP_PROP_FRAME_HEIGHT));

        return cv::Size(w, h);

    } else { // если ввод - это вектор изображений

        cv::Mat tmp = cv::imread(images[0]);
        if (!tmp.data)
            return cv::Size(0, 0);
        else
            return tmp.size();
    }
}
//----------------------------------------------------------------------------------------


//номер следующего кадра------------------------------------------------------------------
long VideoProcessor::getFrameNumber() {

    if (images.size() == 0) {

        // получение информации об устройстве захвата
        long f = static_cast<long>(capture.get(CV_CAP_PROP_POS_FRAMES));
        return f;

    } else { // если ввода производится из вектора изображений

        return static_cast<long>(itImg - images.begin());
    }
}
//----------------------------------------------------------------------------------------


//возврат положения в милисекундах--------------------------------------------------------
double VideoProcessor::getPositionMS() {

    // неопределно для вектора изображений
    if (images.size() != 0)
        return 0.0;

    double t = capture.get(CV_CAP_PROP_POS_MSEC);
    return t;
}
//----------------------------------------------------------------------------------------


// количествао кадров в секунду-----------------------------------------------------------
double VideoProcessor::getFrameRate() {

    // неопределно для вектора изображений
    if (images.size() != 0)
        return 0;

    double r = capture.get(CV_CAP_PROP_FPS);
    return r;
}
//----------------------------------------------------------------------------------------


// возврат количества кадров в видео------------------------------------------------------
long VideoProcessor::getTotalFrameCount() {

    //для вектора изображений
    if (images.size() != 0)
        return images.size();

    long t = capture.get(CV_CAP_PROP_FRAME_COUNT);
    return t;
}
//----------------------------------------------------------------------------------------с


// получение кодека видео-----------------------------------------------------------------
int VideoProcessor::getCodec(char codec[4]) {

    // не определено для вектора изображений
    if (images.size() != 0)
        return -1;

    union {
        int value;
        char code[4];
    } returned;

    returned.value = static_cast<int>(capture.get(CV_CAP_PROP_FOURCC));

    codec[0] = returned.code[0];
    codec[1] = returned.code[1];
    codec[2] = returned.code[2];
    codec[3] = returned.code[3];

    return returned.value;
}
//----------------------------------------------------------------------------------------


// Остановка работы-----------------------------------------------------------------------
void VideoProcessor::stopIt() {
    stop = true;
}
//----------------------------------------------------------------------------------------


// Остановлена ли работа?-----------------------------------------------------------------
bool VideoProcessor::isStopped() {
    return stop;
}
//----------------------------------------------------------------------------------------


// Открыто ли устройство захвата?---------------------------------------------------------
bool VideoProcessor::isOpened() {
    return capture.isOpened() || !images.empty();
}
//----------------------------------------------------------------------------------------


// запуск---------------------------------------------------------------------------------
void VideoProcessor::run() {

    cv::Mat frame;  //текущий кадр
    cv::Mat output; //обработанный кадр

    // если не установлено устройства захвата
    if (!isOpened())
        return;

    stop = false;

    while (!isStopped()) {

        // попотка чтения следующего кадра
        if (!readNextFrame(frame))
            break;

        // отображение входящего кадра
        if (windowNameInput.length() != 0)
            cv::imshow(windowNameInput, frame);

        // вызов метода обработки
        if (callProc)
        {
            frameProcessor->process(frame, output);
            //увеличение счетчика кадров
                fnumber++;
         } else {
                output = frame;
         }

        //вызов метода анализа
        if (callAnal) {
            frameAnalyzer->analyze(output);
        }

        // запись кадра
        if (outputFile.length() != 0)
            writeNextFrame(output);

        // отображение обработанного кадра
        if (windowNameOutput.length() != 0)
            cv::imshow(windowNameOutput, output);

        // задержка
        if (delay >= 0 && cv::waitKey(delay) >= 0)
            stopIt();

        // проверка остановки
        if (frameToStop >= 0 && getFrameNumber() == frameToStop)
            stopIt();
    }

}
//----------------------------------------------------------------------------------------

#endif
