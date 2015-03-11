#ifndef FILTERBILATERAL_H
#define FILTERBILATERAL_H

# define _USE_MATH_DEFINES
# include "CImg.h"
# include <cmath>
# include <iostream>

/**
 * @brief Classe permettant de manipuler des images avec un filtre bilateral
 * Cette classe permet d'appliquer un filtre bilateral sur une image en niveau de gris ou RGB
 * @author Natacha Marlio-Marette
 * @version 1.0
 * @date 11/03/2015
 */
class FilterBilateral
{
    public:
        /**
         * @brief Constructeur par défaut
         */
        FilterBilateral(){}
        /**
         * @brief Constructeur par recopie
         * @param other Objet FilterBilateral a recopié
         */
        FilterBilateral(const FilterBilateral& other):img(other.img), fSigmaS(other.fSigmaS), fSigmaR(other.fSigmaR), width(other.width), height(other.height){}
        /**
         * @brief Constructeur
         * @param fsigmaS Valeur de sigma S
         * @param fsigmaR Valeur de sigma R
         * @param input Image initiale
         */
        FilterBilateral(float fsigmaS, float fsigmaR, const cimg_library::CImg<double> &input):img(input), fSigmaS(fsigmaS), fSigmaR(fsigmaR), width(input.width()), height(input.height()){}
        /**
         * @brief Constructeur
         * @param input Image initiale
         */
        FilterBilateral(const cimg_library::CImg<double> &input): img(input),fSigmaS(0), fSigmaR(0),width(input.width()), height(input.height()){}
        /**
          * @brief Destructeur
          */
        ~FilterBilateral(){}

        /**
         * @brief Applique le filtre bilateral à l'image initiale
         *  Appelle applyFilterNdG() si l'image est en niveau de gris sinon applyFilterRGB()
         * @return Retourne une nouvelle image instanciée sur laquelle le filtre bilatéral a été appliquée
         */
        cimg_library::CImg<double> applyFilter();
        /**
         * @brief Applique le filtre bilateral à une image en niveau de gris
         * @return Retourne une nouvelle image instanciée
         */
        cimg_library::CImg<double> applyFilterNdG();
        /**
         * @brief Applique le filtre bilateral à une image RGB
         * Le filtre bilateral est appliquée à la luminance
         * @return Retourne une nouvelle image instanciée
         */
        cimg_library::CImg<double> applyFilterRGB();

        /**
         * @brief Getter pour sigma S
         * @return Retourne sigma S
         */
        float get_fSigmaS() {return fSigmaS;}
        /**
         * @brief Getter pour sigma R
         * @return Retourne sigma R
         */
        float get_fSigmaR() {return fSigmaR;}
        /**
         * @brief Getter de l'image initiale
         * @return Retourne l'iamge initiale
         */
        cimg_library::CImg<double> get_img() {return img;}

        /**
         * @brief Change la valeur de sigma S
         * @param sigmaS Valeur de sigma S
         */
        void set_fSigmaS(float sigmaS) {fSigmaS = sigmaS;}
        /**
         * @brief Change la valeur de sigma R
         * @param sigmaS Valeur de sigma R
         */
        void set_fSigmaR(float sigmaR) {fSigmaR = sigmaR;}
        /**
         * @brief Change l'image initiale
         * @param newImg Nouvelle image
         */
        void set_img(cimg_library::CImg<double>& newImg) {img = newImg;}

    private:
        /**
         * @brief calcul d'une gaussienne
         * Calcul d'une gaussienne
         * @param value Paramètre de la gaussienne
         * @param sigma Valeur du sigma de la gaussienne
         * @return Résultat du calcul de la gaussienne
         */
        double loiGaussienne(double value, float sigma);
        /**
         * @brief Calcul de la distance euclidienne entre deux points
         *  Calcul de la distance euclidienne entre deux points
         * @param xP Coordonnée x du premier point
         * @param yP Coordonnée y du premier point
         * @param xQ Coordonnée x du second point
         * @param yQ Coordonnée y du second point
         * @return Résultat de la distance euclidienne entre les deux points
         */
        double distanceEuclidienne(int xP, int yP, int xQ, int yQ);

        /**
         * @brief Image initiale
         */
        cimg_library::CImg<double> img;
        /**
         * @brief Valeur de sigma S
         */
        float fSigmaS;
        /**
         * @brief Valeur de sigma R
         */
        float fSigmaR;
        /**
         * @brief Nombre de colonne de l'image initiale
         */
        int width;
        /**
         * @brief Nombre de ligne de l'image initiale
         */
        int height;
};

#endif // FILTERBILATERAL_H
