#PFE#
===================================================================


##Dossier Articles##
Contient les articles de références et le sujet du PFE

##Dossier Rapport##
Contient tous les différents rapports et présentation

##Dossier Dev##

 - Benchmark : Code pour les benchmarks (CImg, Paris et Durand, FB Naif) base d'images utilisées dans le dossier
	- Doc : Documentation du filtre et de l'interface (disponible en pdf et html)
	- Filtre_Bilateral_Naif : 
		- Filtre_Bilateral_Detail : 
			Permet la manipulation des détails (à modifier dans le code - variable "decrease" à mettre à true/false)
			Execution exemple : lena.jpg 10 30
			(NomDeLimage.extension sigmaS sigmaR)
		- Filter_Bilateral_Naif : 
			Permet d'appliquer le FB sur une image
			Execution exemple : lena.jpg 10 30
			(NomDeLimage.extension sigmaS sigmaR)
		- Filtre_Bilateral_Pyramide : 
			Permet de décomposer une image
			Execution exemple : lena.jpg 10 30
			(NomDeLimage.extension sigmaS sigmaR)
	- InterfaceQt : Interface avec la version naïve du FB
	- InterfaceQtFastFB : Interface avec la version CImg du FB
	- Doxyfile : pour générer la doc du dossier InterfaceQt
	- Test : 
		- ValidationFB : 
			Code pour valider l'implémentation naïve du FB (Comparaison avec CImg)

