<div style="text-align: justify">

# PRÁCTICA 5 - ADMINISTRADOR DE PROCESOS EN LINUX Y WINDOWS (1)

#### ASEGÚRESE DE LEER TODO EL TEXTO ANTES DE COMENZAR CON LA PRÁCTICA

## 🏆 COMPETENCIAS

- **El alumno aprende a familiarizarse con el administrador de procesos del sistema operativo Linux y Windows a través de la creación de nuevos procesos por copia exacta de código y/o por sustitución de código para el desarrollo de aplicaciones concurrentes sencillas.**

## ✅ DETALLES A CONSIDERAR DE LA PRÁCTICA

#### No se mencionan puntos con recomendaciones, ya que todos se consideran intuitivos y están bien abordados en el [`reporte.pdf`](Unidad2_Practica5_Reporte.pdf). Sin embargo, hay algunas sugerencias en la sección de código - punto que soluciona.

## 🧑‍💻 CÓDIGOS Y EJECUCIONES

#### Se mencionan los nombres de los códigos, su forma de compilación, cómo se ejecutan y el punto de la asignación que solucionan. Lo anterior se presenta en dos tablas distintas, una para cada sistema operativo.

#### Estas tablas con la forma de compilación y ejecución solo funcionan para los códigos de este repositorio en el orden de archivos y carpetas presentado. Si cambia la ubicación de una carpeta o archivo, la ejecución puede no funcionar como se espera.

#### Siga la guía de compilación y ejecución de estas tablas. NO compile ni ejecute como se muestra en las capturas de pantalla del [`reporte.pdf`](Unidad2_Practica5_Reporte.pdf), ya que los códigos fueron modificados para una ejecución más sencilla.

## TABLA: CÓDIGO - PUNTO QUE SOLUCIONA (SECCIÓN LINUX 🐧)

✪ Para obtener el tiempo de ejecución de un programa, utilice `time` antes del comando de ejecución del programa. Por ejemplo: `time ./sustitucion_3`. Esto obtendrá el tiempo de ejecución del programa `sustitucion_3`.

✪ Para el punto 4, el árbol de procesos puede variar con respecto al que se le solicite a usted. En este caso, se solicitó un árbol como el que se muestra en la imagen [pizarron.png](pizarron.png). Esta imagen es la original tomada del pizarrón cuando el profesor dibujó el árbol.

✪ Para el punto 6, primero compile [hola.c](LINUX/hola.c), luego compile y ejecute [sustitucion_1.c](LINUX/sustitucion_1.c).

✪ Para el punto 7, primero compile [expresion.c](LINUX/PUNTO%207/expresion.c), [permisos.c](LINUX/PUNTO%207/permisos.c) e [inversa.c](LINUX/PUNTO%207/inversa.c). Además, debe tener un archivo llamado `permisos.txt`. Después de realizar lo anterior, compile y ejecute [sustitucion_2.c](LINUX/PUNTO%207/sustitucion_2.c).

✪ Para el punto 8, primero compile [suma.c](LINUX/PUNTO%208/suma.c), [resta.c](LINUX/PUNTO%208/resta.c), [multiplicacion.c](LINUX/PUNTO%208/multiplicacion.c), [traspuesta.c](LINUX/PUNTO%208/traspuesta.c), [inversa.c](LINUX/PUNTO%208/inversa.c), y [archivo.c](LINUX/PUNTO%208/archivo.c). Luego, compile y ejecute [sustitucion_3.c](LINUX/PUNTO%208/sustitucion_3.c).


