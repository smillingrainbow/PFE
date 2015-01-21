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

#ifndef FILTREBILATERAL_H
#define FILTREBILATERAL_H

#define _USE_MATH_DEFINES
#include "CImg.h"
#include <cmath>
#include <iostream>


class FiltreBilateral
{
public:
  FiltreBilateral();
  FiltreBilateral(const FiltreBilateral& other);
  ~FiltreBilateral();
  FiltreBilateral(float fsigmaS, float fsigmaR, const cimg_library::CImg<double> &input);
  FiltreBilateral(const cimg_library::CImg<double> &input);
  cimg_library::CImg<double> applyFilter();
  cimg_library::CImg<double> applyFilterV2();
  cimg_library::CImg<double> moyennePixel();
  
  cimg_library::CImg<double> bruitGaussien(float sigma);
  
private:
  
  double loiGaussienne(double value, float sigma);
  double distanceEuclidienne(int xP, int yP, int xQ, int yQ);
  double distanceScalaire(int xP, int yP, int xQ, int yQ);
  double transformationBoxMuller(float sigma);
  
  cimg_library::CImg<double> img;
  float fSigmaS;
  float fSigmaR;
  int width;
  int height;
};

#endif // FILTREBILATERAL_H
