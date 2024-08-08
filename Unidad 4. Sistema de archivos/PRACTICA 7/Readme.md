<div style="text-align: justify">

# PRÁCTICA 7 - COMUNICACIÓN INTER PROCESOS (IPC) EN LINUX Y WINDOWS

#### ASEGÚRESE DE LEER TODO EL TEXTO ANTES DE COMENZAR CON LA PRÁCTICA

## 🏆 COMPETENCIA

- **El alumno comprende el funcionamiento de las tuberías (pipes) sin nombre y de la memoria compartida como mecanismos de comunicación entre procesos tanto en el sistema operativo Linux como Windows para el desarrollo de aplicaciones concurrentes con soporte de comunicación.**

## ✅ DETALLES A CONSIDERAR DE LA PRÁCTICA

#### No se mencionan puntos con recomendaciones, ya que todos se consideran intuitivos y están bien abordados en el [`reporte.pdf`](Unidad4_Práctica7_Reporte.pdf). Sin embargo, hay algunas sugerencias en la sección de código - punto que soluciona.

## 🧑‍💻 CÓDIGOS Y EJECUCIONES

#### Se mencionan los nombres de los códigos, su forma de compilación, cómo se ejecutan y el punto de la asignación que solucionan. Lo anterior se presenta en dos tablas distintas, una para cada sistema operativo.

#### Estas tablas con la forma de compilación y ejecución solo funcionan para los códigos de este repositorio en el orden de archivos y carpetas presentado. Si cambia la ubicación de una carpeta o archivo, la ejecución puede no funcionar como se espera.

#### Siga la guía de compilación y ejecución de estas tablas. NO compile ni ejecute como se muestra en las capturas de pantalla del [`reporte.pdf`](Unidad4_Práctica7_Reporte.pdf), ya que los códigos fueron modificados para una ejecución más sencilla.

## TABLA: CÓDIGO - PUNTO QUE SOLUCIONA (SECCIÓN LINUX 🐧)

✪ Para el punto 6, primero compile y ejecute el programa [`memoria_2.c`](LINUX/memoria_2.c). Notará que al ejecutar el programa se quedará pausado; esto es normal, ya que el programa esperará hasta que se ejecute [`memoria_1.c`](LINUX/memoria_1.c). Por lo tanto, primero compile y ejecute [`memoria_2.c`](LINUX/memoria_2.c) y luego [`memoria_1.c`](LINUX/memoria_1.c). Después de ejecutar [`memoria_1.c`](LINUX/memoria_1.c), [`memoria_2.c`](LINUX/memoria_2.c) terminará automáticamente su ejecución.

| PUNTO | NOMBRE DEL CÓDIGO | COMPILACION | EJECUCION |
|-------|-------------------|-------------|-----------|
| 2     | [tuberias_1.c](LINUX/tuberias_1.c) | gcc tuberias_1.c -o tuberias_1 | ./tuberias_1 |
| 5     | [tuberias_2.c](LINUX/tuberias_2.c) | gcc tuberias_2.c -o tuberias_2 | ./tuberias_2 |
| 6     | [memoria_2.c](LINUX/memoria_2.c) | gcc memoria_2.c -o memoria_2 | ./memoria_2 |
| 6     | [memoria_1.c](LINUX/memoria_1.c) | gcc memoria_1.c -o memoria_1 | ./memoria_1 |
| 8     | [memoria_3.c](LINUX/memoria_3.c) | gcc memoria_3.c -o memoria_3 | ./memoria_3 |
| 9     | [tuberias_3.c](LINUX/tuberias_3.c) | gcc tuberias_3.c -o tuberias_3 | ./tuberias_3 |
| 9     | [memoria_4.c](LINUX/memoria_4.c) | gcc memoria_4.c -o memoria_4 | ./memoria_4 |

## TABLA: CÓDIGO - PUNTO QUE SOLUCIONA (SECCIÓN WINDOWS 🪟)

✪ Se recomienda compilar todos los códigos en Visual Studio Code, pero para la ejecución y capturas de pantalla usar la consola CMD.

