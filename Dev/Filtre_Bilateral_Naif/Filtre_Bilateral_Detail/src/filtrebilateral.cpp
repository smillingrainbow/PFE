/*
 * Copyright 2014 <copyright holder> <email>
 * 
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 *     http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 * 
 */

#include "../include/filtrebilateral.h"
using namespace cimg_library;
using namespace std;


FiltreBilateral::FiltreBilateral()
{
	
}

FiltreBilateral::FiltreBilateral(const FiltreBilateral& other):img(other.img), fSigmaS(other.fSigmaS), fSigmaR(other.fSigmaR), width(other.width), height(other.height){}

FiltreBilateral::~FiltreBilateral(){}


FiltreBilateral::FiltreBilateral(float fsigmaS, float fsigmaR, const CImg<double> &input):img(input), fSigmaS(fsigmaS), fSigmaR(fsigmaR), width(input.width()), height(input.height()){}

FiltreBilateral::FiltreBilateral(const CImg<double> &input): img(input),fSigmaS(0), fSigmaR(0),width(input.width()), height(input.height()){}


CImg<double> FiltreBilateral::applyFilter()
{
	//CImg<double> res(img);
	//return res;
	// crée une image avec les mêmes caractéristiques que l'actuelle et remplie de 0
	CImg<double> bfImg(width, height, img.depth(), img.spectrum(),0);
	double wp=0;
	int size = 21;
	int iXdebut=0, iYdebut=0, iXfin=0, iYfin=0;
	double gauss=0;
	double distEuclidienne=0;
	double distScalaire=0;
	double *value = new double[img.spectrum()];
	double valueNormal=0.0;
	
	
	// parcours de l'image sur la longeur (y) et la largeur(x)
	cimg_forX(img, x){                                                                                                                         
		cimg_forY(img, y){
			wp=0;
			cimg_forC(img, c){
				value[c] = 0.0;
			}
			// parcours d'un carré de 21x21 autour du pixel courant
			// délimitation des variables de parcours en fonction de la position du pixel
			if(x<(size/2)-1){
				iXdebut= 0;
			}
			else{
				iXdebut = x - (size/2);
			}
			if(y < (size/2)-1){
				iYdebut = 0;
			}
			else{
				iYdebut =  y - (size/2);
			}
			
			if(x+(size/2) > width){
				iXfin = width-1;
			}
			else{
				iXfin = x + (size/2);
			}
			
			if(y+(size/2) > height){
				iYfin = height-1;
			}
			else{
				iYfin = y + (size/2);
			}
			
			// parcours sur la largeur 
			for(int iX=iXdebut; iX<=iXfin; iX++){
				
				// parcours sur la longueur
				for(int iY=iYdebut; iY<=iYfin; iY++){
					
					distEuclidienne = distanceEuclidienne(x, y, iX, iY);
					distScalaire = distanceScalaire(x, y, iX, iY);
					gauss = loiGaussienne(distEuclidienne, fSigmaS) * 					loiGaussienne(distScalaire, fSigmaR); 
					
					cimg_forC(img, c){
						value[c] += gauss*img._atXYZC(iX,iY, 0, c);
						bfImg.set_linear_atXYZ(value[c], x, y, 0, c, false);
						
						wp += gauss;
					}
					
				}
			}
			cimg_forC(img, c){
				valueNormal = bfImg._atXYZC(x,y, 0 , c)/wp;
				bfImg.set_linear_atXYZ(valueNormal, x,y, 0, c, false);
			}
		}
	}
	
	return bfImg;
}

/* 
 * calcul de la convolution gaussienne suivant sigma s de value
 */
double FiltreBilateral::loiGaussienne(double value, float sigma){
	
	double gauss = (1/(2*M_PI* pow(sigma,2))) * exp(-(pow(value,2))/(2*pow(sigma,2)));
	
	return gauss;
}


/*
 * calcul de la distance euclidienne entre 2 points P et Q
 */
double FiltreBilateral::distanceEuclidienne(int xP, int yP, int xQ, int yQ){
	
	double dist = pow(xP - xQ, 2) + pow(yP - yQ, 2);
	dist = sqrt(dist);
	return dist;
}

