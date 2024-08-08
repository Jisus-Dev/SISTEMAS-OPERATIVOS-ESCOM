#!/bin/sh
#
clear
#
ls -l
#
rm -f ./prueba
#
ls -l
#
echo "------------------ Creando archivo: prueba ----------------"
#
echo "Hola a todos" >> prueba
echo "Esto es una prueba" >> prueba
echo "De un script" >> prueba
#
ls -l ./prueba
#
echo "------------------ Script terminado ----------------------"
more ./prueba