| PUNTO | NOMBRE DEL CÓDIGO | COMPILACION | EJECUCION |
|-------|-------------------|-------------|-----------|
| 3     | [copiaexacta_1.c](LINUX/copiaexacta_1.c) | gcc copiaexacta_1.c -o copiaexacta_1 | ./copiaexacta_1 |
| 3     | [copiaexacta_2.c](LINUX/copiaexacta_2.c) | gcc copiaexacta_2.c -o copiaexacta_2 | ./copiaexacta_2 |
| 4     | [copiaexacta_3.c](LINUX/copiaexacta_3.c) | gcc copiaexacta_3.c -o copiaexacta_3 | ./copiaexacta_3 |
| 5     | [copiaexacta_4.c](LINUX/copiaexacta_4.c) | gcc copiaexacta_4.c -o copiaexacta_4 | ./copiaexacta_4 |
| 5     | [copiaexacta_5.c](LINUX/copiaexacta_5.c) | gcc copiaexacta_5.c -o copiaexacta_5 | ./copiaexacta_5 |
| 6     | [hola.c](LINUX/hola.c) | gcc hola.c -o hola | SOLO COMPILAR, NO EJECUTAR, SE EJECUTA DESDE sustitucion_1  |
| 6     | [sustitucion_1.c](LINUX/sustitucion_1.c) | gcc sustitucion_1.c -o sustitucion_1 | ./sustitucion_1 |
| 7     | [expresion.c](LINUX/PUNTO%207/expresion.c) | gcc expresion.c -o expresion | SOLO COMPILAR, NO EJECUTAR, SE EJECUTA DESDE sustitucion_2 |
| 7     | [permisos.c](LINUX/PUNTO%207/permisos.c) | gcc permisos.c -o permisos | SOLO COMPILAR, NO EJECUTAR, SE EJECUTA DESDE sustitucion_2 |
| 7     | [inversa.c](LINUX/PUNTO%207/inversa.c) | gcc inversa.c -o inversa | SOLO COMPILAR, NO EJECUTAR, SE EJECUTA DESDE sustitucion_2 |
| 7     | [sustitucion_2.c](LINUX/PUNTO%207/sustitucion_2.c) | gcc sustitucion_2.c -o sustitucion_2 | ./sustitucion_2 |
| 8     | [suma.c](LINUX/PUNTO%208/suma.c) | gcc suma.c -o suma | SOLO COMPILAR, NO EJECUTAR, SE EJECUTA DESDE sustitucion_3 |
| 8     | [resta.c](LINUX/PUNTO%208/resta.c) | gcc resta.c -o resta | SOLO COMPILAR, NO EJECUTAR, SE EJECUTA DESDE sustitucion_3 |
| 8     | [multiplicacion.c](LINUX/PUNTO%208/multiplicacion.c) | gcc multiplicacion.c -o multiplicacion | SOLO COMPILAR, NO EJECUTAR, SE EJECUTA DESDE sustitucion_3 |
| 8     | [traspuesta.c](LINUX/PUNTO%208/traspuesta.c) | gcc traspuesta.c -o traspuesta | SOLO COMPILAR, NO EJECUTAR, SE EJECUTA DESDE sustitucion_3 |
| 8     | [inversa.c](LINUX/PUNTO%208/inversa.c) | gcc inversa.c -o inversa | SOLO COMPILAR, NO EJECUTAR, SE EJECUTA DESDE sustitucion_3 |
| 8     | [archivo.c](LINUX/PUNTO%208/archivo.c) | gcc archivo.c -o archivo | SOLO COMPILAR, NO EJECUTAR, SE EJECUTA DESDE sustitucion_3 |
| 8     | [sustitucion_3.c](LINUX/PUNTO%208/sustitucion_3.c) | gcc sustitucion_3.c -o sustitucion_3 | ./sustitucion_3 |

## TABLA: CÓDIGO - PUNTO QUE SOLUCIONA (SECCIÓN WINDOWS 🪟)

✪ Para obtener el tiempo de ejecución de un programa en Windows, utilice `Measure-Command` en PowerShell antes del comando de ejecución del programa. Por ejemplo: `Measure-Command { ./sustitucion_3.exe }`. Esto obtendrá el tiempo de ejecución del programa `sustitucion_3.exe`. Este comando debe ejecutarse forzosamente en PowerShell, ya que no funciona en el símbolo del sistema (cmd).

✪ Se recomienda compilar todos los códigos en Visual Studio Code, pero para la ejecución y capturas de pantalla usar la consola CMD.

✪ Para el punto 3, 4 y 5 primero compile [sustitucion_1.c](WINDOWS/sustitucion_1.c), luego compile [sustitucion_1_1.c](WINDOWS/sustitucion_1_1.c), finalmente ejecute `sustitucion_1.exe sustitucion_1_1.exe`.

✪ Para el punto 7, primero compile [sustitucion_2_3.c](WINDOWS/PUNTO%207/sustitucion_2_3.c), [sustitucion_2_2.c](WINDOWS/PUNTO%207/sustitucion_2_2.c) y [sustitucion_2_1.c](WINDOWS/PUNTO%207/sustitucion_2_1.c). Después de realizar lo anterior, compile [sustitucion_2.c](WINDOWS/PUNTO%207/sustitucion_2.c) y ejecute `sustitucion_2.exe sustitucion_2_1.exe`.

✪ Para el punto 8, primero compile [suma.c](WINDOWS/PUNTO%208/suma.c), [resta.c](WINDOWS/PUNTO%208/resta.c), [multiplicacion.c](WINDOWS/PUNTO%208/multiplicacion.c), [traspuesta.c](WINDOWS/PUNTO%208/traspuesta.c), [inversa.c](WINDOWS/PUNTO%208/inversa.c), y [archivo.c](WINDOWS/PUNTO%208/archivo.c). Luego, compile y ejecute [sustitucion_3.c](WINDOWS/PUNTO%208/sustitucion_3.c).