✪ Para el punto 7, primero compile y ejecute el programa [`memoria_2.c`](WINDOWS/memoria_2.c). Notará que al ejecutar el programa se quedará pausado; esto es normal, ya que el programa esperará hasta que se ejecute [`memoria_1.c`](WINDOWS/memoria_1.c). Por lo tanto, primero compile y ejecute [`memoria_2.c`](WINDOWS/memoria_2.c) y luego [`memoria_1.c`](WINDOWS/memoria_1.c). Después de ejecutar [`memoria_1.c`](WINDOWS/memoria_1.c), [`memoria_2.c`](WINDOWS/memoria_2.c) terminará automáticamente su ejecución.

✪ Para el punto 8, primero compile [memoria_5.c](WINDOWS/memoria_5.c) y [memoria_4.c](WINDOWS/memoria_4.c). Luego compile [memoria_3.c](WINDOWS/memoria_3.c) y ejecute `memoria_3.exe memoria_4.exe`.

✪ Para el punto 9, hay dos carpetas: una para IPC tuberías y otra para IPC memoria. Cada una contiene todos los códigos que resuelven este punto. Para cada carpeta, primero compile [suma.c](WINDOWS/Punto%209%20-%20Tuberias/suma.c), [resta.c](WINDOWS/Punto%209%20-%20Tuberias/resta.c), [multiplicacion.c](WINDOWS/Punto%209%20-%20Tuberias/multiplicacion.c), [traspuesta.c](WINDOWS/Punto%209%20-%20Tuberias/traspuesta.c), [inversa.c](WINDOWS/Punto%209%20-%20Tuberias/inversa.c), y [recoleccion.c](WINDOWS/Punto%209%20-%20Tuberias/recoleccion.c). Finalmente, compile y ejecute [padre.c](WINDOWS/Punto%209%20-%20Tuberias/padre.c).

