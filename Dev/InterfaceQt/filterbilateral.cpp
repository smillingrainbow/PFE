#include "filterbilateral.h"

using namespace cimg_library;
using namespace std;

double FilterBilateral::loiGaussienne(double value, float sigma){

    double gauss = (1/(2*M_PI* pow(sigma,2))) * exp(-(pow(value,2))/(2*pow(sigma,2)));

    return gauss;
}

double FilterBilateral::distanceEuclidienne(int xP, int yP, int xQ, int yQ){

    double dist = pow(xP - xQ, 2) + pow(yP - yQ, 2);
    dist = sqrt(dist);
    return dist;
}

CImg< double > FilterBilateral::applyFilter(){
    CImg<double> bfImg;
    cout << "Nombre de canaux de l'image : " << img.spectrum() << endl;
    // image en niveau de gris
    if(img.spectrum() == 1){
        bfImg = applyFilterNdG();
    }
    // image RGB
    else{
        bfImg = applyFilterRGB();
    }

    return bfImg;
}

CImg< double > FilterBilateral::applyFilterNdG()
{
    CImg<double> bfImg(width, height, img.depth(), img.spectrum(),0);
    double wp=0;
    int size = 21;
    int iXdebut=0, iYdebut=0, iXfin=0, iYfin=0;
    double gauss=0;
    double distEuclidienne=0;
    double value;
    double valueNormal=0.0;
    // parcours de l'image sur la longeur (y) et la largeur(x)
    cimg_forX(img, x){
        cimg_forY(img, y){
            wp=0;
            value = 0.0;

            // parcours d'un carré de 21x21 autour du pixel courant
            // délimitation des variables de parcours en fonction de la position du pixel
            if(x<(size/2)-1){
                iXdebut= 0;
            }
            else{
                iXdebut = x - (size/2);
            }
            if(y < (size/2)-1){
                iYdebut = 0;
            }
            else{
                iYdebut =  y - (size/2);
            }

            if(x+(size/2) > width){
                iXfin = width-1;
            }
            else{
                iXfin = x + (size/2);
            }

            if(y+(size/2) > height){
                iYfin = height-1;
            }
            else{
                iYfin = y + (size/2);
            }

            // parcours sur la largeur
            for(int iX=iXdebut; iX<=iXfin; iX++){

                // parcours sur la longueur
                for(int iY=iYdebut; iY<=iYfin; iY++){

                    distEuclidienne = distanceEuclidienne(x, y, iX, iY);
                    gauss = loiGaussienne(distEuclidienne, fSigmaS) * 						loiGaussienne(std::abs(img._atXYZC(x,y,0,0) - 						img._atXYZC(iX,iY,0,0)), fSigmaR);

                    value += gauss*img._atXYZC(iX,iY, 0, 0);
                    bfImg.set_linear_atXYZ(value, x, y, 0, 0, false);

                    wp += gauss;

                }
            }
            valueNormal = bfImg._atXYZC(x,y, 0 , 0)/wp;
            bfImg.set_linear_atXYZ(valueNormal, x,y, 0, 0, false);
        }
    }
    return bfImg;

}

CImg< double > FilterBilateral::applyFilterRGB()
{
    CImg<double> bfImg(width, height, img.depth(), img.spectrum(),0);
    // conversion de l'image RGB vers YCbCr
    CImg<double> imgY = img.get_RGBtoYCbCr();
    bfImg.RGBtoYCbCr();
    double wp=0;
    int size = 21;
    int iXdebut=0, iYdebut=0, iXfin=0, iYfin=0;
    double gauss=0;
    double distEuclidienne=0;
    double value = 0.0;
    double valueNormal=0.0;

    // parcours de l'image sur la longeur (y) et la largeur(x)
    cimg_forX(imgY, x){
        cimg_forY(imgY, y){
            wp=0;
            value = 0.0;

            // copie de Cb et Cr de l'image
            bfImg.set_linear_atXYZ(imgY._atXYZC(x,y,0,1), x, y, 0, 1, false);
            bfImg.set_linear_atXYZ(imgY._atXYZC(x,y,0,2), x, y, 0, 2, false);

            // parcours d'un carré de 21x21 autour du pixel courant
            // délimitation des variables de parcours en fonction de la position du pixel
            if(x<(size/2)-1){
                iXdebut= 0;
            }
            else{
                iXdebut = x - (size/2);
            }
            if(y < (size/2)-1){
                iYdebut = 0;
            }
            else{
                iYdebut =  y - (size/2);
            }

            if(x+(size/2) > width){
                iXfin = width-1;
            }
            else{
                iXfin = x + (size/2);
            }

            if(y+(size/2) > height){
                iYfin = height-1;
            }
            else{
                iYfin = y + (size/2);
            }

            // parcours sur la largeur
            for(int iX=iXdebut; iX<=iXfin; iX++){

                // parcours sur la longueur
                for(int iY=iYdebut; iY<=iYfin; iY++){

                    distEuclidienne = distanceEuclidienne(x, y, iX, iY);
                    gauss = loiGaussienne(distEuclidienne, fSigmaS) * 					loiGaussienne(std::abs(imgY._atXYZC(x,y,0,0) - 								imgY._atXYZC(iX,iY,0,0)), fSigmaR);

                    value += gauss*imgY._atXYZC(iX,iY, 0, 0);
                    bfImg.set_linear_atXYZ(value, x, y, 0, 0, false);

                    wp += gauss;
                }
            }
            valueNormal = bfImg._atXYZC(x,y, 0 , 0)/wp;
            bfImg.set_linear_atXYZ(valueNormal, x,y, 0, 0, false);
        }
    }
    bfImg.YCbCrtoRGB();
    return bfImg;
}