double FiltreBilateral::distanceScalaire(int xP, int yP, int xQ, int yQ)
{
	double dist = 0;
	for(int iColor=0; iColor<= img.spectrum(); iColor++){
		dist += pow(img._atXYZC(xP, yP, 0, iColor) -img._atXYZC(xQ, yQ, 0, iColor),2 );
	}
	dist = sqrt(dist);
	return dist;
}


CImg<double> FiltreBilateral::moyennePixel(){
	
	CImg<double> res(width, height, img.depth(), img.spectrum(),0);
	double moy;
	int compt;
	cimg_forX(res, x){ // parcours largeur
		cimg_forY(res, y){ // parcours longueur
			compt=0;
			moy = 0;
			if(x!=0){ // bordure supérieure
				compt++;
				moy += img._atXY(x, y-1);
			}
			if(x!= res.height()-1){ // bordure inférieur
				compt++;
				moy += img._atXY(x, y+1);
				
			}
			if(y!=0){ // bordure gauche
				moy += img._atXY(x-1, y);
				compt++;
			}
			if(y!= img.width()-1){ // bordure droite
				moy += img._atXY(x+1, y);
				compt++;
			}
			moy = moy/compt;
			res.set_linear_atXY(moy, x, y);
		}
	}
	
	return res;
}

CImg< double > FiltreBilateral::bruitGaussien(float sigma){
	CImg<double> res(width, height, img.depth(), img.spectrum(), 0);
	double boxmuller = 0;
	double value = 0;
	double gauss = 0;
	const double min=img.min(), max= img.max();
	
	cimg_forX(res, x){ // parcours largeur
		cimg_forY(res, y){ // parcours longueur
			value = img._atXY(x, y);
			boxmuller = transformationBoxMuller(sigma);
			gauss = loiGaussienne(boxmuller, sigma);
			
			value = value + gauss;
			
			if(value>max){
				value = max;
			}
			if(value < min){
				value = min;
			}
			
			res.set_linear_atXY(value, x, y);
		}
	}
	
	
	return res;
}

double FiltreBilateral::transformationBoxMuller(float sigma){
	double res=0;
	
	static bool haveSpare = false;
	static double rand1, rand2;
	
	if(haveSpare)
	{
		haveSpare = false;
		res = sqrt(sigma * rand1) * sin(rand2);
	}
	else{
		haveSpare = true;
		
		rand1 = rand() / ((double) RAND_MAX);
		if(rand1 < 1e-100) rand1 = 1e-100;
		rand1 = -2 * log(rand1);
		rand2 = (rand() / ((double) RAND_MAX)) * 2 * M_PI;
		
		res = sqrt(sigma * rand1) * cos(rand2);
	}
	
	return res;
}


CImg< double > FiltreBilateral::applyFilterNdG()
{
	CImg<double> bfImg(width, height, img.depth(), img.spectrum(),0);
	double wp=0;
	int size = 21;
	int iXdebut=0, iYdebut=0, iXfin=0, iYfin=0;
	double gauss=0;
	double distEuclidienne=0;
	double value;
	double valueNormal=0.0;
	
	cout<< "Image en niveau de gris " << endl;
	
	// parcours de l'image sur la longeur (y) et la largeur(x)
	cimg_forX(img, x){                                                                                                                         
		cimg_forY(img, y){
			wp=0;
			value = 0.0;
			
			// parcours d'un carré de 21x21 autour du pixel courant
			// délimitation des variables de parcours en fonction de la position du pixel
			if(x<(size/2)-1){
				iXdebut= 0;
			}
			else{
				iXdebut = x - (size/2);
			}
			if(y < (size/2)-1){
				iYdebut = 0;
			}
			else{
				iYdebut =  y - (size/2);
			}
			
			if(x+(size/2) > width){
				iXfin = width-1;
			}
			else{
				iXfin = x + (size/2);
			}
			
			if(y+(size/2) > height){
				iYfin = height-1;
			}
			else{
				iYfin = y + (size/2);
			}
			
			// parcours sur la largeur 
			for(int iX=iXdebut; iX<=iXfin; iX++){
				
				// parcours sur la longueur
				for(int iY=iYdebut; iY<=iYfin; iY++){
					
					distEuclidienne = distanceEuclidienne(x, y, iX, iY);
					gauss = loiGaussienne(distEuclidienne, fSigmaS) * 						loiGaussienne(std::abs(img._atXYZC(x,y,0,0) - 						img._atXYZC(iX,iY,0,0)), fSigmaR); 
					
					value += gauss*img._atXYZC(iX,iY, 0, 0);
					bfImg.set_linear_atXYZ(value, x, y, 0, 0, false);
					
					wp += gauss;
					
				}
			}
			valueNormal = bfImg._atXYZC(x,y, 0 , 0)/wp;
			bfImg.set_linear_atXYZ(valueNormal, x,y, 0, 0, false);
		}
	}
	return bfImg;
	
}

