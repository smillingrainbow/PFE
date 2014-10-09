#include <iostream>
#include <time.h>

#include "include/CImg.h"
#include "include/filtrebilateral.h"

using namespace cimg_library;
using namespace std;

int main(int argc, char **argv) {
  
  double temps;
  clock_t start;
  
  
  float fsigmaS;
  float fsigmaR;
   
  cout<<"Veuillez saisir la valeur de sigma S (en pourcentage)."<< endl;
  cin>> fsigmaS;
  cout<<"Veuillez saisir la valeur de sigma R (en pourcentage)."<< endl;
  cin>> fsigmaR;
  
  CImg<double> img("lena.jpg");
  
  FiltreBilateral *fb;
  fb = new FiltreBilateral(fsigmaS, fsigmaR, img);
  
  start = clock();
  
  temps = (double)(clock()-start)/(double) CLOCKS_PER_SEC;
  
  
  //FiltreBilateral fb(fsigmaS, fsigmaR);
//   FiltreBilateral fb();
  
  return 0;
}
