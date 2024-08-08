#!/bin/sh
#
clear
# Crear el archivo de script
echo "-------------- Creando archivo---------------"
echo "#!/bin/sh" > script_generado.sh
echo "echo "Hola, mundo!"" >> script_generado.sh

# Dar permisos de edicion y ejecucion
echo "-------------- Dando permisos ---------------"
chmod +x script_generado.sh

# Abrir el archivo de script para edicion
echo "-------------- Abro Nano para editar ---------------"
nano script_generado.sh

# Dar permisos de ejecucion
echo "-------------- Permisos de ejecucion ---------------"
chmod +x script_generado.sh

# Ejecutar script generado
echo "-------------- Ejecutando el nuevo script ---------------"
./script_generado.sh