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

#include "CImg.h"
using namespace cimg_library;

class FiltreBilateral
{
public:
  FiltreBilateral();
  FiltreBilateral(const FiltreBilateral& other);
  ~FiltreBilateral();
  FiltreBilateral(float fsigmaS, float fsigmaR, CImg<double> Cimg);
  
  
private:
  
  CImg<double> applyFilter();
  
  CImg<double> img;
  float fSigmaS;
  float fSigmaR;
  int width;
  int height;
};

#endif // FILTREBILATERAL_H
