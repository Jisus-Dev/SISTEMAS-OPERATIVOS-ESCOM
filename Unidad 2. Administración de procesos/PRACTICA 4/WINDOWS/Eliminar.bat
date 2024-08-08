@echo off
setlocal enabledelayedexpansion

set /p directory=Introduce la ruta del directorio:
echo Eliminando archivos que empiezan con segundo caracter igual a 'e' en "%directory%":

for %%f in ("%directory%\*") do (
    set "filename=%%~nxf"
    if "!filename:~1,1!"=="e" (
        echo Eliminando archivo: %%~nxf
        del "%%~f"
    )
)

echo Archivos eliminados correctamente.
pause