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
        /**
         * @brief Constructeur par défaut
         */
        Controller():nbIteration(iteration),alpha(0.0), beta(0.0),sigmaS(fsigmaS), sigmaR(fsigmaR), fileNameInput(""),detail(true){}
        /**
         * @brief Constructeur par recopie
         * @param c Controlleur a copié
         */
        Controller(const Controller &c): nbIteration(c.iteration), alpha(c.alpha), beta(c.beta), sigmaS(c.sigmaS), sigmaR(c.sigmaR), fileNameInput(c.fileNameInput), detail(c.detail){}
        /**
          * @brief Destructeur
          */
        ~Controller(){}

        /**
         * @brief Modifie l'image itérant un filtre bilatéral
         * Cette fonction permet de manipuler les détails d'une image en itérant un filtre bilatéral dessus.
         * @return Retourne la nouvelle image reconstruite.
         */
        QImage* changeDetailsUser();

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

        QString getFileNameInput(){return fileNameInput;}
        void setFileNameInput(const QString &value){fileNameInput = value;}

        bool getDetail(){return detail;}
        void setDetail(bool value){detail = value;}

private:
        static int iteration;
        static float fsigmaS;
        static float fsigmaR;
        static float alphaRaise;
        static float betaRaise;
        static float alphaLower;
        static float betaLower;

        /**
         * @brief Construit la nouvelle image en itérant le filtre bilatéral dessus.
         * @param imgInput L'image à manipuler
         * @return Retourne la nouvelle image reconstruite.
         */
        cimg_library::CImg<double> constructNewImage(cimg_library::CImg<double> &imgInput);
        /**
         * @brief Applique le filtre bilatéral à l'image <b>img</b>
         * @param img L'image sur laquelle le filtre bilatéral est exécuté
         * @param sigma Valeur de sigma R (Sigma S étant fixe).
         * @return Retourne la résultante du filtre bilatéral.
         */
        cimg_library::CImg<double> bilateralFilter(cimg_library::CImg<double> img, float sigma);

        int nbIteration;
        float alpha;
        float beta;
        float sigmaS;
        float sigmaR;
        QString fileNameInput;
        bool detail;
};

#endif // CONTROLLER_H
