#!/bin/bash
#Script d'installation des dependances pour le projet g�nie logiciel INFO3 (pour distribution bas�e sur debian)
#GSTL

#Installation des composants SDL de developpement
sudo apt-get install libsdl1.2-dev libsdl-image1.2-dev subversion

mkdir /tmp/ProjetGenieLogiciel_GSTL
cd /tmp/ProjetGenieLogiciel_GSTL
svn checkout http://projet-genie-logiciel-gstl.googlecode.com/svn/trunk/ projet-genie-logiciel-gstl-read-only