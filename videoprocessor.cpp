#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>

#include <opencv/cv.h>
#include <opencv/highgui.h>

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
        callProc(false), callAnal(false), callDist(false), callQuared(false),
        callCompAnal(false), callBlindAnal(false),
        delay(40), fnumber(0), stop(false), digits(0), frameToStop(-1), frameProcessor(0)
{
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


// установка объекта класса, который реализует интерфейс Distortion
void VideoProcessor::setFrameDistortion(Distortion* frameDistortionPtr) {
    frameDistortion = frameDistortionPtr;
    callDistortion();
}
//----------------------------------------------------------------------------------------


// установка объекта класса, который реализует интерфейс Losses
void VideoProcessor::setFrameQualityReduction(QualityReduction* frameQualityReductionPtr) {
    frameQualityReduction = frameQualityReductionPtr;
    callQualityReduction();
}
//----------------------------------------------------------------------------------------


// установка объекта класса, который реализует интерфейс ComparativeAnalyzer
void VideoProcessor::setFrameComparativeAnalyzer(ComparativeAnalyzer* frameComparativeAnalyzerPtr) {
    frameComparativeAnalyzer = frameComparativeAnalyzerPtr;
    callComparativeAnalyzer();
}
//----------------------------------------------------------------------------------------


// установка объекта класса, который реализует интерфейс BlindAnalyzer
void VideoProcessor::setFrameBlindAnalyzer(BlindAnalyzer* frameBlindAnalyzerPtr) {
    frameBlindAnalyzer = frameBlindAnalyzerPtr;
    callBlindAnalyzer();
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


// вызывать метод искажения---------------------------------------------------------------
void VideoProcessor::callDistortion() {
    callDist = true;
}
//----------------------------------------------------------------------------------------


// вызывать метод ухудшения качества-------------------------------------------------------
void VideoProcessor::callQualityReduction() {
    callQuared = true;
}
//----------------------------------------------------------------------------------------


// вызывать метод сравнительного анализа кадров-------------------------------------------
void VideoProcessor::callComparativeAnalyzer() {
    callCompAnal = true;
}
//----------------------------------------------------------------------------------------


// вызывать метод сравнительного анализа кадров-------------------------------------------
void VideoProcessor::callBlindAnalyzer() {
    callBlindAnal = true;
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


// не вызывать метод искажения------------------------------------------------------------
void VideoProcessor::dontCallDistortion() {
    callDist = false;
}
//----------------------------------------------------------------------------------------


// не вызывать метод ухудшения качества---------------------------------------------------
void VideoProcessor::dontCallQualityReduction() {
    callQuared = false;
}
//----------------------------------------------------------------------------------------


// не вызывать метод ухудшения качества---------------------------------------------------
void VideoProcessor::dontCallComparativeAnalyzer() {
    callCompAnal = false;
}
//----------------------------------------------------------------------------------------


// не вызывать метод ухудшения качества---------------------------------------------------
void VideoProcessor::dontCallBlindAnalyzer() {
    callBlindAnal = false;
}
//----------------------------------------------------------------------------------------


// выводить необработанные кадры----------------------------------------------------------
void VideoProcessor::displayInput(std::string wn) {

    windowNameInput = wn;
    cv::namedWindow(windowNameInput);
}
//----------------------------------------------------------------------------------------


// выводить неискаженные кадры----------------------------------------------------------
void VideoProcessor::displayWithoutLosts(std::string wn) {
    windowNameWithoutLosts = wn;
    cv::namedWindow(windowNameWithoutLosts);
}
//----------------------------------------------------------------------------------------


// выводить обработанные кадры------------------------------------------------------------
void VideoProcessor::displayOutput(std::string wn) {
    windowNameOutput = wn;
    cv::namedWindow(windowNameOutput);
}
//----------------------------------------------------------------------------------------


// выводить результаты анализатора--------------------------------------------------------
void VideoProcessor::displayAnalyzed(std::string wn) {
    windowNameAnalyzed = wn;
    cv::namedWindow(windowNameAnalyzed);
}
//----------------------------------------------------------------------------------------


void VideoProcessor::displayHistograms(std::string wn1, std::string wn2)
{
    windowNameInitialHistogram = wn1;
    windowNameFinalHistogram = wn2;
}


// не выводить обработанные кадры---------------------------------------------------------
void VideoProcessor::dontDisplay() {

    cv::destroyWindow(windowNameInput);
    cv::destroyWindow(windowNameOutput);
    cv::destroyWindow(windowNameWithoutLosts);
    cv::destroyWindow(windowNameAnalyzed);
    cv::destroyWindow(windowNameInitialHistogram);
    cv::destroyWindow(windowNameFinalHistogram);

    windowNameInput.clear();
    windowNameOutput.clear();
    windowNameWithoutLosts.clear();
    windowNameAnalyzed.clear();
    windowNameInitialHistogram.clear();
    windowNameFinalHistogram.clear();
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

    cv::Mat input_frame; //обработанный кадр
    cv::Mat processed_frame; //изначальный кадр
    cv::Mat output_frame; //изначальный кадр
    cv::Mat analyzed_frame; //проанализированный кадр
    cv::Mat histogram_initial; //гистограмма исходного кадра
    cv::Mat histogram_final; //гистограмма измененного кадра

    // если не установлено устройства захвата
    if (!isOpened())
        return;

    stop = false;

    while (!isStopped()) {

        // попытка чтения следующего кадра
        if (!readNextFrame(input_frame))
            break;

        // отображение входящего кадра
        if (windowNameInput.length() != 0)
            cv::imshow(windowNameInput, input_frame);
        // копируем кадры

        processed_frame = input_frame.clone();
        histogram_initial = input_frame.clone();
        histogram_final = input_frame.clone();

        /// ------------вызов методов анализа--------------------------
        if (callAnal) {
           frameAnalyzer->analyze(input_frame, histogram_initial);
        }
        // отображение конечной гистограммы
        if (windowNameOutput.length() != 0)
          cv::imshow(windowNameInitialHistogram, histogram_initial);
        /// -----------------------------------------------------------

        // вызов метода обработки
        if (callProc)
        {
           frameProcessor->process(input_frame, processed_frame);
           //увеличение счетчика кадров
                fnumber++;
         } else {
                processed_frame = input_frame;
         }

        //отображение обработанного кадра без внесения искажений
        if (windowNameWithoutLosts.length() != 0)
            cv::imshow(windowNameWithoutLosts, processed_frame);

        //вызов метода ухудшения качества
        if (callQuared) {
            frameQualityReduction->process(processed_frame, output_frame);
        }

        //вызов метода искажения
        if (callDist) {
            frameDistortion->process(output_frame, output_frame);
        }

        /// ------------вызов методов анализа--------------------------
        if (callAnal) {
           frameAnalyzer->analyze(output_frame, histogram_final);
        }
        // отображение конечной гистограммы
        if (windowNameOutput.length() != 0)
          cv::imshow(windowNameFinalHistogram, histogram_final);
        /// -----------------------------------------------------------

        analyzed_frame = output_frame.clone();

        if(callCompAnal) {
            frameComparativeAnalyzer->analyze(input_frame, analyzed_frame);
        } else {
           frameBlindAnalyzer->analyze(output_frame, analyzed_frame);
        }

        // отображение обработанного кадра
        if (windowNameOutput.length() != 0)
          cv::imshow(windowNameOutput, output_frame);

        // отображение обработанного кадра
        if (windowNameAnalyzed.length() != 0)
          cv::imshow(windowNameAnalyzed, analyzed_frame);

        // запись кадра
        if (outputFile.length() != 0)
            writeNextFrame(output_frame);

        // задержка
        if (delay >= 0 && cv::waitKey(delay) >= 0)
            stopIt();

        // проверка остановки
        if (frameToStop >= 0 && getFrameNumber() == frameToStop)
            stopIt();
    }
}
//----------------------------------------------------------------------------------------
