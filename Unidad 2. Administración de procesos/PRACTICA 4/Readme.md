<div style="text-align: justify">

# PRÁCTICA 4 - PROGRAMACIÓN BAJO EL INTÉRPRETE DE COMANDOS (SHELL) EN LINUX Y WINDOWS

#### ASEGÚRESE DE LEER TODO EL TEXTO ANTES DE COMENZAR CON LA PRÁCTICA

## 🏆 COMPETENCIAS

- **El alumno entenderá lo que es la programación a nivel intérprete de comandos basándose en la creación de controles de flujo mediante las estructuras existentes para este propósito.**
- **El alumno aprenderá a realizar programas sencillos orientados al intérprete de comandos (shell) de Linux y Windows.**

## ✅ DETALLES A CONSIDERAR DE LA PRÁCTICA

#### Se mencionan solo los puntos con recomendaciones importantes. Los demás puntos se consideran intuitivos y muy bien abordados en el [`reporte.pdf`](Unidad2_Practica4_Reporte.pdf).

### 🐧 SECCIÓN LINUX

| PUNTO | DETALLES |
|-------|----------|
| 3 al 10 | Todos los códigos que resuelven estos puntos ya están adaptados para usar rutas relativas. Por lo tanto, no es necesario que modifique ninguna ruta en los códigos; estos funcionarán sin ningún ajuste adicional. |
| 3 al 10 | En el caso de Linux, siempre es necesario cambiar los permisos de los archivos `.sh` para que se puedan ejecutar, por lo que deberá cambiar los permisos de cada uno de los códigos que resuelven estos puntos antes de ejecutarlos. |

### 🪟 SECCIÓN WINDOWS

| PUNTO | DETALLES |
|-------|----------|
| 2 al 6 | Todos los códigos que resuelven estos puntos ya están adaptados para usar rutas relativas. Por lo tanto, no es necesario que modifique ninguna ruta en los códigos; estos funcionarán sin ningún ajuste adicional. |

## 🧑‍💻 CÓDIGOS Y EJECUCIONES

#### Se mencionan los nombres de los códigos, su forma de compilación, cómo se ejecutan y el punto de la asignación que solucionan. Lo anterior se presenta en dos tablas distintas, una para cada sistema operativo.

#### Estas tablas con la forma de compilación y ejecución solo funcionan para los códigos de este repositorio en el orden de archivos y carpetas presentado. Si cambia la ubicación de una carpeta o archivo, la ejecución puede no funcionar como se espera.

#### Siga la guía de compilación y ejecución de estas tablas. NO compile ni ejecute como se muestra en las capturas de pantalla del [`reporte.pdf`](Unidad2_Practica4_Reporte.pdf), ya que los códigos fueron modificados para una ejecución más sencilla.

## TABLA: CÓDIGO - PUNTO QUE SOLUCIONA (SECCIÓN LINUX 🐧)

✪ Para el punto 4, antes de ejecutar el script, cree las carpetas `respaldos`, `directorio1`, `directorio2` y `directorio3`. Cada una de las carpetas `directorio1`, `directorio2` y `directorio3` debe contener un archivo `.txt`, esto con fines de verificar que todos los directorios se comprimen correctamente después de ejecutar el script. El respaldo `.tar` de los directorios se guardará en la carpeta `respaldos`.

✪ Para el punto 7, no es necesario tener la carpeta `descomprimidos` creada antes de ejecutar el script, ya que al ejecutar el script, si la carpeta no existe, se creará automáticamente.

✪ Para el punto 9, ejecute usando `./InfoDirectorio.sh ./`. Esta ejecución devolverá los archivos del mismo directorio en donde está ejecutando el programa, o bien puede cambiar `./` y especificar otro directorio para obtener sus archivos.

✪ Para el punto 10, tiene que tener una carpeta llamada `Eliminar` que contenga algunos archivos que lleven la letra "e" en sus nombres. Posteriormente, ejecute el script y estos archivos se eliminarán. Considere tener archivos que no tengan la letra "e" en sus nombres para que observe cómo solo se eliminan los que llevan la "e" y los que no tienen "e" en el nombre se mantienen.

