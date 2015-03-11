#include "controller.h"

using namespace cimg_library;
using namespace std;

float fsigmaS = 60;
float fsigmaR = 15;
float alphaRaise = 0.8;
float betaRaise = 3;
float alphaLower = 1;
float betaLower = 0.5;
int nbrIteration = 3;

QImage* Controller::changeDetails(QString fileName, bool detail)
{
    CImg<double> imgInput(fileName.toStdString().c_str());
    CImgDisplay (imgInput,"entree");
    CImg<double> imgOutput;
    // rehaussement
    if(detail){
        imgOutput = raiseDetails(imgInput);
    }
    // attenuation
    else{
        imgOutput = lowerDetails(imgInput);
    }

    CImgDisplay display(imgOutput, "Manipulation");

    return new QImage();
}

CImg<double> Controller::raiseDetails(CImg<double> imgInput)
{
    CImg<double> gImg(imgInput.width(), imgInput.height(), imgInput.depth(), imgInput.spectrum(),0);

    CImgList<double> base(nbrIteration+1);
    base.insert(imgInput, 0);
    CImgList<double> detail(nbrIteration);

    FilterBilateral fb;
    fb.set_fSigmaS(fsigmaS);

    for(int i=0; i<nbrIteration; i++){
        fb.set_img(base(i));
        fb.set_fSigmaS(fsigmaR);

        base.insert(fb.applyFilter(), i+1);
        detail.insert(base(i) - base(i+1), i);
        gImg += (betaRaise*(i+1) *detail(i));
    }
    gImg += (alphaRaise*base(nbrIteration));

    return gImg.get_cut(0,255);
}

CImg<double> Controller::lowerDetails(cimg_library::CImg<double> imgInput)
{
    CImg<double> gImg(imgInput.width(), imgInput.height(), imgInput.depth(), imgInput.spectrum(),0);

    CImgList<double> base(nbrIteration+1);
    base.insert(imgInput, 0);
    CImgList<double> detail(nbrIteration);

    FilterBilateral fb;
    fb.set_fSigmaS(fsigmaS);

    for(int i=0; i<nbrIteration; i++){
        fb.set_img(base(i));
        fb.set_fSigmaS(fsigmaR);

        base.insert(fb.applyFilter(), i+1);
        detail.insert(base(i) - base(i+1), i);
        gImg += (betaLower*(i+1) *detail(i));
    }
    gImg += (alphaLower*base(nbrIteration));

    return gImg.get_cut(0,255);
    return CImg<double>();
}

