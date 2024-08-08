<div style="text-align: justify">

# PRÁCTICA 3 - INTRODUCCIÓN A LOS SISTEMAS OPERATIVOS LINUX Y WINDOWS: INTERFAZ DE INTERRUPCIONES

#### ASEGÚRESE DE LEER TODO EL TEXTO ANTES DE COMENZAR CON LA PRÁCTICA

## 🏆 COMPETENCIA

- **El alumno aprende a programar aplicaciones sencillas a nivel ensamblador bajo los sistemas operativos Linux y Windows utilizando la interfaz de interrupciones respectiva de cada sistema, mediante la comprensión de la estructura general e instrucciones para el lenguaje ensamblador del procesador Intel de 32 bits.**

## ✅ DETALLES A CONSIDERAR DE LA PRÁCTICA

#### Se mencionan solo los puntos con recomendaciones importantes. Los demás puntos se consideran intuitivos y muy bien abordados en el [`reporte.pdf`](Unidad2_Práctica3_Reporte.pdf).

### 🐧 SECCIÓN LINUX

| PUNTO | DETALLES |
|-------|----------|
| 2     | NO ES NECESARIO DESARROLLAR ESTE PUNTO, PUEDE GUARDAR SUS PROGRAMAS EN CUALQUIER LUGAR Y NO ES NECESARIO BORRARLOS. |

### 🪟 SECCIÓN WINDOWS

| PUNTO | DETALLES |
|-------|----------|
| 2     | NO ES NECESARIO DESARROLLAR ESTE PUNTO, PUEDE GUARDAR SUS PROGRAMAS EN CUALQUIER LUGAR Y NO ES NECESARIO BORRARLOS. |

## 🧑‍💻 CÓDIGOS Y EJECUCIONES

#### Se mencionan los nombres de los códigos, su forma de compilación, cómo se ejecutan y el punto de la asignación que solucionan. Lo anterior se presenta en dos tablas distintas, una para cada sistema operativo.

#### Estas tablas con la forma de ensamblar, enlazar y ejecutar solo funcionan para los códigos de este repositorio en el orden de archivos y carpetas presentado. Si cambia la ubicación de una carpeta o archivo, la ejecución puede no funcionar como se espera.

#### Siga la guía de ensamblar, enlazar y ejecutar de estas tablas. NO compile ni ejecute como se muestra en las capturas de pantalla del [`reporte.pdf`](Unidad2_Práctica3_Reporte.pdf), ya que los códigos fueron modificados para una ejecución más sencilla.

## TABLA: CÓDIGO - PUNTO QUE SOLUCIONA (SECCIÓN LINUX 🐧)

✪ Antes de ensamblar en Linux, ejecute `sudo apt install nasm` en su terminal. Si le solicita contraseña, digite la misma que usa para ingresar a su sistema operativo Linux.

| PUNTO | NOMBRE DEL CÓDIGO | ENSAMBLAR | ENLAZAR | EJECUTAR |
|-------|-------------------|-----------|---------|----------|
| 3,4,5,6 | [Escribir.asm](LINUX/Escribir.asm) | nasm -f elf64 -o Escribir.o Escribir.asm  | ld Escribir.o -o Escribir | ./Escribir |
| 7,8 | [Leer_Escribir.asm](LINUX/Leer_Escribir.asm) | nasm -f elf64 -o Leer_Escribir.o Leer_Escribir.asm  | ld Leer_Escribir.o -o Leer_Escribir | ./Leer_Escribir |
| 9 | [Contador.asm](LINUX/Contador.asm) | nasm -f elf64 -o Contador.o Contador.asm  | ld Contador.o -o Contador | ./Contador |
| 10 | [Intercalado.asm](LINUX/Intercalado.asm) | nasm -f elf64 -o Intercalado.o Intercalado.asm  | ld Intercalado.o -o Intercalado | ./Intercalado |
| 11 | [Longitud.asm](LINUX/Longitud.asm) | nasm -f elf64 -o Longitud.o Longitud.asm  | ld Longitud.o -o Longitud | ./Longitud |
| 12 | [Inversa.asm](LINUX/Inversa.asm) | nasm -f elf64 -o Inversa.o Inversa.asm  | ld Inversa.o -o Inversa | ./Inversa |
| 13 | [Calculadora.asm](LINUX/Calculadora.asm) | nasm -f elf64 -o Calculadora.o Calculadora.asm  | ld Calculadora.o -o Calculadora | ./Calculadora |

## TABLA: CÓDIGO - PUNTO QUE SOLUCIONA (SECCIÓN WINDOWS 🪟)

