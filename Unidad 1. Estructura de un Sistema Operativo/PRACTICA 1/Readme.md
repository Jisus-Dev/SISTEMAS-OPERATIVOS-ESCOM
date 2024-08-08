<div style="text-align: justify">

# PRÁCTICA 1 - INTRODUCCIÓN A LOS SISTEMAS OPERATIVOS

#### ASEGÚRESE DE LEER TODO EL TEXTO ANTES DE COMENZAR CON LA PRÁCTICA

## 🏆 COMPETENCIAS

- **El alumno analiza los sistemas operativos Linux y Windows utilizando sus interfaces de comandos para comparar sus características principales y diferenciarlos en su ambiente de trabajo.**
- **El alumno desarrolla aplicaciones en lenguaje C para los sistemas operativos Linux y Windows.**

## ✅ DETALLES A CONSIDERAR DE LA PRÁCTICA

#### Se mencionan solo los puntos con recomendaciones importantes. Los demás puntos se consideran intuitivos y muy bien abordados en el [`reporte.pdf`](Unidad1_Practica1_Reporte.pdf).

### 🐧 SECCIÓN LINUX

| PUNTO | DETALLES |
|-------|----------|
| 1     | Considere cambiar la información de este punto por la de su distribución y versión. |
| 11    | Se recomienda utilizar una carpeta compartida entre el sistema operativo base y la máquina virtual en lugar de un USB, ya que es más fácil de manejar y será útil para las prácticas futuras. Si su máquina virtual es Linux y su sistema operativo base es Windows, puede consultar este video [CLIC](https://www.youtube.com/watch?v=Mzd5i48OAiU) u otro tutorial para crear la carpeta compartida. |

### 🪟 SECCIÓN WINDOWS

| PUNTO | DETALLES |
|-------|----------|
| 4     | Se recomienda utilizar una carpeta compartida en lugar de un USB como ya se mencionó anteriormente. |
| 5     | Se recomienda configurar Visual Studio Code para ejecutar C. Vea este video: [CLIC](https://www.youtube.com/watch?v=v3ENcQpoA5A), o busque otro para realizar este proceso. |
| 6 y 7 | Con Visual Studio Code configurado para ejecutar C, puede hacer clic en el botón de ejecutar en la parte superior derecha y simplificar los puntos 6 y 7 de la asignación. Guíese con el video recomendado anteriormente. Configurar C en Visual Studio puede ser complicado, pero una vez configurado, lo agradecerá en todas las prácticas restantes por su facilidad de uso y compilación en comparación con la forma de compilar y ejecutar que recomienda la práctica. |

## 🧑‍💻 CÓDIGOS Y EJECUCIONES

#### Se mencionan los nombres de los códigos, su forma de compilación, cómo se ejecutan y el punto de la asignación que solucionan. Lo anterior se presenta en dos tablas distintas, una para cada sistema operativo.

#### Estas tablas con la forma de compilación y ejecución solo funcionan para los códigos de este repositorio en el orden de archivos y carpetas presentado. Si cambia la ubicación de una carpeta o archivo, la ejecución puede no funcionar como se espera.

#### Siga la guía de compilación y ejecución de estas tablas. NO compile ni ejecute como se muestra en las capturas de pantalla del [`reporte.pdf`](Unidad1_Practica1_Reporte.pdf), ya que los códigos fueron modificados para una ejecución más sencilla.

## TABLA: CÓDIGO - PUNTO QUE SOLUCIONA (SECCIÓN LINUX 🐧)

| PUNTO | NOMBRE DEL CÓDIGO | COMPILACIÓN | EJECUCIÓN |
|-------|-------------------|-------------|-----------|
| 6     | [holamundo.c](LINUX/holamundo.c)       | gcc holamundo.c -o holamundo  | ./holamundo |
| 7     | [asteriscos.c](LINUX/asteriscos.c)      | gcc asteriscos.c -o asteriscos | ./asteriscos |
| 8     | [hanoi.c](LINUX/hanoi.c)           | gcc hanoi.c -o hanoi          | ./hanoi     |
| 9     | [balanceo.c](LINUX/balanceo.c)        | gcc balanceo.c -o balanceo    | ./balanceo  |
| 10    | [expresion.c](LINUX/expresion.c)       | gcc expresion.c -o expresion  | ./expresion |

## TABLA: CÓDIGO - PUNTO QUE SOLUCIONA (SECCIÓN WINDOWS 🪟)

✪ Se recomienda compilar todos los códigos en Visual Studio Code como ya se mencionó anteriormente, pero para la ejecución y captura de pantalla usar la consola CMD.

| PUNTO | NOMBRE DEL CÓDIGO | EJECUCIÓN |
|-------|-------------------|-----------|
| 7     | [holamundo.c](WINDOWS/holamundo.c) | holamundo.exe |
| 7     | [asteriscos.c](WINDOWS/asteriscos.c) | asteriscos.exe |
| 7     | [hanoi.c](WINDOWS/hanoi.c) | hanoi.exe |
| 7     | [balanceo.c](WINDOWS/balanceo.c) | balanceo.exe |
| 7     | [expresion.c](WINDOWS/expresion.c) | expresion.exe |

## 📝 NOTAS IMPORTANTES

- **PONDERACIÓN**: El [`reporte.pdf`](Unidad1_Practica1_Reporte.pdf) de este repositorio es el documento original presentado al profesor durante el semestre 2024-2. Se incluyen los puntos de corrección basados en la retroalimentación dada por el profesor, ya que la calificación de esta práctica fue 9; las correcciones necesarias para obtener una calificación de 10 son mínimas y se mencionan en el siguiente punto.

- **CORRECCIÓN**: En el reporte de esta práctica, las conclusiones se realizaron de forma individual por cada miembro del equipo. Sin embargo, las conclusiones deben ser realizadas en equipo; es decir, debe presentarse una sola conclusión por todo el equipo.

- **CÓDIGOS**: Notará que los códigos en este repositorio pueden diferir de los presentados en las capturas de pantalla del archivo [`reporte.pdf`](Unidad1_Practica1_Reporte.pdf). Estas diferencias se deben a modificaciones realizadas para documentar mejor el código y simplificar el proceso de compilación y ejecución, aunque la funcionalidad es la misma. Se recomienda utilizar las tablas de compilación y ejecución proporcionadas para los códigos de este repositorio. Si intenta copiar los códigos directamente desde [`reporte.pdf`](Unidad1_Practica1_Reporte.pdf), es posible que las instrucciones de compilación y ejecución no le funcionen. Por lo tanto, se sugiere usar los códigos del repositorio. Además, tenga en cuenta que la forma de compilación y ejecución puede no funcionar si cambia el orden de los archivos o las carpetas en comparación con cómo se presentan en este repositorio. Si modifica este orden, es posible que necesite ajustar algunos códigos y métodos de ejecución.

- **ADVERTENCIA**: Se recomienda verificar todos los puntos de la práctica, ya que pueden variar con respecto a su asignación. Ensamble su propio reporte considerando los cambios pertinentes.

</div>