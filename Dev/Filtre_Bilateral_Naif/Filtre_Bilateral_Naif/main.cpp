#include <iostream>
#include <time.h>
#include <fstream>
#include <string>
#include <sstream>

#include "include/CImg.h"
#include "include/filtrebilateral.h"

using namespace cimg_library;
using namespace std;

template <typename T>
inline std::string to_string (const T& t)
{
  std::stringstream ss;
  ss << t;
  return ss.str();
}

CImg<double> filtre_bilateral(CImg<double> img, string nomImg){

  double temps;
  clock_t start;
  float fsigmaS, fsigmaR;
 
  cout<<"Veuillez saisir la valeur de sigma S (en pourcentage)."<< endl;
  cin>> fsigmaS;
  cout<<"Veuillez saisir la valeur de sigma R (en pourcentage)."<< endl;
  cin>> fsigmaR;
  
  fsigmaS = fsigmaS/100;
  fsigmaR = fsigmaR/100;
 
  string nomFichier = "resultat.txt";
  ofstream fichier(nomFichier.c_str(), ios::app);
   
  // FILTRE BILATERAL
  FiltreBilateral fb(fsigmaS, fsigmaR, img);
  cout<< "Filtre bilatéral : début" << endl;
  start = clock();
  CImg<double> fbImg = fb.applyFilter();
  temps = (double)(clock()-start)/(double) CLOCKS_PER_SEC;
  cout<< "Temps d'éxécution : " << temps  << " secondes" << endl;
  cout<< "Filtre bilatéral : done" << endl;
 
  string sigmaS =  to_string(fsigmaS);
  string sigmaR = to_string(fsigmaR);
  
  string nomImgSave = "filtrebilateral_sigmaS_" + sigmaS + "_sigmaR_" + sigmaR + "_" + nomImg ;   
  
  fbImg.save(nomImgSave.c_str());  
  
  
  if(fichier){
      fichier << "Nom de l'image : " << nomImg << endl; 
      fichier << "Paramètre : " << endl;
      fichier << "\t" <<  "Sigma S : " << fsigmaS << endl;
      fichier << "\t" << "Sigma R : " << fsigmaR << endl;
      fichier << "Tenmps d'éxécution : " << temps << "secondes" << endl;
      fichier << "Nom de l'image avec le filtre : " <<  nomImgSave << endl; 
      fichier << "----------------------------" <<endl;
      
      fichier.close();
  }
  return fbImg;
}

CImg<double> filtre_moyen(CImg<double> img){
  double temps;
  clock_t start;
  
  // FILTRE MOYEN
  FiltreBilateral moy(img);
  cout<< "Filtre moyen : début" << endl;
  start = clock();
  CImg<double> moyImg = moy.moyennePixel();
  temps = (double)(clock()-start)/(double) CLOCKS_PER_SEC;
  cout<< "Temps d'éxécution : " << temps  << " secondes" << endl;
  cout<< "Filtre moyen : done" << endl;
  
  return moyImg;
}

CImg<double> ajout_bruit_gaussien(CImg<double> img){
  double temps;
  clock_t start;
 
  float fsigma;
  cout<<"Veuillez saisir la valeur de sigma (en pourcentage)."<< endl;
  cin>> fsigma;
  
  fsigma = fsigma/100;
  
  // FILTRE MOYEN
  FiltreBilateral bGauss(img);
  cout<< "Ajout bruit gaussien : début" << endl;
  start = clock();
  CImg<double> bGaussImg = bGauss.bruitGaussien(fsigma);
  temps = (double)(clock()-start)/(double) CLOCKS_PER_SEC;
  cout<< "Temps d'éxécution : " << temps  << " secondes" << endl;
  cout<< "Ajout bruit gaussien : done" << endl;
  
  return bGaussImg;
  
}

int main(int argc, char **argv) {
  
  string nomImg;
   
  cout<<"Veuillez saisir le nom de l'image avec son extension (ex: lena.jpg)" << endl;
  cin>> nomImg; 
  
  CImg<double> img(nomImg.c_str());
  
//   CImg<double> moyImg = filtre_moyen(img);
//   CImgDisplay windows_moy(moyImg, "Image moyenne");
  
    CImg<double> bGaussImg = ajout_bruit_gaussien(img);
    CImgDisplay windows_bGauss(bGaussImg, "Bruit gaussien");
  
//   CImg<double> fbImg = filtre_bilateral(img, nomImg);
//   CImgDisplay windows_fb(fbImg, "Image filtre bilateral");
  
  CImgDisplay main(img, "Normal");

  while(!main.is_closed()){
    main.wait();
  }
  return 0;
}




