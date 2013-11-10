#include "frameanalyzer.h"

FrameAnalyzer::FrameAnalyzer() {
    // TODO Auto-generated constructor stub
}

FrameAnalyzer::~FrameAnalyzer() {
    // TODO Auto-generated destructor stub
}

Mat& FrameAnalyzer::getMat(int index) {
    if((index<frameList.length())&&(index>=0)) {
        return frameList[index];
    }
}
