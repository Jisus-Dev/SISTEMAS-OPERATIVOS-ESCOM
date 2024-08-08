@echo off
cls
echo "-------------- Obteniendo archivo mas reciente --------------"
set "directorio=.\respaldos"
for /f "delims=" %%a in ('dir /b /od /a-d "%directorio%\*.tar" 2^>nul') do set "archivo=%directorio%\%%a"
if "%archivo%" == "" (
    echo No se encontraron archivos tar en el directorio especificado.
    exit /b 1
)
echo El archivo mas reciente es: %archivo%
echo "-------------- Descromprimiendo --------------"
set "ruta_destino=.\descomprimidos"

if not exist "%ruta_destino%" (
    mkdir "%ruta_destino%"
)
"%ProgramFiles%\WinRAR\WinRAR.exe" x -y "%archivo%" "%ruta_destino%"
echo "-------------- Terminado --------------"