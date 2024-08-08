#!/bin/sh
#
clear
#
echo "-------------- Obteniendo fecha ---------------"
fecha=`date +%Y%m%d%H%M`
#
echo "-------------- Empacando ----------------"
tar -cvf ./respaldo$fecha.tar ./directorio1 ./directorio2 ./directorio3
#
echo "-------------- Comprimiendo ----------------"
bzip2 ./respaldo$fecha.tar
#
echo "-------------- Enviando a otro directorio --------------"
cp ./respaldo$fecha.tar.bz2 ./respaldos
#
echo "-------------- Descomprimiendo ------------------"
bunzip2 ./respaldos/respaldo$fecha.tar.bz2
#
echo "-------------- Desempacando ----------------"
tar -xvf ./respaldos/respaldo$fecha.tar
#
echo "-------------- Limpiando ------------------"
rm -f ./respaldo$fecha.tar.bz2
rm -f ./respaldo$fechar.tar
#
echo "-------------- Terminado ------------------"