#!/bin/bash

#2>&1 Afficher les erreur

echo "Choisir la precision"

sudo python /var/www/html/backEnd/recup_fichier.py 

sudo /var/www/html/backEnd/./cylindriqueTOcartesien 

sudo /var/www/html/backEnd/./test

echo "Fichier compilé"
