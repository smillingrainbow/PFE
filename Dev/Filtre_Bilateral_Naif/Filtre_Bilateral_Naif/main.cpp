#include <iostream>
#include <time.h>
#include <fstream>
#include <string>

#include "include/CImg.h"
#include "include/filtrebilateral.h"

using namespace cimg_library;
using namespace std;

// template <typename T>
// inline std::string to_string (const T& t)
// {
//   std::stringstream ss;
//   ss << t;
//   return ss.str();
// }


int main(int argc, char **argv) {
  
  double temps;
  clock_t start;
  
  
  float fsigmaS = 0.1;
  float fsigmaR = 0.1;
  
  string nomImg;
   
//   cout<<"Veuillez saisir la valeur de sigma S (en pourcentage)."<< endl;
//   cin>> fsigmaS;
//   cout<<"Veuillez saisir la valeur de sigma R (en pourcentage)."<< endl;
//   cin>> fsigmaR;
  
  cout<<"Veuillez saisir le nom de l'image avec son extension (ex: lena.jpg)" << endl;
  cin>> nomImg; 
  
  CImg<double> img(nomImg.c_str());
 
  string nomFichier = "resultat.txt";
  ofstream fichier(nomFichier.c_str(), ios::ate);
 
  FiltreBilateral fb(fsigmaS, fsigmaR, img);
  
  
  // FILTRE MOYEN
  cout<< "Filtre moyen : début" << endl;
  start = clock();
  CImg<double> moyImg = fb.moyennePixel();
  temps = (double)(clock()-start)/(double) CLOCKS_PER_SEC;
  cout<< "Temps d'éxécution : " << temps  << " secondes" << endl;
  cout<< "Filtre moyen : done" << endl;

  
  // FILTRE BILATERAL
  cout<< "Filtre bilatéral : début" << endl;
  start = clock();
  CImg<double> fbImg = fb.applyFilter();
  temps = (double)(clock()-start)/(double) CLOCKS_PER_SEC;
  cout<< "Temps d'éxécution : " << temps  << " secondes" << endl;
  cout<< "Filtre bilatéral : done" << endl;
 
  //   string sigmaS =  to_string(fsigmaS);
//   string sigmaR = to_string(fsigmaR);
  
//   nomImgSave = "filtrebilateral_sigmaS_" + sigmaS + "_sigmaR_" + sigmaR + "_" + nomImg ;   
//   fbImg.save_bmp("filtrebilateral");
// 	fbImg.save(nomImgSave.c_str());  
  
  
  //   if(fichier){
//       fichier << "Nom de l'image : " << nomImg << endl; 
//       fichier << "Paramètre : " << endl;
//       fichier << "\t" <<  "Sigma S : " << fsigmaS << endl;
//       fichier << "\t" << "Sigma R : " << fsigmaR << endl;
//       fichier << "Tenmps d'éxécution : " << temps << "secondes" << endl;
//       fichier << "Nom de l'image avec le filtre : " <<  nomImgSave << endl; 
//       fichier << "----------------------------" <<endl;
//       
//       fichier.close();
//   }
  
  
  
  CImgDisplay main(img, "Normal");
  CImgDisplay windows_moy(moyImg, "Image moyenne");
  CImgDisplay windows_fb(fbImg, "Image filtre bilateral");

  while(!windows_fb.is_closed() && !main.is_closed() && !windows_moy.is_closed()){
    windows_fb.wait();
    main.wait();
    windows_moy.wait();
  }
  return 0;
}
