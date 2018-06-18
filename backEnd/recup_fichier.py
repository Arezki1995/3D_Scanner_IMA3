#!/usr/bin/env python
# -*- coding: latin-1 -*-

print("hello")

import serial
import time   
ser = serial.Serial('/dev/ttyACM0', 9600) #changer le port si besoin
fichier = open("/var/www/html/backEnd/data_brut.txt", "w") 
# 'w' pour une ouverture en mode ecrase et réécrit

nb_mesure = ser.readline() #recoit nb mesure par tour
nb_tour = ser.readline() #recoit nb tour

print(nb_mesure)
print(nb_tour)
fichier.write(nb_mesure)
fichier.write(nb_tour)
i = 0

y = int(nb_mesure) * int(nb_tour)

while i < y:
	x = ser.readline()
	fichier.write(x)
	print(x)
	i = i + 1

print("fini_py")
fichier.close()

