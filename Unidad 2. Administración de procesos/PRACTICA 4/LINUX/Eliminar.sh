#!/bin/bash

clear

# Ruta a evaluar
ruta_destino="./eliminar"

# Eliminar los archivos del directorio que cumplan con el criterio
echo "Eliminando archivos con segundo carácter igual a 'e' en $ruta_destino..."
for archivo in $ruta_destino/*; do
    nombre=${archivo##*/}
    if [ -f "$archivo" ] && [ "${nombre:1:1}" = "e" ]; then
        echo "Eliminando archivo ${archivo##*/}"
        rm "$archivo"
    fi
done

echo "Proceso finalizado"