#### 4. Cuestionario

  4.1. ¿Cuáles son los tipos de _type descriptors_ que podemos encontrar en _/proc/<id>/fd_?
  pag 181 del libro de linux

  En la carpeta fd correspondiente a cada proceso (/proc/id/fd) encontramos los file descriptors de ese proceso en cuestión. Estos son identificadores o "links simbolicos" unicos para un archivo, o recurso de entrada/salida que el proceso ha abierto. Tipicamente estos identificadores tienen numeros enteros no negativos, ya que los valores negativos estan reservados para indicar que "no ahy valor" o condiciones de error.
  
Segun se menciona en el manual de Standar I/O, al inciarse un programa tiene 3 "streams" abiertos por defecto, uno para entrada (standard input), otro para salida (standard output), y otro para imprimir mensajes de error (standard error). Al iniciarse el programa, se asocian file descriptors a estos "streams" de la siguiente manera: 0 para stdin, 1 para stdout y 2 para stderr.
  
Ademas, cada proceso tendra otros file descriptors asociados a archivos que el proceso este utilizando.
  
Por ejemplo, si abrimos la carpeta "/proc/5026/fd" correspondiente a una pestaña de Chrome, veremos los siguiente file descriptors (y mas aún, en la imagen no estan todos):
  
![Screenshot from 2022-09-09 09-49-13](https://user-images.githubusercontent.com/65351453/189353670-d78ef6a5-d035-42dd-b19d-786849eb0c53.png)

  
  4.2. Suponiendo que un usuario está ejecutando el proceso _pid 1212_, ¿Es válida la ejecución del siguiente comando desde una terminal nueva?
_% echo “Hello, world.” >> /proc/1212/fd/1_
  
  Es valida, ya que desde la nueva terminal lo que estaríamos haciendo es escribir el mensaje en el standard output del otro proceso, al cual accedemos desde el file descriptor 1. Por ejemplo, podemos hacer esto con el proceso "cat". Si ejecutamos en una terminal el comando "cat", y luego desde otra terminal ejecutamos el comando echo “Hello, world.” >> /proc/11247/fd/1_, veremos como desde la primera terminal se imprime el mensaje, ya que lo escribimos en el standard output del proceso cat.
  
  ![image](https://user-images.githubusercontent.com/65351453/189358492-c64295a0-ccf4-49a4-97cc-439fc70314d9.png)
  
  ![image](https://user-images.githubusercontent.com/65351453/189358438-ed27f292-34e9-42a7-841e-71f65cf07583.png)
  
  4.3. Qué diferencia hay entre _hard_ y _soft limits_?

Los "limits" son numeros que identifican limitaciones para el acceso de distintos usuarios a determinados recursos del sistema, tales como memoria, procesador, disco duro, entre otros.
Un "hard limit" es un limite "tope" que el usuario nunca puede sobrepasar. Por ejemplo, si tenemos un hard limit de 10 procesos por cada usuario, ninguno puede sobrepasar ese limite.
Por otro lado, un "soft limit" es un limite de "advertencia". Indica al usuario y al administrador del sistema que se esta cerca de alcanzar un nivel peligroso, es decir el hard limit. En este caso, los usuarios pueden sobrepasar este soft limit, a diferencia del hard limit.
Los usuarios comunes pueden aumentar sus soft limits hasta alcanzar el valor del hard limit. Tambien pueden reducir su soft limit.
Ademas, pueden reducir su hard limit, pero no aumentarlo.
El usuario "root" en cambio, puede modificar a su antojo ambos limits.
