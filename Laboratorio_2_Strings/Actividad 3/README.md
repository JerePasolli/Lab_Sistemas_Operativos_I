**¿Cómo utilizar typedef junto a struct? ¿Para qué sirve? Ejemplo.**

   La palabra typedef nos permite crear sinónimos o alias para tipos de datos. Justamente este es el uso que se le da en el caso de las estructuras, ya que creamos un sinónimo para la estructura.
   Por ejemplo:
   
![image](https://user-images.githubusercontent.com/65351453/186173077-5ae5024c-9968-4531-a158-04b8e424258b.png)

   Aquí tenemos la misma estructura en ambos casos, la primera declarada sin el uso de typedef, y la segunda con el uso de esta palabra clave. La segunda nos permite inicializar la estructura mediante el alias que definimos, es decir "Persona", mientras que en el caso de la primera esto no se puede hacer. A continuación se muestra un ejemplo de inicialización de ambas:

   Primera estructura:

![image](https://user-images.githubusercontent.com/65351453/186173292-79693f1d-ee85-4d6a-962c-5ca04bddc762.png)

   Segunda estructura:

![image](https://user-images.githubusercontent.com/65351453/186173378-9fe25ae4-fba4-4979-816f-641063dde09c.png)

**¿Qué es packing and padding?**

   El relleno de memoria o padding en inglés consiste en agregar algunos bytes de memoria extra al guardar datos de una estructura en memoria, con el objetivo de que el CPU pueda acceder a los datos rápidamente (debido a que el CPU no lee 1 byte a la vez, sino que lee 4 bytes por ciclo en sistemas de 32 bits y hasta 8 bytes por ciclo en sistemas de 64 bits). Por esto, el compilador alineará los datos en la memoria, haciendo bloques de 4 u 8 bytes de memoria según las variables de la estructura y la arquitectura del sistema, tomando el tipo de dato más grande (mayor cantidad de bytes) y reservando bloques de ese tamaño en la memoria. Lógicamente, esto generara espacios con "basura" en memoria, pero con  la ventaja de que los datos esten "alineados". En resumen, estaremos utilizando memoria innecesaria, pero con el beneficio de obtener un acceso más veloz a los datos. Por ejemplo:

![image](https://user-images.githubusercontent.com/65351453/186173544-7345b671-c1fe-48bf-a031-269f815e5569.png)

   Al reservar memoria para esta estructura, el compilador reservará 2 bloques de 8 bytes (ya que la variable de mayor tamaño tiene 8 bytes) de memoria, para así alinear los datos. En el primer bloque colocará las variables "a" y "b", mientras que en el segundo la variable "c", ocupando así 16 bytes en total (3 bytes extra). En la siguiente imagen se ilustra como se da esto:

![Screenshot from 2022-08-23 10-32-51](https://user-images.githubusercontent.com/65351453/186171525-0002ed41-29ed-439b-9192-a4b218323194.png)

   Por otro lado, el empaquetado o packing consiste en evitar este consumo extra de memoria, utilizando solo la memoria necesaria para cada variable, sin consumo extra para la alineación de datos. Lógicamente, la desventaja de esto es que perdemos el rápido acceso a los datos que teníamos con el padding, pero ahorramos memoria. Para que el compilador tenga este comportamiento, debemos explicitarlo en el código, ya que por defecto hará padding. Para indicarle esto al compilador debemos agregar en el encabezao del código la siguiente sentencia:

#pragma pack(1)

   O bien agregar a la definici+on de la estructura lo siguiente:

__attribute__((packed))

   Si utilizamos packing en la estructura del ejemplo anterior se utilizarán 13 bytes de memoria (1 del char + 4 del int + 8 del double), es decir 3 bytes menos que utilizando padding. En la memoria sucederá lo siguiente:

![image](https://user-images.githubusercontent.com/65351453/186173919-fa2b6f1d-baab-4503-aef3-05cbba6fcf63.png)

**Explique a que se debe los tamanios de cada una de las estructuras (archivo lab2.c)**

**Estructura BaseData:**

   Dado que la variable de mayor tamaño es de tipo int, se reservarán bloques de 4 bytes en memoria, por lo tanto tendremos 5 bloques de 4 bytes (20 bytes ocupados), de la siguiente manera:
   
   ![image](https://user-images.githubusercontent.com/65351453/186180176-2ff7aebf-2f7f-4e51-beae-ee68803c310e.png)

**Estructura ReorderData:**

   Dado que la variable de mayor tamaño es de tipo int, se reservarán bloques de 4 bytes en memoria, pero en este caso el orden de declaración de las variables es distinto, generando así 4 bloques de 4 bytes (16 bytes ocupados) que se organizarán de la siguiente manera:
   
   ![image](https://user-images.githubusercontent.com/65351453/186180343-0368799e-e7d1-40ed-ae8b-0bec5b358648.png)

**Estructura ExtendedData:**

   Dado que la variable de mayor tamaño es de tipo long int, se reservarán bloques de 8 bytes en memoria, teniendo en este caso 3 bloques de 8 bytes de memoria (24 bytes ocupados), de la siguiente manera:
   
   ![image](https://user-images.githubusercontent.com/65351453/186181248-0eb48fe0-2c3c-4653-bd1e-634532a140d7.png)

   En este caso no se desperdicio memoria con basura.
   
**Estructura BaseDataPacked:**

   En este último caso se aplica packing, por lo que se utilizara solo la memoria necesaria, sin rellenar con basura para alinear, por lo que tendremos:
   
   ![image](https://user-images.githubusercontent.com/65351453/186182358-74881ec3-6abb-435e-88f8-271d32f747c3.png)

**Explique por que las expresiones que calculan  limit y limit_aux generan el mismo resutado
hint : investigar sobre reglas de aritmetica de punteros**

![image](https://user-images.githubusercontent.com/65351453/186182674-2929ea00-219e-4f3c-a5bf-dd951f541102.png)

   En este primer caso, al puntero "limit" se le pasa el resultado de sumarle a la dirección de memoria de "data" el tamaño de la estructura "BaseData", que es de 20 bytes, como ya sabemos.
   
![image](https://user-images.githubusercontent.com/65351453/186182922-dee5cbee-836a-4dc3-92f2-cabff4da6c13.png)

   En este otro caso, si bien la sintaxis es diferente, tendremos el mismo resultado, ya que se está haciendo uso de la aritmética de punteros, es decir que el compilador identifica que data tiene asignado un bloque de memoria de 20 bytes (por ser del tipo BaseData), por lo tanto al indicarle que sume 1, no sumara 1 byte literalmente, sino que como data tiene un tamaño de 20 bytes ese "+ 1" indica que debemos desplazarnos un tamaño de 1 "data" en la memoria, es decir 20 bytes.
   
**Explique los valores que se muestran en pantalla en cada iteración del for**

![image](https://user-images.githubusercontent.com/65351453/186183465-5b3f6e1b-44cf-4ead-9c22-3a3382710151.png)

   En primer lugar, en cada iteración se imprime el número de byte. Esto está manejado por la variable "i", simplemente es un número entero que se imprime en cada ciclo, completado con un 0 al inicio para numeros de un solo digito (esto por el modificador "02" antes de "d", que indica que rellene con un cero para formar números de dos digitos de ser necesario). Luego del caracter ":", lo que se imprime en cada ciclo es el contenido de la dirección a la que apunta el puntero "c", con la salvedad de que se imprime en formato hexadecimal (el formato indicado para la impresion es "0x", y el mismo modificador "02" utilizado antes, sumado a los modificadores %hhx). EL bucle está limitado a 20 repeticiones, ya que el tamaño de limit es de 20 bytes. Por lo tanto, recordando la inicialización de valores de data y como se guardaron sus datos:

![image](https://user-images.githubusercontent.com/65351453/186183919-5a0eb372-f24f-4bad-b058-410df3421c12.png)
![image](https://user-images.githubusercontent.com/65351453/186180176-2ff7aebf-2f7f-4e51-beae-ee68803c310e.png)

   Vemos que se van imprimiendo los valores de las variables de la estructura en hexadecimal, con "basura" de por medio, debido al padding:

     byte 00 : 0x01 --> valor de "a"
     byte 01 : 0x03 --> valor de "b"
     byte 02 : 0x72 --> basura
     byte 03 : 0xc3 --> basura
     byte 04 : 0x0f --> valor de "x"
     byte 05 : 0x00 --> valor de "x"
     byte 06 : 0x00 --> valor de "x"
     byte 07 : 0x00 --> valor de "x"
     byte 08 : 0xff --> valor de "y"
     byte 09 : 0xff --> valor de "y"
     byte 10 : 0x80 --> valor de "c"
     byte 11 : 0x00 --> basura
     byte 12 : 0xff --> valor de "z"
     byte 13 : 0xff --> valor de "z"
     byte 14 : 0x01 --> valor de "d"
     byte 15 : 0x01 --> valor de "d"
     byte 16 : 0x01 --> valor de "d"
     byte 17 : 0x10 --> basura
     byte 18 : 0x00 --> basura
     byte 19 : 0x00 --> basura

   Resulta extraño el comportamiento del arreglo d, ya que al parecer no se ha guardado en el ultimo bloque de 4 bytes, sino que ha guardado 2 elementos en el bloque en el que esta "z", y el ultimo elemento en otro bloque separado. Al parecer ese arreglo "d" no se esta alineando. Esto puede ser por el hecho de que en C los arreglos corresponden a un puntero a su primer elemento, y al ser un arreglo de variables tipo char, el compilador identifica que tiene 1 char por vez, por lo que no asigna un bloque de 3 bytes haciendo padding, sino que va asignando de a 1 bytes por vez. 
