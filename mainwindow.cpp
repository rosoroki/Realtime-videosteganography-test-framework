#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QtGui>
#include <stdio.h>
#include <stdlib.h>

#include <opencv/cv.h>
#include <opencv/highgui.h>

#include "videoprocessor.h"
#include "frameprocessor.h"
#include "QRprocessor.h"
#include "frameanalyzerhistogram.h"
#include "qrencode.h"
#include "basicdistortion.h"
#include "basicqualityreduction.h"
#include "comparativeanalyzer.h"

using namespace std;
using namespace cv;

MainWindow::MainWindow(QWidget *parent) :  QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setupEnvironment(); //загружает все используемыек модулиц
}


//деструктор класса главного окна
MainWindow::~MainWindow()
{
    delete ui;
}


//метод загрузки всех внешних модулей
void MainWindow::setupEnvironment()
{    
    ui->useDefaultWebCam->setChecked(true);

    ui->comparative_radio->setChecked(true);

    ui->qualityreductionmethod->addItem("Basic Quality Reduction");
    ui->distortionmethod->addItem("Basic Distortion");
}


// обработчик события "нажата кнопка HANDLE"
void MainWindow::on_pushButton_clicked()
{
    //Установки ввода видео------------------------------------------------------------------------------------------------------
    int capDevice = 0; //устройство захвата видео
    VideoProcessor processor;  //переменная класса видеообработки
    if(ui->useAnotherCaptureDevice->isChecked()) //если выбран источник, отличный от источника по умолчанию
    {
        capDevice=ui->lineEdit->text().toInt(); //попытка преобразования строки в число и запись в переменную устройства захвата
    }
    processor.setInput(capDevice);   //установка устройства захвата видео; 0 - вебкамера по умолчанию
    //---------------------------------------------------------------------------------------------------------------------------


    //Установки стеганографических методов---------------------------------------------------------------------------------------
    QRprocessor qrprocessor(ui->secretMessage->toPlainText().toStdString(),ui->colorChannel->text().toStdString(),ui->intensity->text().toStdString());
    processor.setFrameProcessor(&qrprocessor);
    //---------------------------------------------------------------------------------------------------------------------------


    //Установки методов искажения видеоизображения и ухудшения качества-----------------------------------------------------------
    //BasicDistortion basicdistortion(ui->basicdistortionparams->text().toStdString());
    //processor.setFrameDistortion(&basicdistortion);

    BasicQualityReduction basicqualityreduction(ui->qualityreductionparams->text().toStdString());
    processor.setFrameQualityReduction(&basicqualityreduction);
    //---------------------------------------------------------------------------------------------------------------------------


    //Установки средств обработки и анализа видео--------------------------------------------------------------------------------
    FrameAnalyzerHistogram FAH;
    processor.setFrameAnalyzer(&FAH);
    //---------------------------------------------------------------------------------------------------------------------------

    ComparativeAnalyzer CA(ui->colorchannelanalyzer->text().toStdString(),ui->intensityanalyzer->text().toStdString());
    BlindAnalyzer BA(ui->colorchannelanalyzer->text().toStdString(),ui->intensityanalyzer->text().toStdString());

    if (ui->comparative_radio->isChecked())
    {
        //Установки сравниительного анализатора----------------------------------------------------------------------------------
        processor.setFrameComparativeAnalyzer(&CA);
        //-----------------------------------------------------------------------------------------------------------------------
    } else {
        //Установки слепового анализатора----------------------------------------------------------------------------------------
        processor.setFrameBlindAnalyzer(&BA);
        //-----------------------------------------------------------------------------------------------------------------------
    }

    //Запуск на выполнение обработчиков------------------------------------------------------------------------------------------
    cv::Size size= processor.getFrameSize();
    std::cout << size.width << " " << size.height << std::endl;
    int t = round(processor.getFrameRate());
    std::cout << t << std::endl;

    processor.displayInput("Intput Video");   //вывод на экран исходного видео
    processor.displayWithoutLosts("Without Losts");   //вывод на экран видео без искажений
    processor.displayOutput("Output Video");   //вывод на экран обработанного видео
    processor.displayAnalyzed("Analyzed Video");   //вывод на экран результата анализа

    processor.displayHistograms("Initial Histogram", "Final Histogram");   //вывод на экран гистограмм

    processor.run();  //запуск на выполнение

    cv::waitKey();  //ожидание нажатия на кнопку Enter
    //---------------------------------------------------------------------------------------------------------------------------   
}
