# MyShellBasic
## Instalación
Para instalar el programa en primer lugar se debe clonar el repositorio. Para esto se debe ejecutar el siguiente comando desde el directorio deseado:
```bash
git clone https://github.com/ICOMP-UNC/soi---2022---laboratorio-4-JerePasolli.git            
```
O bien descargar el archivo zip desde GitHub.

Luego se debe ejecutar el siguiente comando desde el directorio del proyecto:
```bash
make            
```
Con esto el programa estará listo para ejecutarse.

## Ejecución
Hay dos formas de ejecutar MyShell: se puede ejecutar el binario generado por el comando make (myshell), ubicado en la carpeta bin del proyecto, de la siguiente manera:
```bash
./bin/myshell            
```
Lo que ejecutará MyShell dentro de la shell desde la cual se escribió el comando. Para evitar confusiones, MyShell contiene colores en su prompt que lo diferencian de la shell típica de linux, como se ve en la siguiente imagen:

![Screenshot from 2022-10-01 16-51-53](https://user-images.githubusercontent.com/65351453/193426171-527432e7-4418-473d-a5f0-ebb268e1e77a.png)

Otra posibilidad es la de ejecutar el programa utilizando el launcher que se encuentra en el directorio del proyecto, de la siguiente forma:
```bash
sh ./launcher.sh
            
```
Esto abrirá una nueva ventana, para poder ejecutar MyShell de forma independiente.

Cabe aclarar que este launcher solo funcionará si su distribución de linux utiliza el entorno de escritorio GNOME, de lo contrario se debe utilizar el método mencionado previamente.

## Comandos internos
MyShell cuenta con los siguientes comandos incorporados:

- echo <Message/$env>

    Imprime por pantalla el mensaje, en caso de colocar $, se interpretará como una variable de entorno y se imprimirá en pantalla su contenido (si existe).
- cd <directory>

    Cambia al directorio indicado, actualizando los valores de las variables de entorno PWD y OLDPWD. En caso de que no se indique un path, se cambiará al directorio /home/username.
- clr

    Limpia la consola

- quit
    
    Termina la ejecución de MyShell

## Programas externos
Si se ingresa un comando que no se corresponda con ninguno interno, se interpretará que se desea lanzar un programa. Para esto, se debe proveer el path del programa (relativo o absoluto) y los argumentos si así se lo desea. 

Si no se indica el path, MyShell buscará el programa en el directorio "/bin/".

### Ejecución en background
Si al intentar ejecutar un programa externo se coloca el caracter '&' al final del comando este se ejecutará en background. Al lanzarse en background la terminal indicará su id de trabajo y su pid de la siguiente forma:
```bash
[jobId]pid           
```
## Ejecución de instrucciones desde archivo de texto
Si se desea ejecutar un set de instrucciones desde un archivo de texto, este se debe pasar como parámetro al ejecutar MyShell, de la siguiente manera:
```bash
./bin/myshell batchfile           
```
Donde batchfile corresponde al archivo de texto que se desee leer. Se debe colocar una instruccion por linea.

Al terminar de ejecutar las instrucciones, MyShell finalizará su ejecución.

Se provee un batchfile a modo de ejemplo.

## Soporte de comandos ctrl-c, ctrl-z y ctrl-|
Se puede ingresar cualquiera de estas combinaciones de teclas para abortar o pausar procesos en ejecución en MyShell.

## Pipes
Se soporta el uso de pipes (el caracter "|") para "encadenar procesos", utilizando la stdout de uno como stdin del siguiente, y asi sucesivamente. Por ejemplo:
```bash
ls | grep .txt           
```
Correrá el comando "ls", y la salida que este genere será enviada al comando "grep" como entrada. En el caso del ejemplo, el comando "grep" filtrará los archivos que contengan la cadena ".txt" de los elementos listados por "ls".

## Redirección de entrada y salida
Se puede redireccionar la entrada, la salida o ambos de un programa. Por defecto, la entrada de un programa son los caracteres ingresados por teclado por el usuario, y la terminal es la salida. Con esta funcionalidad, podemos cambiar este comportamiento, pudiendo hacer que un programa tome como entrada el texto de un archivo, por ejemplo, o bien pedirle que escriba la salida en un archivo. Por ejemplo:
```bash
ls > outputfile.txt          
```
Generará que los resultados del comando ls se escriban en el archivo de nombre outputfile.txt. En caso de que este no exista se creará. En caso de que el archivo contuviera texto, este se sobreescribirá. Para el caso de redirección de entrada, el archivo elegido como entrada debe existir, de lo contrario el comando será inválido.


## Bugs y limitaciones
- Al ejecutar un programa externo se soporta un pasaje de 5 argumentos como máximo.
- El programa funciona únicamente en distribuciones de GNU/linux.
- Para indicar los path y las distintas instrucciones para los comandos se soporta un máximo de 300 caracteres.
- Para el caso de pipes, se soporta un máximo de 5 procesos (es decir 4 pipes).



