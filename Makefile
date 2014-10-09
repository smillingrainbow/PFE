

all:
	filtre_bilateral
	test

filtre_bilateral:
	cd Dev/Filtre_Bilateral_Naif/Filtre_Bilateral_Naif/ 
	make mproper
	make

test:
	cd Dev/Test/CImg/Test_Bilateral/ 
	make mproper
	make 
