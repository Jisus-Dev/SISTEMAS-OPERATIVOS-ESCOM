@echo off
echo Opciones:
echo Directorio
echo DirectorioExtendido
echo Salir
set /p Op="Opcion: "
set fin=0
for %%V IN (Directorio DirectorioExtendido Salir) do (call :opcion_elegida %%V, %Op%)
if %fin%==0 echo "Opcion no encontrada"
goto :salir
:opcion_elegida
 if "%2"=="%1" if %1==Directorio dir & set fin=1 & goto :EOF else (
 if "%2"=="%1" if %1==DirectorioExtendido echo "Similar a dir" & set fin=1 & goto :EOF else (
 if "%2"=="%1" if %1==Salir set fin=1 & goto :EOF ))
 goto :EOF
:salir
 for %%V in (Hola como estan todos) do echo %%V
 pause