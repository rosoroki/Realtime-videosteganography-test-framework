#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtGui>
#include <stdio.h>
#include <stdlib.h>
#include <cv.h>
#include <highgui.h>
#include "videoprocessor.h"
#include "frameprocessor.h"
#include "QRprocessor.h"
#include "frameanalyzerhistogram.h"
#include "qrencode.h"

using namespace std;
using namespace cv;

MainWindow::MainWindow(QWidget *parent) :  QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->toolBox->setItemText(0, "Video Capture");
    ui->toolBox->setItemText(1, "Video Analyzer");

    ui->useDefaultWebCam->setChecked(true);


    //ui->comboBox->addItem("X");
    //ui->comboBox->addItem("Y");
}

//деструктор класса главного окна
MainWindow::~MainWindow()
{
    delete ui;
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


    //Установки средств обработки и анализа видео--------------------------------------------------------------------------------
    FrameAnalyzerHistogram FAH;
    processor.setFrameAnalyzer(&FAH);
    //---------------------------------------------------------------------------------------------------------------------------


    //Запуск на выполнение обработчиков------------------------------------------------------------------------------------------
    cv::Size size= processor.getFrameSize();
    std::cout << size.width << " " << size.height << std::endl;
    int t = round(processor.getFrameRate());
    std::cout << t << std::endl;

    processor.displayInput("Intput Video");   //вывод на экран исходного видео
    processor.displayOutput("Output Video");   //вывод на экран обработанного видео

    processor.run();  //запуск на выполнение

    cv::waitKey();  //ожидание нажатия на кнопку Enter
    //---------------------------------------------------------------------------------------------------------------------------


    //Сохранение результатов анализа в виделфайл---------------------------------------------------------------------------------
    FAH.saveList();
    //---------------------------------------------------------------------------------------------------------------------------
}


//void MainWindow::on_searchButton_4_clicked()
//{
    //add(7,9);
    //print();

//}



void MainWindow::on_pushButton_2_clicked()
{
    VideoCapture cap(0); // open the video camera no. 0


       if (!cap.isOpened())  // if not success, exit program
       {
           cout << "ERROR: Cannot open the video file" << endl;
           //return -1;
       }

    namedWindow("MyVideo",CV_WINDOW_AUTOSIZE); //create a window called "MyVideo"

      double dWidth = cap.get(CV_CAP_PROP_FRAME_WIDTH); //get the width of frames of the video
      double dHeight = cap.get(CV_CAP_PROP_FRAME_HEIGHT); //get the height of frames of the video

      cout << "Frame Size = " << dWidth << "x" << dHeight << endl;

      Size frameSize(static_cast<int>(dWidth), static_cast<int>(dHeight));

    VideoWriter oVideoWriter ("/home/srj/Documents/MyVideo.avi",
                              //CV_FOURCC('P','I','M','1'),
                              //CV_FOURCC('I', 'Y', 'U', 'V'),
                              CV_FOURCC('M', 'J', 'P', 'G'),
                              15, frameSize, true); //initialize the VideoWriter object

      if ( !oVideoWriter.isOpened() ) //if not initialize the VideoWriter successfully, exit the program
      {
   cout << "ERROR: Failed to write the video" << endl;
   //return -1;
      }

      int i=1;
       while (i<150)
       {
           i++;

           Mat frame;

           bool bSuccess = cap.read(frame); // read a new frame from video

           if (!bSuccess) //if not success, break loop
   {
                cout << "ERROR: Cannot read a frame from video file" << endl;
                break;
           }

   oVideoWriter.write(frame); //writer the frame into the file

           imshow("MyVideo", frame); //show the frame in "MyVideo" window

           if (waitKey(10) == 27) //wait for 'esc' key press for 30ms. If 'esc' key is pressed, break loop
          {
               cout << "esc key is pressed by user" << endl;
               break;
          }
       }
}



/*
void MainWindow::on_pushButton_clicked()
{
    std::cout << "works!" << endl;
    //VideoProcessor processor1, processor2;
    VideoProcessor processor2;
    //processor1.setInput(0);
    processor2.setInput(0);    //webcam
    //FrameProcessorExample example1;
    FrameProcessorExample2 example2;

    //processor1.setFrameProcessor(&example1);
    //processor2.dontCallProcess();

    processor2.setFrameProcessor(&example2);

    //processor1.displayInput("Input Video");
    //processor1.displayOutput("Output Video");


    cv::Size size= processor2.getFrameSize();
    std::cout << size.width << " " << size.height << std::endl;
    int t = round(processor2.getFrameRate());
    std::cout << t << std::endl;

    processor2.displayInput("Intput Video");
    processor2.displayOutput("Output Video");

    // Play the video at the original frame rate
    //processor1.setDelay(40);

        // Set the frame processor callback function
        //processor.setFrameProcessor(canny);
        // Start the process
        //processor1.run();
    processor2.run();
    cv::waitKey();
}
*/
