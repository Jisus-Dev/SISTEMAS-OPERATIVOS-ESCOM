@echo off
set /a num_archivos=0

if "%~1"=="" (
    echo Debe ingresar un directorio como argumento de entrada
    goto fin
)

set "directorio=%~1"

if not exist "%directorio%" (
    echo %directorio% no es un directorio valido
    goto fin
)

echo Archivos en "%directorio%":
for %%f in ("%directorio%\*") do (
    if "%%~xf" NEQ "" (
        echo %%~nxf
        set /a num_archivos+=1
    )
)

echo El directorio "%directorio%" contiene %num_archivos% archivos.

:fin