| PUNTO | NOMBRE DEL CODIGO | CAMBIAR PERMISOS | EJECUCION |
|-------|-------------------|------------------|-----------|
| 3 | [Prueba.sh](./LINUX/Prueba.sh) | chmod +x Prueba.sh | ./Prueba.sh |
| 4 | [Comprimir.sh](./LINUX/Comprimir.sh) | chmod +x Comprimir.sh | ./Comprimir.sh |
| 5 | [Operaciones.sh](./LINUX/Operaciones.sh) | chmod +x Operaciones.sh | ./Operaciones.sh |
| 6 | [Directorio.sh](./LINUX/Directorio.sh) | chmod +x Directorio.sh | ./Directorio.sh |
| 7 | [Descompresion.sh](./LINUX/Descompresion.sh) | chmod +x Descompresion.sh | ./Descompresion.sh |
| 8 | [Generador.sh](./LINUX/Generador.sh) | chmod +x Generador.sh | ./Generador.sh |
| 9 | [InfoDirectorio.sh](./LINUX/InfoDirectorio.sh) | chmod +x InfoDirectorio.sh | ./InfoDirectorio.sh ./ |
| 10 | [Eliminar.sh](./LINUX/Eliminar.sh) | chmod +x Eliminar.sh | ./Eliminar.sh |

## TABLA: CÓDIGO - PUNTO QUE SOLUCIONA (SECCIÓN WINDOWS 🪟)

✪ Para el punto 3, antes de ejecutar el script, cree las carpetas `respaldos`, `directorio1`, `directorio2` y `directorio3`. Cada una de las carpetas `directorio1`, `directorio2` y `directorio3` debe contener un archivo `.txt`, esto con fines de verificar que todos los directorios se comprimen correctamente después de ejecutar el script. El respaldo `.tar` de los directorios se guardará en la carpeta `respaldos`.

✪ Para el punto 6, no es necesario tener la carpeta `descomprimidos` creada antes de ejecutar el script, ya que al ejecutar el script, si la carpeta no existe, se creará automáticamente.

✪ Para el punto 8, ejecute usando `InfoDirectorio.bat ./`. Esta ejecución devolverá los archivos del mismo directorio en donde está ejecutando el programa, o bien puede cambiar `./` y especificar otro directorio para obtener sus archivos.

✪ Para el punto 9, tiene que tener una carpeta llamada `Eliminar` que contenga algunos archivos que lleven la letra "e" en sus nombres. Posteriormente, ejecute el script y estos archivos se eliminarán. Considere tener archivos que no tengan la letra "e" en sus nombres para que observe cómo solo se eliminan los que llevan la "e" y los que no tienen "e" en el nombre se mantienen.

| PUNTO | NOMBRE DEL CODIGO | EJECUCION |
|-------|-------------------|-----------|
| 2 | [Prueba.bat](./WINDOWS/Prueba.bat) | Prueba.bat |
| 3 | [Comprimir.bat](./WINDOWS/Comprimir.bat) | Comprimir.bat |
| 4 | [Operaciones.bat](./WINDOWS/Operaciones.bat) | Operaciones.bat |
| 5 | [Directorio.bat](./WINDOWS/Directorio.bat) | Directorio.bat |
| 6 | [Descompresion.bat](./WINDOWS/Descompresion.bat) | Descompresion.bat |
| 7 | [Generador.bat](./WINDOWS/Generador.bat) | Generador.bat |
| 8 | [InfoDirectorio.bat](./WINDOWS/InfoDirectorio.bat) | InfoDirectorio.bat ./ |
| 9 | [Eliminar.bat](./WINDOWS/Eliminar.bat) | Eliminar.bat |

## 📝 NOTAS IMPORTANTES

- **PONDERACIÓN**: El [`reporte.pdf`](Unidad2_Practica4_Reporte.pdf) de este repositorio es el documento original presentado al profesor durante el semestre 2024-2. No se incluyen los puntos de corrección ya que la calificación de esta práctica fue 10.

- **CÓDIGOS**: Notará que los códigos en este repositorio pueden diferir de los presentados en las capturas de pantalla del archivo [`reporte.pdf`](Unidad2_Practica4_Reporte.pdf). Estas diferencias se deben a modificaciones realizadas para documentar mejor el código y simplificar el proceso de compilación y ejecución, aunque la funcionalidad es la misma. Se recomienda utilizar las tablas de compilación y ejecución proporcionadas para los códigos de este repositorio. Si intenta copiar los códigos directamente desde [`reporte.pdf`](Unidad2_Practica4_Reporte.pdf), es posible que las instrucciones de compilación y ejecución no le funcionen. Por lo tanto, se sugiere usar los códigos del repositorio. Además, tenga en cuenta que la forma de compilación y ejecución puede no funcionar si cambia el orden de los archivos o las carpetas en comparación con cómo se presentan en este repositorio. Si modifica este orden, es posible que necesite ajustar algunos códigos y métodos de ejecución.

- **ADVERTENCIA**: Se recomienda verificar todos los puntos de la práctica con cuidado. Para cada uno de los códigos, verifique que el comportamiento del mismo sea correcto y ajuste si es necesario. Cualquier error de ejecución en los códigos puede ser resultado de cambios en las rutas o el orden de ejecución.

</div>
