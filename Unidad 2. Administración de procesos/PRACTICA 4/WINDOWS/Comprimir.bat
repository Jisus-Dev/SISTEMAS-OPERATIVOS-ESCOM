@echo off
cls
echo "-------------- Captura fecha ---------------"
for /F "tokens=1,2,3 delims=/ " %%V in ('date /t') do set dia=%%V%%W%%X
set tiempo=%time%
for /F "tokens=1,2,3 delims=:." %%V in ("%tiempo%") do set tiempo=%%V%%W%%X
set fecha=%dia%%tiempo%
echo "-------------- Empacando ----------------"
tar -cvf ".\respaldo%fecha%.tar" ".\directorio1" ".\directorio2" ".\directorio3"
echo "-------------- Comprimiendo ----------------"
"C:\Program Files\WinRAR\rar.exe" a -c- ".\respaldo%fecha%.rar" ".\respaldo%fecha%.tar"
echo "-------------- Enviando a otro directorio --------------"
copy ".\respaldo%fecha%.rar" ".\respaldos"
echo "-------------- Descomprimiendo ------------------"
"C:\Program Files\WinRAR\rar.exe" e -y ".\respaldos\respaldo%fecha%.rar" ".\respaldos"
echo "-------------- Desempacando ----------------"
tar -xvf ".\respaldos\respaldo%fecha%.tar" -C ".\respaldos"
echo "-------------- Limpiando ------------------"
del ".\respaldo%fecha%.rar"
del ".\respaldo%fecha%.tar"
echo "-------------- Terminado ------------------" 