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
        Controller():nbIteration(iteration),alpha(0.0), beta(0.0),sigmaS(fsigmaS), sigmaR(fsigmaR){}
        ~Controller(){}

        void changeDetails(QString fileName, bool detail, QImage &image);
        void changeDetailsUser(QString fileName, bool detail, QImage &image);

        int getNbIteration(){return nbIteration;}
        void setNbIteration(int value){nbIteration = value;}
        float getAlpha(){return alpha;}
        void setAlpha(float value){alpha =  value;}
        float getBeta(){return beta;}
        void setBeta(float value){beta =  value;}
        float getSigmaS(){return sigmaS;}
        void setSigmaS(float value){sigmaS  = value;}
        float getSigmaR(){return sigmaR;}
        void setSigmaR(float value){sigmaR =  value;}

private:
        static int iteration;
        static float fsigmaS;
        static float fsigmaR;
        static float alphaRaise;
        static float betaRaise;
        static float alphaLower;
        static float betaLower;

        cimg_library::CImg<double> constructNewImage(cimg_library::CImg<double> &imgInput);
        cimg_library::CImg<double> bilateralFilter(cimg_library::CImg<double> img, float sigma);

        int nbIteration;
        float alpha;
        float beta;
        float sigmaS;
        float sigmaR;
};

#endif // CONTROLLER_H
