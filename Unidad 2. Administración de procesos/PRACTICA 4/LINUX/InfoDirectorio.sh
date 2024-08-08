#!/bin/sh
#
clear

# Verificar que se haya ingresado un argumento de entrada
if [ $# -eq 0 ]; then
    echo "Debe ingresar un directorio como argumento de entrada"
    exit 1
fi

# Verificar que el argumento de entrada sea un directorio valido
if [ ! -d "$1" ]; 
    then
        echo "$1 no es un directorio valido."
        exit 1
fi

# Contar el numero de archivos en el directorio
num_archivos=$(find "$1" -maxdepth 1 -type f | wc -l)

# Mostrar el numero total de archivos en el directorio
echo "El directorio $1 contiene $num_archivos archivos."

# Mostrar los archivos del directorio
echo "Archivos en $1:"
for archivo in "$1"/*; do
    if [ -f "$archivo" ]; then
        echo "${archivo##*/}"
    fi
done
