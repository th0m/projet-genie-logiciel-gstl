#!/bin/bash

#Script d'installation des dependances pour le projet génie logiciel INFO3 (pour distribution basée sur debian)
#GSTL

#Installation des composants SDL de developpement
sudo apt-get install libsdl1.2-dev libsdl-image1.2-dev subversion

mkdir -p /tmp/ProjetGenieLogiciel_GSTL
cd /tmp/ProjetGenieLogiciel_GSTL
svn checkout http://projet-genie-logiciel-gstl.googlecode.com/svn/trunk/ projet-genie-logiciel-gstl-read-only
g++ *.cpp -lSDL -lSDL_image -o ../bin/Release ProjetGSTL