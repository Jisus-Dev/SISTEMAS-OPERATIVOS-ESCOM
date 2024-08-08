#!/bin/bash
#
clear
#
echo "-------------- Obteniendo archivo más reciente ---------------"
#
directorio="./respaldos"
#
archivo=$(ls -t "$directorio"/*.tar | head -1)
#
if [ -z "$archivo" ]; then
    echo "No se encontraron archivos tar en el directorio especificado."
    exit 1
fi
#
echo "El archivo más reciente es: $archivo"
#
echo "-------------- Descomprimiendo ------------------"
#
ruta_destino="./descomprimidos"
#
mkdir -p "$ruta_destino"
#
tar -xf "$archivo" -C "$ruta_destino"
#
echo "-------------- Terminado ------------------"
