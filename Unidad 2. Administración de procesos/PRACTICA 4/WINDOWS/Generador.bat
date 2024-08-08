@echo off
echo -------------- Extension del archivo --------------
set /p extension=Ingrese la extension del archivo: 
set mensaje=Creando un archivo %extension%
echo.
timeout /t 1 /nobreak > nul
echo -------------- %mensaje% --------------
echo @echo off > ejecutable.%extension%
timeout /t 1 /nobreak > nul
echo -------------- Archivo creado --------------
echo.
timeout /t 1 /nobreak > nul
echo -------------- Editando archivo --------------
set /p edicion=Ingrese el contenido del archivo: 
echo %edicion%>>ejecutable.%extension%
echo.
timeout /t 1 /nobreak > nul
echo -------------- Ejecutando archivo --------------
start ejecutable.%extension%
echo.
echo -------------- Finalizado --------------
pause > nul
