#include <QtGui/QApplication>
#include "mainwindow.h"

using namespace std;

int main(int argc, char *argv[])
{
    /*
    // create an embedded R instance
    //RInside R(argc, argv);
    RInside R(argc, argv);

    // evaluate an R expression with curve()
    // because RInside defaults to interactive=false we use a file
    std::string cmd = "tmpf <- tempfile('curve'); "
            "png(tmpf); "
            "curve(x^5, -10, 10, 200); "
            "dev.off();"
            "tmpf";


    //cmd = "x11(); cars <- c(1, 3, 6, 4, 9); plot(cars); Sys.sleep(10);";
    //R.parseEvalQ(cmd);

    cmd = "x11(); x <- stats::rnorm(50); opar <- par(bg = 'white'); plot(x, ann = FALSE, type = 'n'); Sys.sleep(10);";
    R.parseEvalQ(cmd);

    cmd = "x11();"
    "x <- stats::rnorm(50);"
    "opar <- par(bg = 'white');"
    "plot(x, ann = FALSE, type = 'n');"
    "abline(h = 0, col = gray(.90));"
    "lines(x, col = 'green4', lty = 'dotted');"
    "points(x, bg = 'limegreen', pch = 21);"
    "title(main = 'Simple Use of Color In a Plot', xlab = 'Just a Whisper of a Label', col.main = 'blue', col.lab = gray(.8), cex.main = 1.2, cex.lab = 1.0, font.main = 4, font.lab = 3);"
    "Sys.sleep(10);";
    R.parseEvalQ(cmd);
*/


    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    
    return a.exec();
}
