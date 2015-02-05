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
	CImg<double> fbImg = fb.applyFilterV2();
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
	CImg<double> fbImg = fb.applyFilterV2();
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
	float fsigmaS, fsigmaR;
	
	if(argc == 4){
		nomImg = string(argv[1]);
		fsigmaS = atof(argv[2]);
		fsigmaR = atof(argv[3]);
		
		
	}
	else{
		cout<<"Veuillez saisir le nom de l'image avec son extension (ex: lena.jpg)" << endl;
		cin>> nomImg; 
		
		cout<<"Veuillez saisir la valeur de sigma S."<< endl;
		cin>> fsigmaS;
		
		cout<<"Veuillez saisir la valeur de sigma R (en pourcentage)."<< endl;
		cin>> fsigmaR;  
	}
	
	CImg<double> img(nomImg.c_str());
	CImg<double> noiseGauss(img);
	noiseGauss.noise(10);
	
	CImg<double> fbImg = filtre_bilateral(noiseGauss, nomImg, fsigmaS, fsigmaR);
	
// 	CImg<double> fbImg = filtre_bilateral(img, nomImg, fsigmaS, fsigmaR);
// 	CImg<double> fbImg = filtre_bilateralV2(img, fsigmaS, fsigmaR);
	
	CImg<double> imgTest(noiseGauss);
// 	CImg<double> imgTest(img);
	imgTest = imgTest.blur_bilateral(imgTest, fsigmaS, fsigmaR);

	
	CImgDisplay windows_fb(fbImg, "Image filtre bilateral");
	CImgDisplay windows_fbTest(imgTest, "Image filtre bilateral CImg");



	CImgDisplay main(img, "Normal");
	
	cout << "Valeur de diff max : " << comparaisonImageMax(fbImg, imgTest) << endl;
	cout << "Valeur de diff : " << comparaisonEntreImage(fbImg, imgTest) << endl;
	
	cout << "PSNR : " << noiseGauss.PSNR(fbImg) << endl;
	 
	while(!main.is_closed()){
		main.wait();
	}
	return 0;
}





