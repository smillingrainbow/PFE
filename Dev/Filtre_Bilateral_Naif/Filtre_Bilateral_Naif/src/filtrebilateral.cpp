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

FiltreBilateral::FiltreBilateral()
{

}

FiltreBilateral::FiltreBilateral(const FiltreBilateral& other)
{

}

FiltreBilateral::~FiltreBilateral()
{

}


FiltreBilateral::FiltreBilateral(float fsigmaS, float fsigmaR, CImg<double> Cimg)
{
  fSigmaS = fsigmaS;
  fSigmaR = fsigmaR;
  img = Cimg;
  width = img.width();
  height = img.height();
}

FiltreBilateral::applyFilter()
{
  // crée une image avec les mêmes caractéristiques que l'actuelle et rempli de 0
  CImg<double> *bfImg = new CImg<double>(width, height, img.depth(), img.spectrum(),0);
  
  // parcours de l'image sur la longeur (y) et la largeur(x)
  cimg_forXY(img, x, y){
    
    
  }
}


