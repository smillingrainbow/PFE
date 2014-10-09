#include <time.h>
#include <iostream>

#include "include/CImg.h"
using namespace cimg_library;
using namespace std;

int main(int argc, char** argv)
{
    double temps;
    clock_t start;
  
    // Initialisation des images
    
    CImg<unsigned char> imageGaussian("lena.jpg");
    CImg<unsigned char> visu(500,400,1,3,0);
    CImg<double> imageBilateral("lena.jpg");
    CImgDisplay Imgbilateral(imageBilateral, "Image originale");
    // initialisation des couleurs
    const unsigned char red[] = { 255,0,0 }, green[] = { 0,255,0 }, blue[] = { 0,0,255 };
    
    start = clock();
    
    // Application d'un filtre gaussien avec définition du sigma
    imageGaussian.blur(10);
    imageBilateral.blur_bilateral(imageBilateral, 1, 0.1);
    
    temps = (double)(clock()-start)/(double) CLOCKS_PER_SEC;
    cout << "Temps d'éxécution : " << temps << endl;
    
    imageBilateral.save_bmp("filtreBilateral");
    imageGaussian.save_bmp("filtreGaussian");
    
    // Création des fenêtres contenant les images
    CImgDisplay main_disp_Gaussian(imageGaussian,"Click a point");
    CImgDisplay main_disp_Bilateral(imageBilateral, "Filtre bilatéral");
    CImgDisplay draw_disp(visu,"Intensity profile");
    
    
    while (!main_disp_Gaussian.is_closed() && !draw_disp.is_closed() && !main_disp_Bilateral.is_closed()) {
      // Attente d'une action dans la fenêtre
      main_disp_Gaussian.wait();
      
      // Si un bouton est préssé
      if (main_disp_Gaussian.button() && main_disp_Gaussian.mouse_y()>=0) {
	// Indice de la ligne qui a été cliquée
	const int y = main_disp_Gaussian.mouse_y();
	visu.fill(0).draw_graph(imageGaussian.get_crop(0,y,0,0,imageGaussian.width()-1,y,0,0),red,1,1,0,255,0);
	visu.draw_graph(imageGaussian.get_crop(0,y,0,1,imageGaussian.width()-1,y,0,1),green,1,1,0,255,0);
	visu.draw_graph(imageGaussian.get_crop(0,y,0,2,imageGaussian.width()-1,y,0,2),blue,1,1,0,255,0).display(draw_disp);
      }
    }
    return 0;
  
}

