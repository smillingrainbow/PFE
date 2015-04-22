/*! \file
  \verbatim
  
    Copyright (c) 2006, Sylvain Paris and Frédo Durand

    Permission is hereby granted, free of charge, to any person
    obtaining a copy of this software and associated documentation
    files (the "Software"), to deal in the Software without
    restriction, including without limitation the rights to use, copy,
    modify, merge, publish, distribute, sublicense, and/or sell copies
    of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be
    included in all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
    EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
    MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
    NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
    HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
    WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
    DEALINGS IN THE SOFTWARE.

  \endverbatim
*/


#include <cmath>
#include <time.h>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#define CHRONO
#include "include/geom.h"
#include "include/fast_color_bf.h"
#include "include/CImg.h"
#include "include/filterbilateral.h"

using namespace std; 
using namespace cimg_library;

template <typename T>
inline std::string to_string (const T& t)
{
	std::stringstream ss;
	ss << t;
	return ss.str();
}

typedef Array_2D<Geometry::Vec3<double> > image_type;


void cimg_BilateralFilter(string nomImg, double sigma_s, double sigma_r){

	CImg<> img(nomImg.c_str());

	img = img.blur_bilateral(img, sigma_s, sigma_r);

	string saveImg = "resultat/cimg_FB_"+to_string(sigma_s)+"_"+ to_string(sigma_r)+"_" + nomImg;
	img.save(saveImg.c_str());
}
 
void parisDurand_BilateralFilter(string nomImg, double sigma_s, double sigma_r){
	
	cout << "Image : " << nomImg << endl;
	ifstream ppm_in(nomImg.c_str(),ios::binary);

	string magic_number("  ");
	
	ppm_in.get(magic_number[0]);
	ppm_in.get(magic_number[1]);

	if (magic_number != std::string("P6")){
		cerr<<"error: unrecognized file format\n"<<nomImg<<" is not a PPM file.\n"<<endl;
		exit(2);   
	}

	unsigned width,height,bpp;
	
	ppm_in>>width>>height>>bpp;

	if (bpp != 255){
		cerr<<"error: unsupported maximum value ("<<bpp<<")\n"<<"It must be 255."<<endl;
		exit(3);   
	}

	image_type image(width,height);
	
	char ch;
	ppm_in.get(ch); // Trailing white space.

	char r,g,b;
	
	for(unsigned y=0;y<height;y++){
		for(unsigned x=0;x<width;x++){

		ppm_in.get(r);
		ppm_in.get(g);
		ppm_in.get(b);

		const unsigned char R = static_cast<unsigned char>(r);
		const unsigned char G = static_cast<unsigned char>(g);
		const unsigned char B = static_cast<unsigned char>(b);
						
		image(x,y)[0] = static_cast<double>(R) / 255.0;
		image(x,y)[1] = static_cast<double>(G) / 255.0;
		image(x,y)[2] = static_cast<double>(B) / 255.0;
		}
	}
	
	ppm_in.close();

	cout<<"Done"<<endl;

	// ##############################################################
	
	cout<<"Filter the image... "<<endl;

	image_type filtered_image(width,height);
	
	Image_filter::fast_color_BF(image,
					sigma_s,sigma_r,
					&filtered_image);
	
	cout<<"Filtering done"<<endl;

	// ##############################################################
	
	string saveImg = "resultat/DS_"+to_string(sigma_s)+"_"+ to_string(sigma_r)+"_"+nomImg;
	
	cout<<"Write the output image '"<<saveImg<<"'... "<<flush;

	ofstream ppm_out(saveImg.c_str(),ios::binary);

	ppm_out<<"P6";
	ppm_out<<' ';
	ppm_out<<width;
	ppm_out<<' ';
	ppm_out<<height;
	ppm_out<<' ';
	ppm_out<<"255";
	ppm_out<<'\n';
	
	for(unsigned y=0;y<height;y++){    
		for(unsigned x=0;x<width;x++){

		const double R = filtered_image(x,y)[0] * 255.0;
		const double G = filtered_image(x,y)[1] * 255.0;
		const double B = filtered_image(x,y)[2] * 255.0;
		
		const char r = static_cast<unsigned char>(Math_tools::clamp(0.0,255.0,R));
		const char g = static_cast<unsigned char>(Math_tools::clamp(0.0,255.0,G));
		const char b = static_cast<unsigned char>(Math_tools::clamp(0.0,255.0,B));
		
		ppm_out<<r<<g<<b;
		}
	}
	
	ppm_out.flush();
	ppm_out.close();
	
	cout<<"Done"<<endl;
	
}

