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

CImg<double> filtre_bilateral(CImg<double> img, string nomImg, float fsigmaS, float fsigmaR){
	
	double temps;
	clock_t start;
	
	string nomFichier = "resultat.txt";
	ofstream fichier(nomFichier.c_str(), ios::app);
	
	// FILTRE BILATERAL
	FiltreBilateral fb(fsigmaS, fsigmaR, img);
	cout<< "Filtre bilatéral : début" << endl;
	cout<< "Nombre de canaux : " << img.spectrum() << endl;
	cout << "Sigma s : " << fsigmaS << endl;
	cout << "Sigma r : " << fsigmaR << endl;
	start = clock();
	CImg<double> fbImg = fb.applyFilterV3();
	temps = (double)(clock()-start)/(double) CLOCKS_PER_SEC;
	cout<< "Temps d'éxécution : " << temps  << " secondes" << endl;
	cout<< "Filtre bilatéral : done" << endl;
	
	string sigmaS =  to_string(fsigmaS);
	string sigmaR = to_string(fsigmaR);
	
	string nomImgSave = "filtrebilateral_sigmaS_" + sigmaS + "_sigmaR_" + sigmaR + "_" + nomImg ;   
	
	//   fbImg.save(nomImgSave.c_str());  
	CImg<double>(fbImg.get_cut(0,255)).save(nomImgSave.c_str());
	
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


CImg<double> filtre_bilateralV2(CImg<double> img, float fsigmaS, float fsigmaR){
	
	double temps;
	clock_t start;
	
	// FILTRE BILATERAL
	FiltreBilateral fb(fsigmaS, fsigmaR, img);
	cout<< "Filtre bilatéral : début" << endl;
	cout<< "Nombre de canaux : " << img.spectrum() << endl;
	cout << "Sigma s : " << fsigmaS << endl;
	cout << "Sigma r : " << fsigmaR << endl;
	start = clock();
	CImg<double> fbImg = fb.applyFilterV3();
	temps = (double)(clock()-start)/(double) CLOCKS_PER_SEC;
	cout<< "Temps d'éxécution : " << temps  << " secondes" << endl;
	cout<< "Filtre bilatéral : done" << endl;
	
	return CImg<double> (fbImg.get_cut(0, 255));
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

double comparaisonImageMax(const CImg<double> &imgFb, const CImg<double> &imgCimg){
	double max = 0.0;
	double diff= 0.0;
	
	cimg_forX(imgFb, x){
		cimg_forY(imgFb, y){
			diff = 0.0;
			cimg_forC(imgFb, c){
				diff += abs(imgFb._atXYZC(x,y, 0, c) - imgCimg._atXYZC(x,y, 0, c))/255.0;
			}
			diff = (diff*100) / imgFb.spectrum();
			if(diff >= max){
				max = diff;
			}
		}
	}
	return max;
}

double comparaisonEntreImage(const CImg<double> &imgFb, const CImg<double> &imgCimg){
	double diff=0.0;
	cimg_forX(imgFb, x){
		cimg_forY(imgFb, y){
			cimg_forC(imgFb, c){
				diff += abs(imgCimg._atXYZC(x,y,0, c) - imgFb._atXYZC(x,y,0,c))/255.0;
			}
		}
	}
	diff = (diff*100)/(imgFb.width() * imgFb.height() * imgFb.spectrum());
	return diff;
}


int main(int argc, char **argv) {
	
	string nomImg;
	string nomFichier = "resultatStat.txt";
	ofstream fichier(nomFichier.c_str(), ios::app);

	nomImg = "tulip.ppm";
	
	CImg<double> img(nomImg.c_str());
	CImg<double> noiseGauss(img);
	noiseGauss.noise(10);
	
	// Comparaison avec une image en NdG et une RGB entre l'implémentation naive du filtre et celle de CImg
	for(float fsigmaS = 4; fsigmaS <=64 ; fsigmaS*=2){
		for(float fsigmaR = 20; fsigmaR <= 60; fsigmaR+=10){
			CImg<double> fbImg = filtre_bilateralV2(noiseGauss, fsigmaS, fsigmaR);
			CImg<double> fbCImg = noiseGauss.get_blur_bilateral(noiseGauss, fsigmaS, fsigmaR);
			
			double diffPixel = comparaisonImageMax(fbImg, fbCImg);
			double diffImage = comparaisonEntreImage(fbImg, fbCImg);
			
			if(fichier){
				fichier << nomImg << "\t" << fsigmaS <<  "\t" << fsigmaR << "\t" << diffPixel << "\t" << diffImage << endl;
			}
			cout << "Valeur de diff max : " << diffPixel << endl;
			cout << "Valeur de diff : " << diffImage << endl;
		}
	}
	
	nomImg = "flower.ppm";
	
	CImg<double> img2(nomImg.c_str());
	CImg<double> noiseGauss2(img2);
	noiseGauss2.noise(10);
	
	for(float fsigmaS = 4; fsigmaS <=64 ; fsigmaS*=2){
		for(float fsigmaR = 20; fsigmaR <= 60; fsigmaR+=10){
			CImg<double> fbImg = filtre_bilateralV2(noiseGauss2, fsigmaS, fsigmaR);
			CImg<double> fbCImg = noiseGauss2.get_blur_bilateral(noiseGauss2, fsigmaS, fsigmaR);
			
			double diffPixel = comparaisonImageMax(fbImg, fbCImg);
			double diffImage = comparaisonEntreImage(fbImg, fbCImg);
			
			if(fichier){
				fichier << nomImg << "\t" << fsigmaS <<  "\t" << fsigmaR << "\t" << diffPixel << "\t" << diffImage << endl;
			}
			cout << "Valeur de diff max : " << diffPixel << endl;
			cout << "Valeur de diff : " << diffImage << endl;
		}
	}
	
	fichier.close();
	
	return 0;
}





