#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QImage>
#include "CImg.h"
#include "filterbilateral.h"

class Controller
{
    public:
        Controller();
        ~Controller(){}

        QImage changeDetails();

    private:
        QImage raiseDetails();
        QImage lowerDetails();

};

#endif // CONTROLLER_H
