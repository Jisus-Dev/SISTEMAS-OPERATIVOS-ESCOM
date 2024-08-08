<div style="text-align: justify">

# PRÁCTICA 2 - INTRODUCCIÓN A LOS SISTEMAS OPERATIVOS LINUX Y WINDOWS: INTERFAZ DE LLAMADAS AL SISTEMA

#### ASEGÚRESE DE LEER TODO EL TEXTO ANTES DE COMENZAR CON LA PRÁCTICA

## 🏆 COMPETENCIA

- **El alumno aprende a familiarizarse con los sistemas operativos Linux y Windows mediante el uso de la interfaz de llamadas al sistema respectiva de cada sistema operativo bajo el lenguaje C para la invocación de llamadas al sistema propias de los sistemas operativos revisados.**

## ✅ DETALLES A CONSIDERAR DE LA PRÁCTICA

#### Se mencionan solo los puntos con recomendaciones importantes. Los demás puntos se consideran intuitivos y muy bien abordados en el [`reporte.pdf`](Unidad1_Práctica2_Reporte.pdf).

| PUNTO | DETALLES |
|-------|----------|
| 1     | Se recomienda utilizar una carpeta compartida entre el sistema operativo base y la máquina virtual en lugar de un USB, ya que es más fácil de manejar y será útil para las prácticas futuras. Si su máquina virtual es Linux y su sistema operativo base es Windows, puede consultar este video [CLIC](https://www.youtube.com/watch?v=Mzd5i48OAiU) u otro tutorial para crear la carpeta compartida. |
| 3     | Puede omitir este paso si transfiere los archivos necesarios para la resolución de la práctica a través de la carpeta compartida. Recuerde que la carpeta compartida es válida, evita el uso de USB y reduce la complejidad al transferir archivos entre el sistema operativo base y la máquina virtual. |
| 4     | En el [`reporte.pdf`](Unidad1_Práctica2_Reporte.pdf) viene primero la captura de pantalla del contenido colocado desde Windows y luego viene la captura de pantalla del texto con el que se está modificando el archivo a través de `gedit`. |
| 5     | Notará que al extraer el `.txt` y el `.docx` a Windows desde la carpeta compartida, el archivo `.txt` abrirá sin problemas, pero el `.docx` se corrompe y no abrirá. Esto es completamente normal. |

## 🧑‍💻 CÓDIGOS Y EJECUCIONES

#### Se mencionan los nombres de los códigos, su forma de compilación, cómo se ejecutan y el punto de la asignación que solucionan. Lo anterior se presenta en dos tablas distintas, una para cada sistema operativo.

#### Estas tablas con la forma de compilación y ejecución solo funcionan para los códigos de este repositorio en el orden de archivos y carpetas presentado. Si cambia la ubicación de una carpeta o archivo, la ejecución puede no funcionar como se espera.

#### Siga la guía de compilación y ejecución de estas tablas. NO compile ni ejecute como se muestra en las capturas de pantalla del [`reporte.pdf`](Unidad1_Práctica2_Reporte.pdf), ya que los códigos fueron modificados para una ejecución más sencilla.

## TABLA: CÓDIGO - PUNTO QUE SOLUCIONA (SECCIÓN LINUX 🐧)

✪ Para el punto 8 `NO` tiene que tener la carpeta `Practica_2` creada; si ya está creada causará un error.  
✪ Para el punto 9 tiene que tener un archivo llamado `permisos.txt` creado antes de ejecutar el programa.  
✪ Para el punto 11 tiene que tener la carpeta `Practica_2_Copia` antes de ejecutar el programa.

| PUNTO | NOMBRE DEL CÓDIGO | COMPILACIÓN | EJECUCIÓN |
|-------|-------------------|-------------|-----------|
| 8     | [archivosaleatorios.c](LINUX/archivosaleatorios.c) | gcc archivosaleatorios.c -o archivosaleatorios | ./archivosaleatorios Practica_2 |
| 9     | [permisos.c](LINUX/permisos.c) | gcc permisos.c -o permisos | ./permisos permisos.txt 777 |
| 10    | [informacion.c](LINUX/informacion.c) | gcc informacion.c -o informacion | ./informacion Practica_2 |
| 11    | [mostrarycopiar.c](LINUX/mostrarycopiar.c) | gcc mostrarycopiar.c -o mostrarycopiar | ./mostrarycopiar Practica_2 Practica_2_Copia |

## TABLA: CÓDIGO - PUNTO QUE SOLUCIONA (SECCIÓN WINDOWS 🪟)

✪ Se recomienda compilar todos los códigos en Visual Studio Code, pero para la ejecución y capturas de pantalla usar la consola CMD.

✪ Para el punto 8 `NO` tiene que tener la carpeta `Practica_2` creada; si ya está creada causará un error.  
✪ Para el punto 9 tiene que tener un archivo llamado `permisos.txt` creado antes de ejecutar el programa.  
✪ Para el punto 11 tiene que tener la carpeta `Practica_2_Copia` antes de ejecutar el programa.

| PUNTO | NOMBRE DEL CÓDIGO | EJECUCIÓN |
|-------|-------------------|-----------|
| 12    | [archivosaleatorios.c](WINDOWS/archivosaleatorios.c) | archivosaleatorios.exe Practica_2 |
| 12    | [permisos.c](WINDOWS/permisos.c) | permisos.exe permisos.txt 777 |
| 12    | [informacion.c](WINDOWS/informacion.c) | informacion.exe Practica_2 |
| 12    | [mostrarycopiar.c](WINDOWS/mostrarycopiar.c) | mostrarycopiar.exe Practica_2 Practica_2_Copia |

## 📝 NOTAS IMPORTANTES

- **PONDERACIÓN**: El [`reporte.pdf`](Unidad1_Práctica2_Reporte.pdf) de este repositorio es el documento original presentado al profesor durante el semestre 2024-2. Se incluyen los puntos de corrección basados en la retroalimentación dada por el profesor, ya que la calificación de esta práctica fue 8.5; las correcciones necesarias para obtener una calificación de 10 son mínimas y se mencionan en el siguiente punto.

- **CORRECCIÓN**: En el reporte de esta práctica, las conclusiones se realizaron de forma individual por cada miembro del equipo. Sin embargo, las conclusiones deben ser realizadas en equipo; es decir, debe presentarse una sola conclusión por todo el equipo. Además, faltó incluir en el [`reporte.pdf`](Unidad1_Práctica2_Reporte.pdf) una captura de pantalla de ejecución del programa [`informacion.c`](WINDOWS/informacion.c) de la sección Windows punto 12.

- **CÓDIGOS**: Notará que los códigos en este repositorio pueden diferir de los presentados en las capturas de pantalla del archivo [`reporte.pdf`](Unidad1_Práctica2_Reporte.pdf). Estas diferencias se deben a modificaciones realizadas para documentar mejor el código y simplificar el proceso de compilación y ejecución, aunque la funcionalidad es la misma. Se recomienda utilizar las tablas de compilación y ejecución proporcionadas para los códigos de este repositorio. Si intenta copiar los códigos directamente desde [`reporte.pdf`](Unidad1_Práctica2_Reporte.pdf), es posible que las instrucciones de compilación y ejecución no le funcionen. Por lo tanto, se sugiere usar los códigos del repositorio. Además, tenga en cuenta que la forma de compilación y ejecución puede no funcionar si cambia el orden de los archivos o las carpetas en comparación con cómo se presentan en este repositorio. Si modifica este orden, es posible que necesite ajustar algunos códigos y métodos de ejecución.

- **ADVERTENCIA**: Se recomienda verificar todos los puntos de la práctica, ya que pueden variar con respecto a su asignación. Ensamble su propio reporte considerando los cambios pertinentes.

</div>