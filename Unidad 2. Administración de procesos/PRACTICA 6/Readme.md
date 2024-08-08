<div style="text-align: justify">

# PRÁCTICA 6 - ADMINISTRADOR DE PROCESOS EN LINUX Y WINDOWS (2)

#### ASEGÚRESE DE LEER TODO EL TEXTO ANTES DE COMENZAR CON LA PRÁCTICA

## 🏆 COMPETENCIA

- **El alumno aprende a familiarizarse con el administrador de procesos del sistema operativo Linux y Windows a través de la creación de procesos ligeros (hilos) para el desarrollo de aplicaciones concurrentes sencillas.**

## ✅ DETALLES A CONSIDERAR DE LA PRÁCTICA

#### No se mencionan puntos con recomendaciones, ya que todos se consideran intuitivos y están bien abordados en el [`reporte.pdf`](Unidad2_Practica6_Reporte.pdf). Sin embargo, hay algunas sugerencias en la sección de código - punto que soluciona.

## 🧑‍💻 CÓDIGOS Y EJECUCIONES

#### Se mencionan los nombres de los códigos, su forma de compilación, cómo se ejecutan y el punto de la asignación que solucionan. Lo anterior se presenta en dos tablas distintas, una para cada sistema operativo.

#### Estas tablas con la forma de compilación y ejecución solo funcionan para los códigos de este repositorio en el orden de archivos y carpetas presentado. Si cambia la ubicación de una carpeta o archivo, la ejecución puede no funcionar como se espera.

#### Siga la guía de compilación y ejecución de estas tablas. NO compile ni ejecute como se muestra en las capturas de pantalla del [`reporte.pdf`](Unidad2_Practica6_Reporte.pdf), ya que los códigos fueron modificados para una ejecución más sencilla.

## TABLA: CÓDIGO - PUNTO QUE SOLUCIONA (SECCIÓN LINUX 🐧)

✪ Para obtener el tiempo de ejecución de un programa, utilice `time` antes del comando de ejecución del programa. Por ejemplo: `time ./hilos_4`. Esto obtendrá el tiempo de ejecución del programa `hilos_4`.

✪ En algunos puntos de esta práctica, le solicitarán comparar los tiempos de ejecución de los programas usando hilos con programas de prácticas anteriores. Se recomienda ejecutar varias veces el programa de hilos hasta obtener el tiempo más bajo posible; de manera similar, ejecute varias veces el programa con el que lo está comparando hasta obtener el tiempo más alto posible. Esto se menciona porque esta práctica intenta demostrar que el programa de hilos es significativamente más rápido. Dado que los tiempos de ambos programas pueden acercarse mucho, es importante ejecutar ambos varios veces para obtener una diferencia notable, donde el programa de hilos tenga un tiempo de ejecución menor y el otro, un tiempo mayor.

| PUNTO | NOMBRE DEL CÓDIGO | COMPILACION | EJECUCION |
|-------|-------------------|-------------|-----------|
| 2     | [hilos_1.c](LINUX/hilos_1.c) | gcc hilos_1.c -o hilos_1 | ./hilos_1 |
| 3     | [hilos_2.c](LINUX/hilos_2.c) | gcc hilos_2.c -o hilos_2 | ./hilos_2 |
| 6     | [hilos_3.c](LINUX/hilos_3.c) | gcc hilos_3.c -o hilos_3 | ./hilos_3 |
| 7     | [hilos_4.c](LINUX/hilos_4.c) | gcc hilos_4.c -o hilos_4 | ./hilos_4 |

## TABLA: CÓDIGO - PUNTO QUE SOLUCIONA (SECCIÓN WINDOWS 🪟)

✪ Para obtener el tiempo de ejecución de un programa en Windows, utilice `Measure-Command` en PowerShell antes del comando de ejecución del programa. Por ejemplo: `Measure-Command { ./sustitucion_3.exe }`. Esto obtendrá el tiempo de ejecución del programa `sustitucion_3.exe`. Este comando debe ejecutarse forzosamente en PowerShell, ya que no funciona en el símbolo del sistema (cmd).

✪ Se recomienda compilar todos los códigos en Visual Studio Code, pero para la ejecución y capturas de pantalla usar la consola CMD.

✪ En algunos puntos de esta práctica, le solicitarán comparar los tiempos de ejecución de los programas usando hilos con programas de prácticas anteriores. Se recomienda ejecutar varias veces el programa de hilos hasta obtener el tiempo más bajo posible; de manera similar, ejecute varias veces el programa con el que lo está comparando hasta obtener el tiempo más alto posible. Esto se menciona porque esta práctica intenta demostrar que el programa de hilos es significativamente más rápido. Dado que los tiempos de ambos programas pueden acercarse mucho, es importante ejecutar ambos varios veces para obtener una diferencia notable, donde el programa de hilos tenga un tiempo de ejecución menor y el otro, un tiempo mayor.

✪ Para el punto 6, primero compile [hilos_2_1.c](WINDOWS/hilos_2_1.c). Después de realizar lo anterior, compile [hilos_2.c](WINDOWS/hilos_2.c) y ejecute `hilos_2.exe hilos_2_1.exe`.

| PUNTO | NOMBRE DEL CÓDIGO | EJECUCIÓN |
|-------|-------------------|-----------|
| 5     | [hilos_1.c](WINDOWS/hilos_1.c) | hilos_1.exe |
| 6     | [hilos_2_1.c](WINDOWS/hilos_2_1.c) | SOLO COMPILAR, NO EJECUTAR, SE EJECUTA DESDE hilos_2 |
| 6     | [hilos_2.c](WINDOWS/hilos_2.c) | hilos_2.exe hilos_2_1.exe |
| 7     | [hilos_3.c](WINDOWS/hilos_3.c) | hilos_3.exe |

## 📝 NOTAS IMPORTANTES

- **PONDERACIÓN**: El [`reporte.pdf`](Unidad2_Practica6_Reporte.pdf) de este repositorio es el documento original presentado al profesor durante el semestre 2024-2. No se incluyen los puntos de corrección ya que la calificación de esta práctica fue 10.

- **CÓDIGOS**: Notará que los códigos en este repositorio pueden diferir de los presentados en las capturas de pantalla del archivo [`reporte.pdf`](Unidad2_Practica6_Reporte.pdf). Estas diferencias se deben a modificaciones realizadas para documentar mejor el código y simplificar el proceso de compilación y ejecución, aunque la funcionalidad es la misma. Se recomienda utilizar las tablas de compilación y ejecución proporcionadas para los códigos de este repositorio. Si intenta copiar los códigos directamente desde [`reporte.pdf`](Unidad2_Practica6_Reporte.pdf), es posible que las instrucciones de compilación y ejecución no le funcionen. Por lo tanto, se sugiere usar los códigos del repositorio. Además, tenga en cuenta que la forma de compilación y ejecución puede no funcionar si cambia el orden de los archivos o las carpetas en comparación con cómo se presentan en este repositorio. Si modifica este orden, es posible que necesite ajustar algunos códigos y métodos de ejecución.

- **ADVERTENCIA**: Se recomienda verificar todos los puntos de la práctica, ya que pueden variar con respecto a su asignación. Ensamble su propio reporte considerando los cambios pertinentes.

</div>