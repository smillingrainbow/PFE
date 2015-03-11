#include "controller.h"

using namespace cimg_library;
using namespace std;

float fsigmaS = 60;
float fsigmaR = 15;
float alphaRaise = 0.8;
float betaRaise = 3;
float alphaLower = 1;
float betaLower = 0.5;
int nbrIteration = 1;

QImage* Controller::changeDetails(QString fileNameInput, bool detail)
{
    CImg<double> imgInput(fileNameInput.toStdString().c_str());
    CImg<double> imgOutput;

    // rehaussement
    if(detail){
        imgOutput = raiseDetails(imgInput);
    }
    // attenuation
    else{
        imgOutput = lowerDetails(imgInput);
    }
    imgOutput.get_cut(0,255);

    QFileInfo fileInput(fileNameInput);
    QString fileNameOutput = fileInput.path() +"fb_"+fileInput.fileName();
    CImg<double> (imgOutput.save(fileNameOutput.toStdString().c_str()));
    QImage *img = new QImage;
    img->load(fileNameOutput);

    QFile fileOutput(fileNameOutput);
    fileOutput.remove();

    return img;
}

CImg<double> Controller::raiseDetails(CImg<double>& imgInput)
{
    cout << "==========RAISE DETAILS DEBUT==========" << endl;

    CImg<double> gImg(imgInput.width(), imgInput.height(), imgInput.depth(), imgInput.spectrum(),0);

    CImgList<double> base(nbrIteration+1);
    base.insert(imgInput, 0);
    CImgList<double> detail(nbrIteration);

    float sigmaR = fsigmaR;

    for(int i=0; i<nbrIteration; i++){
        cout<< "Iteration : " << i << endl;
        base.insert(bilateralFilter(base(i), sigmaR), i+1);
        detail.insert(base(i) - base(i+1), i);
        gImg += (betaRaise*(i+1) *detail(i));
        sigmaR *= 2;
    }
    gImg += (alphaRaise*base(nbrIteration));
    cout << "==========RAISE DETAILS FIN==========" << endl;

    return gImg.get_cut(0,255);
}

CImg<double> Controller::lowerDetails(cimg_library::CImg<double> &imgInput)
{
    cout << "==========LOWER DETAILS DEBUT==========" << endl;

    CImg<double> gImg(imgInput.width(), imgInput.height(), imgInput.depth(), imgInput.spectrum(),0);

    CImgList<double> base(nbrIteration+1);
    base.insert(imgInput, 0);
    CImgList<double> detail(nbrIteration);

    float sigmaR = fsigmaR;

    for(int i=0; i<nbrIteration; i++){
        cout<< "Iteration : " << i << endl;
        base.insert(bilateralFilter(base(i), sigmaR), i+1);
        detail.insert(base(i) - base(i+1), i);
        gImg += (betaLower*(i+1) *detail(i));
        sigmaR *= 2;
    }
    gImg += (alphaLower*base(nbrIteration));

    cout << "==========LOWER DETAILS FIN==========" << endl;

    return gImg.get_cut(0,255);
}

CImg<double> Controller::bilateralFilter(CImg<double> img, float sigmaR){
    double temps;
    clock_t start;

    FilterBilateral fb(fsigmaS, sigmaR, img);
    cout<< ">>>>>FILTRE BILATERAL DEBUT" << endl;
    cout << "Sigma S : " << fsigmaS << " Sigma R : " << sigmaR << endl;

    start = clock();
    CImg<double> fbImg = fb.applyFilter();
    temps = (double) (start - clock())/(double) CLOCKS_PER_SEC;

    cout << "Temps d'éxécution : " << temps << "s" <<endl;
    cout << "<<<<<FILTRE BILATERAL FIN" << endl;

    return CImg<double> (fbImg.get_cut(0,255));
}

