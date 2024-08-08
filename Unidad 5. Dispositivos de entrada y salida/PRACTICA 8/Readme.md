<div style="text-align: justify">

# PRÁCTICA 8 - MECANISMOS DE SINCRONIZACIÓN DE PROCESOS EN LINUX Y WINDOWS (SEMÁFOROS)

#### ASEGÚRESE DE LEER TODO EL TEXTO ANTES DE COMENZAR CON LA PRÁCTICA

## 🏆 COMPETENCIA

- **El alumno comprende el funcionamiento de los mecanismos de sincronización entre procesos cooperativos utilizando los semáforos como árbitros de acceso para el desarrollo de aplicaciones cooperativas tanto en el sistema operativo Linux como Windows.**

## ✅ DETALLES A CONSIDERAR DE LA PRÁCTICA

#### No se mencionan puntos con recomendaciones, ya que todos se consideran intuitivos y están bien abordados en el [`reporte.pdf`](Unidad5_Práctica8_Reporte.pdf). Sin embargo, hay algunas sugerencias en la sección de código - punto que soluciona.

## 🧑‍💻 CÓDIGOS Y EJECUCIONES

#### Se mencionan los nombres de los códigos, su forma de compilación, cómo se ejecutan y el punto de la asignación que solucionan. Lo anterior se presenta en dos tablas distintas, una para cada sistema operativo.

#### Estas tablas con la forma de compilación y ejecución solo funcionan para los códigos de este repositorio en el orden de archivos y carpetas presentado. Si cambia la ubicación de una carpeta o archivo, la ejecución puede no funcionar como se espera.

#### Siga la guía de compilación y ejecución de estas tablas. NO compile ni ejecute como se muestra en las capturas de pantalla del [`reporte.pdf`](Unidad5_Práctica8_Reporte.pdf), ya que los códigos fueron modificados para una ejecución más sencilla.

## TABLA: CÓDIGO - PUNTO QUE SOLUCIONA (SECCIÓN LINUX 🐧)

✪ Sin sugerencias, solo siga las instrucciones de la tabla.

| PUNTO | NOMBRE DEL CODIGO | COMPILACION | EJECUCION |
|-------|-------------------|-------------|-----------|
| 2     | [semaforos_1.c](LINUX/semaforos_1.c) | gcc semaforos_1.c -o semaforos_1 | ./semaforos_1 |
| 5     | [semaforos_2.c](LINUX/semaforos_2.c) | gcc semaforos_2.c -o semaforos_2 | ./semaforos_2 |
| 6     | [semaforos_3.c](LINUX/semaforos_3.c) | gcc semaforos_3.c -o semaforos_3 | ./semaforos_3 |

## TABLA: CÓDIGO - PUNTO QUE SOLUCIONA (SECCIÓN WINDOWS 🪟)

✪ Se recomienda compilar todos los códigos en Visual Studio Code, pero para la ejecución y capturas de pantalla usar la consola CMD.

✪ Para el punto 4, primero compile [`hijo.c`](WINDOWS/hijo.c), luego compile [`padre.c`](WINDOWS/padre.c) y ejecute `padre.exe hijo.exe`.

✪ Para el punto 5, primero compile [`memoria_3.c`](WINDOWS/Punto%205/memoria_3.c) y [`memoria_2.c`](WINDOWS/Punto%205/memoria_2.c), luego compile [`memoria_1.c`](WINDOWS/Punto%205/memoria_1.c) y ejecute `memoria_1.exe memoria_2.exe`.

✪ Para el punto 6, primero compile [`suma.c`](WINDOWS/Punto%206/suma.c), [`resta.c`](WINDOWS/Punto%206/resta.c), [`multiplicacion.c`](WINDOWS/Punto%206/multiplicacion.c), [`traspuesta.c`](WINDOWS/Punto%206/traspuesta.c), [`inversa.c`](WINDOWS/Punto%206/inversa.c), y [`recoleccion.c`](WINDOWS/Punto%206/recoleccion.c). Finalmente, compile y ejecute [`padre.c`](WINDOWS/Punto%206/padre.c).

| PUNTO | NOMBRE DEL CÓDIGO | EJECUCIÓN |
|-------|-------------------|-----------|
| 4     | [hijo.c](WINDOWS/hijo.c) | SOLO COMPILAR, NO EJECUTAR, SE EJECUTA DESDE padre |
| 4     | [padre.c](WINDOWS/padre.c) | padre.exe hijo.exe |
| 5     | [memoria_3.c](WINDOWS/Punto%205/memoria_3.c) | SOLO COMPILAR, NO EJECUTAR, SE EJECUTA DESDE memoria_1 |
| 5     | [memoria_2.c](WINDOWS/Punto%205/memoria_2.c) | SOLO COMPILAR, NO EJECUTAR, SE EJECUTA DESDE memoria_1 |
| 5     | [memoria_1.c](WINDOWS/Punto%205/memoria_1.c) | memoria_1.exe memoria_2.exe |
| 6     | [suma.c](WINDOWS/Punto%206/suma.c) | SOLO COMPILAR, NO EJECUTAR, SE EJECUTA DESDE padre |
| 6     | [resta.c](WINDOWS/Punto%206/resta.c) | SOLO COMPILAR, NO EJECUTAR, SE EJECUTA DESDE padre |
| 6     | [multiplicacion.c](WINDOWS/Punto%206/multiplicacion.c) | SOLO COMPILAR, NO EJECUTAR, SE EJECUTA DESDE padre |
| 6     | [traspuesta.c](WINDOWS/Punto%206/traspuesta.c) | SOLO COMPILAR, NO EJECUTAR, SE EJECUTA DESDE padre |
| 6     | [inversa.c](WINDOWS/Punto%206/inversa.c) | SOLO COMPILAR, NO EJECUTAR, SE EJECUTA DESDE padre |
| 6     | [recoleccion.c](WINDOWS/Punto%206/recoleccion.c) | SOLO COMPILAR, NO EJECUTAR, SE EJECUTA DESDE padre |
| 6     | [padre.c](WINDOWS/Punto%206/padre.c) | padre.exe |

## 📝 NOTAS IMPORTANTES

- **PONDERACIÓN**: El [`reporte.pdf`](Unidad5_Práctica8_Reporte.pdf) de este repositorio es el documento original presentado al profesor durante el semestre 2024-2. No se incluyen los puntos de corrección ya que la calificación de esta práctica fue 10.

- **CÓDIGOS**: Notará que los códigos en este repositorio pueden diferir de los presentados en las capturas de pantalla del archivo [`reporte.pdf`](Unidad5_Práctica8_Reporte.pdf). Estas diferencias se deben a modificaciones realizadas para documentar mejor el código y simplificar el proceso de compilación y ejecución, aunque la funcionalidad es la misma. Se recomienda utilizar las tablas de compilación y ejecución proporcionadas para los códigos de este repositorio. Si intenta copiar los códigos directamente desde [`reporte.pdf`](Unidad5_Práctica8_Reporte.pdf), es posible que las instrucciones de compilación y ejecución no le funcionen. Por lo tanto, se sugiere usar los códigos del repositorio. Además, tenga en cuenta que la forma de compilación y ejecución puede no funcionar si cambia el orden de los archivos o las carpetas en comparación con cómo se presentan en este repositorio. Si modifica este orden, es posible que necesite ajustar algunos códigos y métodos de ejecución.

- **ADVERTENCIA**: Se recomienda verificar todos los puntos de la práctica, ya que pueden variar con respecto a su asignación. Ensamble su propio reporte considerando los cambios pertinentes.

</div>