void naif_BilateralFilter(string nomImg, double sigma_s, double sigma_r){
	CImg<double> img(nomImg.c_str());
    FilterBilateral fb(sigma_s, sigma_r, img);
    CImg<double> fbImg = fb.applyFilter();
	
	string saveImg = "resultat/naif_FB_"+to_string(sigma_s)+"_"+ to_string(sigma_r)+"_" + nomImg;
	CImg<double> (fbImg.get_cut(0,255)).save(saveImg.c_str());
}


int main(int argc,char** argv){
	string nomFichierTab[] = {"dragon.ppm", "greekdome.ppm", "housecorner.ppm", "polin.ppm", "swamp.ppm", "tulip.ppm"};
	vector<string> nomFichier (nomFichierTab, nomFichierTab + sizeof(nomFichierTab)/sizeof(string));
	
	
	
	double tempsCimg, tempsDP, tempsNaif;
	clock_t start;
	string fichierResultat = "resultatFBNaif.txt"; 

	for(double sigmaS=16.0; sigmaS<100; sigmaS+=10.0){
		for (double sigmaR = 0.1; sigmaR<1.0; sigmaR+=0.1){
			for(int i=0; i<nomFichier.size(); i++){
				cout << "Image : " << nomFichier[i] << endl;
				cout<<"sigma_s    = "<<sigmaS<<"\n";
				cout<<"sigma_r    = "<<sigmaR<<"\n";
				
// 				cout << ">>>>>>>>>>>>>>>DEBUT CIMG " << endl;
// 				start = clock();
// 				cimg_BilateralFilter(nomFichier[i], sigmaS, sigmaR);
// 				tempsCimg = (double)(clock()-start)/(double) CLOCKS_PER_SEC;
// 				cout << "Temps d'exécution "<< tempsCimg << " secondes" << endl;
// 				cout << ">>>>>>>>>>>>>>FIN " <<endl;
// 				
// 				cout << ">>>>>>>>>>>>>>>>>>DEBUT PARIS DURAND" << endl;
// 				start = clock();
// 				parisDurand_BilateralFilter(nomFichier[i], sigmaS, sigmaR);
// 				tempsDP = (double)(clock()-start)/(double) CLOCKS_PER_SEC;
// 				
// 				cout << "Temps d'exécution "<< tempsDP << " secondes" << endl;
// 				cout << ">>>>>>>>>>>>>>FIN " <<endl;
				
				
				cout << ">>>>>>>>>>>>>>>>>>DEBUT BILATERAL FILTER NAIF" << endl;
				start = clock();
				naif_BilateralFilter(nomFichier[i], sigmaS, sigmaR);
				tempsNaif = (double)(clock()-start)/(double) CLOCKS_PER_SEC;
				
				cout << "Temps d'exécution "<< tempsNaif << " secondes" << endl;
				cout << ">>>>>>>>>>>>>>FIN " <<endl;
				
				ofstream fichier(fichierResultat.c_str(), ios::app);
				if(fichier){
// 					fichier<< nomFichier[i] << "\t" << sigmaS << "\t" << sigmaR << "\t" << tempsCimg << "\t" << tempsDP  << "\t" << tempsNaif << endl;
					fichier<< nomFichier[i] << "\t" << sigmaS << "\t" << sigmaR << "\t" << tempsNaif << endl;
					fichier.close();
				}
			}
		}
	}
	
	
	
}