| PUNTO | NOMBRE DEL CÓDIGO | EJECUCIÓN |
|-------|-------------------|-----------|
| 4     | [tuberias_1_1.c](WINDOWS/tuberias_1_1.c) | SOLO COMPILAR, NO EJECUTAR, SE EJECUTA DESDE tuberias_1 |
| 4     | [tuberias_1.c](WINDOWS/tuberias_1.c) | tuberias_1.exe tuberias_1_1.exe |
| 5     | [tuberias_2_2.c](WINDOWS/tuberias_2_2.c) | SOLO COMPILAR, NO EJECUTAR, SE EJECUTA DESDE tuberias_2 |
| 5     | [tuberias_2_1.c](WINDOWS/tuberias_2_1.c) | SOLO COMPILAR, NO EJECUTAR, SE EJECUTA DESDE tuberias_2 |
| 5     | [tuberias_2.c](WINDOWS/tuberias_2.c) | tuberias_2.exe tuberias_2_1.exe |
| 7     | [memoria_2.c](WINDOWS/memoria_2.c) | memoria_2.exe  |
| 7     | [memoria_1.c](WINDOWS/memoria_1.c) | memoria_1.exe  |
| 8     | [memoria_5.c](WINDOWS/memoria_5.c) | SOLO COMPILAR, NO EJECUTAR, SE EJECUTA DESDE memoria_3  |
| 8     | [memoria_4.c](WINDOWS/memoria_4.c) | SOLO COMPILAR, NO EJECUTAR, SE EJECUTA DESDE memoria_3 |
| 8     | [memoria_3.c](WINDOWS/memoria_3.c) | memoria_3.exe memoria_4.exe  |
| 9 (tuberias) | [suma.c](WINDOWS/Punto%209%20-%20Tuberias/suma.c) | SOLO COMPILAR, NO EJECUTAR, SE EJECUTA DESDE padre |
| 9 (tuberias) | [resta.c](WINDOWS/Punto%209%20-%20Tuberias/resta.c) | SOLO COMPILAR, NO EJECUTAR, SE EJECUTA DESDE padre |
| 9 (tuberias) | [multiplicacion.c](WINDOWS/Punto%209%20-%20Tuberias/multiplicacion.c) | SOLO COMPILAR, NO EJECUTAR, SE EJECUTA DESDE padre |
| 9 (tuberias) | [traspuesta.c](WINDOWS/Punto%209%20-%20Tuberias/traspuesta.c) | SOLO COMPILAR, NO EJECUTAR, SE EJECUTA DESDE padre |
| 9 (tuberias) | [inversa.c](WINDOWS/Punto%209%20-%20Tuberias/inversa.c) | SOLO COMPILAR, NO EJECUTAR, SE EJECUTA DESDE padre |
| 9 (tuberias) | [recoleccion.c](WINDOWS/Punto%209%20-%20Tuberias/recoleccion.c) | SOLO COMPILAR, NO EJECUTAR, SE EJECUTA DESDE padre |
| 9 (tuberias) | [padre.c](WINDOWS/Punto%209%20-%20Tuberias/padre.c) | padre.exe |
| 9 (memoria)  | [suma.c](WINDOWS/Punto%209%20-%20Memoria/suma.c) | SOLO COMPILAR, NO EJECUTAR, SE EJECUTA DESDE padre |
| 9 (memoria)  | [resta.c](WINDOWS/Punto%209%20-%20Memoria/resta.c) | SOLO COMPILAR, NO EJECUTAR, SE EJECUTA DESDE padre |
| 9 (memoria)  | [multiplicacion.c](WINDOWS/Punto%209%20-%20Memoria/multiplicacion.c) | SOLO COMPILAR, NO EJECUTAR, SE EJECUTA DESDE padre |
| 9 (memoria)  | [traspuesta.c](WINDOWS/Punto%209%20-%20Memoria/traspuesta.c) | SOLO COMPILAR, NO EJECUTAR, SE EJECUTA DESDE padre |
| 9 (memoria)  | [inversa.c](WINDOWS/Punto%209%20-%20Memoria/inversa.c) | SOLO COMPILAR, NO EJECUTAR, SE EJECUTA DESDE padre |
| 9 (memoria)  | [recoleccion.c](WINDOWS/Punto%209%20-%20Memoria/recoleccion.c) | SOLO COMPILAR, NO EJECUTAR, SE EJECUTA DESDE padre |
| 9 (memoria)  | [padre.c](WINDOWS/Punto%209%20-%20Memoria/padre.c) | padre.exe |

## 📝 NOTAS IMPORTANTES

- **PONDERACIÓN**: El [`reporte.pdf`](Unidad4_Práctica7_Reporte.pdf) de este repositorio es el documento original presentado al profesor durante el semestre 2024-2. No se incluyen los puntos de corrección ya que la calificación de esta práctica fue 10.

- **CÓDIGOS**: Notará que los códigos en este repositorio pueden diferir de los presentados en las capturas de pantalla del archivo [`reporte.pdf`](Unidad4_Práctica7_Reporte.pdf). Estas diferencias se deben a modificaciones realizadas para documentar mejor el código y simplificar el proceso de compilación y ejecución, aunque la funcionalidad es la misma. Se recomienda utilizar las tablas de compilación y ejecución proporcionadas para los códigos de este repositorio. Si intenta copiar los códigos directamente desde [`reporte.pdf`](Unidad4_Práctica7_Reporte.pdf), es posible que las instrucciones de compilación y ejecución no le funcionen. Por lo tanto, se sugiere usar los códigos del repositorio. Además, tenga en cuenta que la forma de compilación y ejecución puede no funcionar si cambia el orden de los archivos o las carpetas en comparación con cómo se presentan en este repositorio. Si modifica este orden, es posible que necesite ajustar algunos códigos y métodos de ejecución.

- **ADVERTENCIA**: Se recomienda verificar todos los puntos de la práctica, ya que pueden variar con respecto a su asignación. Ensamble su propio reporte considerando los cambios pertinentes.

</div>