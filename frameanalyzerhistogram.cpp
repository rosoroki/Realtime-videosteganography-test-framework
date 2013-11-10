#include "frameanalyzerhistogram.h"
#include "cv.h"
#include <highgui.h>

FrameAnalyzerHistogram::FrameAnalyzerHistogram()
{

}

void FrameAnalyzerHistogram::analyze(Mat &input) {
    lastFrame=currentFrame;
    currentFrame=input;
    frameList.append(input);
    std::cout << frameList.length() << std::endl;
}

void FrameAnalyzerHistogram::saveList() {

    VideoWriter oVideoWriter ("/home/srj/MyVideo2.avi",
                              //CV_FOURCC('P','I','M','1'),
                              //CV_FOURCC('I', 'Y', 'U', 'V'),
                              CV_FOURCC('M', 'J', 'P', 'G'),
                              15, cv::Size(640,480), true); //инициализация объекта VideoWriter

      if ( !oVideoWriter.isOpened() )
      {
        std::cout << "ERROR: Failed to write the video" << std::endl;
        //return -1;
      } else
      {
          int i=1;
          std::cout << frameList.length() << std::endl;
       while (i<frameList.length())
        {
            oVideoWriter.write(frameList[i]); //запись кадра в файл
            i++;
        }
      }
}

void FrameAnalyzerHistogram::histogram() {
    std::cout << "Histogram!" << std::endl;
}

