#include <iostream>
#include <time.h>

#include "include/CImg.h"
#include "include/filtrebilateral.h"

using namespace cimg_library;
using namespace std;

int main(int argc, char **argv) {
  
  double temps;
  clock_t start;
  
  
  float fsigmaS = 0.1;
  float fsigmaR = 0.1;
   
//   cout<<"Veuillez saisir la valeur de sigma S (en pourcentage)."<< endl;
//   cin>> fsigmaS;
//   cout<<"Veuillez saisir la valeur de sigma R (en pourcentage)."<< endl;
//   cin>> fsigmaR;
  
  CImg<double> img("lena.jpg");
 
//   start = clock();
  
  FiltreBilateral fb(fsigmaS, fsigmaR, img);
  CImg<double> fbImg = fb.applyFilter();
//   temps = (double)(clock()-start)/(double) CLOCKS_PER_SEC;
//   
//   cout<< "Temps d'éxécution : " << temps << endl;
//   
  fbImg.save_bmp("filtrebilateral");
  
//   CImgDisplay main(img, "Normal");
//   CImgDisplay windows_fb(fbImg, "Filtre bilateral");
// 
//   while(!main.is_closed() && !windows_fb.is_closed()){
//     main.wait();
//   }
  
  return 0;
}