| PUNTO | NOMBRE DEL CÓDIGO | EJECUCIÓN |
|-------|-------------------|-----------|
| 3     | [sustitucion_1.c](WINDOWS/sustitucion_1.c) | SOLO COMPILAR, NO EJECUTAR, SE EJECUTA MÁS ADELANTE |
| 4     | [sustitucion_1_1.c](WINDOWS/sustitucion_1_1.c) | SOLO COMPILAR, NO EJECUTAR, SE EJECUTA MÁS ADELANTE |
| 5     | [sustitucion_1.c](WINDOWS/sustitucion_1.c) & [sustitucion_1_1.c](WINDOWS/sustitucion_1_1.c) | sustitucion_1.exe sustitucion_1_1.exe  |
| 7     | [sustitucion_2_3.c](WINDOWS/PUNTO%207/sustitucion_2_3.c) | SOLO COMPILAR, NO EJECUTAR, SE EJECUTA DESDE sustitucion_2 |
| 7     | [sustitucion_2_2.c](WINDOWS/PUNTO%207/sustitucion_2_2.c) | SOLO COMPILAR, NO EJECUTAR, SE EJECUTA DESDE sustitucion_2 |
| 7     | [sustitucion_2_1.c](WINDOWS/PUNTO%207/sustitucion_2_1.c) | SOLO COMPILAR, NO EJECUTAR, SE EJECUTA DESDE sustitucion_2 |
| 7     | [sustitucion_2.c](WINDOWS/PUNTO%207/sustitucion_2.c) | sustitucion_2.exe sustitucion_2_1.exe |
| 8     | [suma.c](WINDOWS/PUNTO%208/suma.c) | SOLO COMPILAR, NO EJECUTAR, SE EJECUTA DESDE sustitucion_3 |
| 8     | [resta.c](WINDOWS/PUNTO%208/resta.c) | SOLO COMPILAR, NO EJECUTAR, SE EJECUTA DESDE sustitucion_3 |
| 8     | [multiplicacion.c](WINDOWS/PUNTO%208/multiplicacion.c) | SOLO COMPILAR, NO EJECUTAR, SE EJECUTA DESDE sustitucion_3 |
| 8     | [traspuesta.c](WINDOWS/PUNTO%208/traspuesta.c) | SOLO COMPILAR, NO EJECUTAR, SE EJECUTA DESDE sustitucion_3 |
| 8     | [inversa.c](WINDOWS/PUNTO%208/inversa.c) | SOLO COMPILAR, NO EJECUTAR, SE EJECUTA DESDE sustitucion_3 |
| 8     | [archivo.c](WINDOWS/PUNTO%208/archivo.c) | SOLO COMPILAR, NO EJECUTAR, SE EJECUTA DESDE sustitucion_3 |
| 8     | [sustitucion_3.c](WINDOWS/PUNTO%208/sustitucion_3.c) | sustitucion_3.exe |

## 📝 NOTAS IMPORTANTES

- **PONDERACIÓN**: El [`reporte.pdf`](Unidad2_Practica5_Reporte.pdf) de este repositorio es el documento original presentado al profesor durante el semestre 2024-2. No se incluyen los puntos de corrección ya que la calificación de esta práctica fue 10.

- **CÓDIGOS**: Notará que los códigos en este repositorio pueden diferir de los presentados en las capturas de pantalla del archivo [`reporte.pdf`](Unidad2_Practica5_Reporte.pdf). Estas diferencias se deben a modificaciones realizadas para documentar mejor el código y simplificar el proceso de compilación y ejecución, aunque la funcionalidad es la misma. Se recomienda utilizar las tablas de compilación y ejecución proporcionadas para los códigos de este repositorio. Si intenta copiar los códigos directamente desde [`reporte.pdf`](Unidad2_Practica5_Reporte.pdf), es posible que las instrucciones de compilación y ejecución no le funcionen. Por lo tanto, se sugiere usar los códigos del repositorio. Además, tenga en cuenta que la forma de compilación y ejecución puede no funcionar si cambia el orden de los archivos o las carpetas en comparación con cómo se presentan en este repositorio. Si modifica este orden, es posible que necesite ajustar algunos códigos y métodos de ejecución.

- **ADVERTENCIA**: Se recomienda verificar todos los puntos de la práctica, ya que pueden variar con respecto a su asignación. Ensamble su propio reporte considerando los cambios pertinentes.

</div>
