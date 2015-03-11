#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QImage>
//#include "filterbilateral.h"

class Controller
{
    public:
        Controller(){}
        ~Controller(){}

        QImage* changeDetails(QString fileName, bool detail);

    private:
        QImage raiseDetails();
        QImage lowerDetails();

};

#endif // CONTROLLER_H
