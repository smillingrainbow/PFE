#include "controller.h"

using namespace cimg_library;
using namespace std;

int Controller::iteration = 1;
float Controller::fsigmaS = 60.0;
float Controller::fsigmaR = 15.0;
float Controller::alphaRaise = 0.8;
float Controller::betaRaise = 3;
float Controller::alphaLower = 1;
float Controller::betaLower = 0.5;

QImage* Controller::changeDetailsUser(){
    CImg<double> imgInput(fileNameInput.toStdString().c_str());
    CImg<double> imgOutput;
    QImage *image = new QImage;
    // Si l'utilisateur n'a pas saisie les valeurs d'alpha et beta
    // on les modifie avec les valeurs par défaut correspondant au mode
    // de manipulation demandé
    if(detail){
        if(alpha==0.0)
            alpha = alphaRaise;
        if(beta==0.0)
            beta = betaRaise;
    }
    else{
        if(alpha==0.0)
            alpha = alphaLower;
        if(beta==0.0)
            beta = betaLower;
    }

    imgOutput = constructNewImage(imgInput);
    imgOutput.get_cut(0,255);

    QFileInfo fileInput(fileNameInput);
    QString fileNameOutput = fileInput.path() +"fb_"+fileInput.fileName();
    CImg<double> (imgOutput.save(fileNameOutput.toStdString().c_str()));
    image->load(fileNameOutput);

    QFile fileOutput(fileNameOutput);
    fileOutput.remove();

    return image;
}

CImg<double> Controller::constructNewImage(CImg<double>& imgInput)
{
    cout << "==========CONSTRUCT NEW IMAGE DEBUT==========" << endl;

    CImg<double> gImg(imgInput.width(), imgInput.height(), imgInput.depth(), imgInput.spectrum(),0);

    CImgList<double> base(nbIteration+1);
    base.insert(imgInput, 0);
    CImgList<double> detail(nbIteration);

    float sigma = sigmaR;

    for(int i=0; i<nbIteration; i++){
        cout<< "Iteration : " << i << endl;
        base.insert(bilateralFilter(base(i), sigma), i+1);
        detail.insert(base(i) - base(i+1), i);
        gImg += (beta*(i+1) *detail(i));
        sigma *= 2;
    }
    gImg += (alpha*base(nbIteration));
    cout << "==========CONSTRUCT NEW IMAGE FIN==========" << endl;

    return gImg.get_cut(0,255);
}


CImg<double> Controller::bilateralFilter(CImg<double> img, float sigma){
    double temps;
    clock_t start;

    FilterBilateral fb(sigmaS, sigma, img);
    cout<< ">>>>>FILTRE BILATERAL DEBUT" << endl;
    cout << "Sigma S : " << sigmaS << " Sigma R : " << sigma << endl;

    start = clock();
    CImg<double> fbImg = fb.applyFilter();
    temps = (double) (clock() - start)/(double) CLOCKS_PER_SEC;

    cout << "Temps d'éxécution : " << temps << "s" <<endl;
    cout << "<<<<<FILTRE BILATERAL FIN" << endl;

    return CImg<double> (fbImg.get_cut(0,255));
}