CImg< double > FiltreBilateral::applyFilterRGB()
{
	CImg<double> bfImg(width, height, img.depth(), img.spectrum(),0);
	// conversion de l'image RGB vers YCbCr
	CImg<double> imgY = img.get_RGBtoYCbCr();
	bfImg.RGBtoYCbCr();
	double wp=0;
	int size = 21;
	int iXdebut=0, iYdebut=0, iXfin=0, iYfin=0;
	double gauss=0;
	double distEuclidienne=0;
	double value = 0.0;
	double valueNormal=0.0;
	
	cout<< "Image couleur --> passage par la luminance" << endl;
	
	// parcours de l'image sur la longeur (y) et la largeur(x)
	cimg_forX(imgY, x){                                                                                                                         
		cimg_forY(imgY, y){
			wp=0;
			value = 0.0;
			
			// copie de Cb et Cr de l'image 
			bfImg.set_linear_atXYZ(imgY._atXYZC(x,y,0,1), x, y, 0, 0, false);
			bfImg.set_linear_atXYZ(imgY._atXYZC(x,y,0,2), x, y, 0, 0, false);
			
			// parcours d'un carré de 21x21 autour du pixel courant
			// délimitation des variables de parcours en fonction de la position du pixel
			if(x<(size/2)-1){
				iXdebut= 0;
			}
			else{
				iXdebut = x - (size/2);
			}
			if(y < (size/2)-1){
				iYdebut = 0;
			}
			else{
				iYdebut =  y - (size/2);
			}
			
			if(x+(size/2) > width){
				iXfin = width-1;
			}
			else{
				iXfin = x + (size/2);
			}
			
			if(y+(size/2) > height){
				iYfin = height-1;
			}
			else{
				iYfin = y + (size/2);
			}
			
			// parcours sur la largeur 
			for(int iX=iXdebut; iX<=iXfin; iX++){
				
				// parcours sur la longueur
				for(int iY=iYdebut; iY<=iYfin; iY++){
					
					distEuclidienne = distanceEuclidienne(x, y, iX, iY);
					gauss = loiGaussienne(distEuclidienne, fSigmaS) * 					loiGaussienne(std::abs(imgY._atXYZC(x,y,0,0) - 								imgY._atXYZC(iX,iY,0,0)), fSigmaR); 
					
					value += gauss*imgY._atXYZC(iX,iY, 0, 0);
					bfImg.set_linear_atXYZ(value, x, y, 0, 0, false);
					
					wp += gauss;
				}
			}
			valueNormal = bfImg._atXYZC(x,y, 0 , 0)/wp;
			bfImg.set_linear_atXYZ(valueNormal, x,y, 0, 0, false);
		}
	}
	bfImg.YCbCrtoRGB();
	return bfImg;
}


CImg< double > FiltreBilateral::applyFilterV3(){
	CImg<double> bfImg;

	// image en niveau de gris
	if(img.spectrum() == 1){
		bfImg = applyFilterNdG();
	}
	// image RGB
	else{
		bfImg = applyFilterRGB();
	}
	
	return bfImg;
}








