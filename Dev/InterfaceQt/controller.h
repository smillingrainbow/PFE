#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QImage>
#include <string>
#include "filterbilateral.h"
#include "CImg.h"

class Controller
{
    public:
        Controller(){}
        ~Controller(){}

        QImage* changeDetails(QString fileName, bool detail);

    private:
        cimg_library::CImg<double> raiseDetails(cimg_library::CImg<double> imgInput);
        cimg_library::CImg<double> lowerDetails(cimg_library::CImg<double> imgInput);

};

#endif // CONTROLLER_H
