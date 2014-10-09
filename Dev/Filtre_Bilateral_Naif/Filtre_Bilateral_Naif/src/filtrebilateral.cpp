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


FiltreBilateral::FiltreBilateral()
{

}

FiltreBilateral::FiltreBilateral(const FiltreBilateral& other):img(other.img), fSigmaS(other.fSigmaS), fSigmaR(other.fSigmaR), width(other.width), height(other.height){}

FiltreBilateral::~FiltreBilateral(){}


FiltreBilateral::FiltreBilateral(float fsigmaS, float fsigmaR, const CImg<double> &input):img(input), fSigmaS(fsigmaS), fSigmaR(fsigmaR), width(input.width()), height(input.height()){}

CImg<double> FiltreBilateral::applyFilter()
{
  //CImg<double> res(img);
  //return res;
  // crée une image avec les mêmes caractéristiques que l'actuelle et rempli de 0
  CImg<double> bfImg(width, height, img.depth(), img.spectrum(),0);
  double wp = 0;
  int size = 21;
  int iXdebut=0, iYdebut=0;
  double gauss=0;
  
  
  // parcours de l'image sur la longeur (y) et la largeur(x)
  cimg_forXY(img, x, y){
    wp = 0;
   
    
    // parcours d'un carré de 21x21 autour du pixel courant
    // délimitation des variables de parcours en fonction de la position du pixel
    if(x<(size/2)-1){
      iXdebut= (size/2)-1 - x;
    }
    else{
      iXdebut = (size/2)-1;
    }
    if(y < (size/2)-1){
      iYdebut = (size/2)-1 - y;
    }
    else{
      iYdebut = (size/2)-1;
    }
    
    // parcours sur la largeur 
    for(int iX=iXdebut; iX<=(iXdebut + (size/2)-1) || iXdebut<img.width(); iX++){
      
      // parcours sur la longueur
      for(int iY=iYdebut; iY<=(iYdebut+(size/2)-1) || iYdebut<img.height(); iY++){
	  gauss = gaussianConvolution(distanceEuclidienne(x, y, iX, iY), fSigmaS) * gaussianConvolution(fabs(img._atXY(x, y) - img._atXY(iX, iY)), fSigmaR);
	
	  bfImg.set_linear_atXY(bfImg._atXY(x,y)+(gauss*img._atXY(iX,iY)), x, y);
	  wp += gauss;
	
      }
    }
    
      bfImg.set_linear_atXY(bfImg._atXY(x,y)/wp  ,x,y);
  }
  
   return bfImg;
}

/* calcul de la convolution gaussienne suivant sigma s de value
 * 
 */
double FiltreBilateral::gaussianConvolution(double value, float sigma){

  double gauss = (1/(2*M_PI* pow(sigma,2))) * exp((-pow(value,2))/(2*pow(sigma,2)));
  
  return gauss;
}


/*
 * calcul de la distance euclidienne entre 2 points P et Q
 */
double FiltreBilateral::distanceEuclidienne(int xP, int yP, int xQ, int yQ){

  double dist = sqrt(pow(xP - xQ, 2) + pow(yP - yQ, 2));
  return dist;
}

CImg<double> FiltreBilateral::moyennePixel(){

  
}