✪ Por defecto, Windows no reconoce `nasm` ni `ld`, por lo que tendrá que seguir una serie de pasos y descargar ciertos programas que le permitirán usar dichos comandos. Consulte este video [CLIC](https://www.youtube.com/watch?v=95z1cUtIcS4) para poder ensamblar y enlazar en Windows.

✪ En el video, los enlaces de MinGW y NASM tienen acortadores. Puede ir directamente a la página de descarga dando clic en los siguientes enlaces:
- [MinGW](https://sourceforge.net/projects/mingw/)
- [Nasm](https://www.nasm.us/)

✪ Es posible que el archivo `.exe` de NASM que descargue desde su página oficial sea detectado como peligroso. No se preocupe por su dispositivo; el archivo `.exe` es confiable y seguro. Solo haga clic en "Más información" y seleccione "Ejecutar de todas formas" para permitir la ejecución del programa. Cabe mencionar que seguimos el mismo proceso y nuestros dispositivos estuvieron y siguen estando seguros; no es necesario desactivar el antivirus, solo seguir los pasos anteriores.

✪ Ignore las advertencias generadas al enlazar en caso de que se muestren; estas no afectan el funcionamiento de los programas.

| PUNTO | NOMBRE DEL CÓDIGO | ENSAMBLAR | ENLAZAR | EJECUTAR |
|-------|-------------------|-----------|---------|----------|
| 3,4,5,6 | [Escribir.asm](WINDOWS/Escribir.asm) | nasm -f win32 -o Escribir.obj Escribir.asm | ld Escribir.obj -m i386pe -e _main -L "C:\Windows\SysWOW64" -l kernel32 -o Escribir.exe| Escribir.exe |
| 7,8 | [Leer_Escribir.asm](WINDOWS/Leer_Escribir.asm) | nasm -f win32 -o Leer_Escribir.obj Leer_Escribir.asm | ld Leer_Escribir.obj -m i386pe -e _main -L "C:\Windows\SysWOW64" -l kernel32 -o Leer_Escribir.exe| Leer_Escribir.exe |
| 9 | [Contador.asm](WINDOWS/Contador.asm) | nasm -f win32 -o Contador.obj Contador.asm | ld Contador.obj -m i386pe -e _main -L "C:\Windows\SysWOW64" -l kernel32 -o Contador.exe| Contador.exe |
| 9 | [Intercalado.asm](WINDOWS/Intercalado.asm) | nasm -f win32 -o Intercalado.obj Intercalado.asm | ld Intercalado.obj -m i386pe -e _main -L "C:\Windows\SysWOW64" -l kernel32 -o Intercalado.exe| Intercalado.exe |
| 9 | [Longitud.asm](WINDOWS/Longitud.asm) | nasm -f win32 -o Longitud.obj Longitud.asm | ld Longitud.obj -m i386pe -e _main -L "C:\Windows\SysWOW64" -l kernel32 -o Longitud.exe| Longitud.exe |
| 9 | [Inversa.asm](WINDOWS/Inversa.asm) | nasm -f win32 -o Inversa.obj Inversa.asm | ld Inversa.obj -m i386pe -e _main -L "C:\Windows\SysWOW64" -l kernel32 -o Inversa.exe| Inversa.exe |
| 9 | [Calculadora.asm](WINDOWS/Calculadora.asm) | nasm -f win32 -o Calculadora.obj Calculadora.asm | ld Calculadora.obj -m i386pe -e _main -L "C:\Windows\SysWOW64" -l kernel32 -o Calculadora.exe| Calculadora.exe |

## 📝 NOTAS IMPORTANTES

- **PONDERACIÓN**: El [`reporte.pdf`](Unidad2_Práctica3_Reporte.pdf) de este repositorio es el documento original presentado al profesor durante el semestre 2024-2. No se incluyen los puntos de corrección ya que la calificación de esta práctica fue 10.

- **CÓDIGOS**: Los códigos en este repositorio están mejorados y completamente documentados en comparación con los códigos que aparecen en las capturas de pantalla del [`reporte.pdf`](Unidad2_Práctica3_Reporte.pdf). Ambos conjuntos de códigos son correctos, pero se recomienda utilizar los códigos de este repositorio para ensamblar su propio reporte debido a la documentación adicional. Además, algunos códigos y ejecutables tienen el nombre y/o forma de ejecución cambiados con respecto a lo mostrado en las capturas del [`reporte.pdf`](Unidad2_Práctica3_Reporte.pdf). Sin embargo, en este documento Markdown, específicamente en las tablas "código - punto que soluciona", se mencionan los nombres de los códigos, el punto que solucionan, cómo se ensambla, enlaza y ejecuta para mayor comodidad. Cabe mencionar que la forma de ensamblar, enlazar y ejecutar puede no funcionar si cambia el orden de los archivos o las carpetas con respecto a cómo se presentan en este repositorio. Por ello, se recomienda descargar el repositorio, compilar y ejecutar siguiendo el orden dado. Si modifica este orden, es posible que requiera hacer cambios en algunos códigos y en algunas formas de ejecución.

- **ADVERTENCIA**: Se recomienda verificar todos los puntos de la práctica, ya que pueden variar con respecto a su asignación. Ensamble su propio reporte considerando los cambios pertinentes.

</div>
