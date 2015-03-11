#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QImage>
#include <QFileInfo>
#include <string>
#include <time.h>

#include "filterbilateral.h"
#include "CImg.h"

class Controller
{
    public:
        Controller(){}
        ~Controller(){}

        QImage* changeDetails(QString fileName, bool detail);

    private:
        cimg_library::CImg<double> raiseDetails(cimg_library::CImg<double> &imgInput);
        cimg_library::CImg<double> lowerDetails(cimg_library::CImg<double> &imgInput);
        cimg_library::CImg<double> bilateralFilter(cimg_library::CImg<double> img, float sigmaR);
};

#endif // CONTROLLER_H
