#include <stdio.h>
#include "structs.h"

int main()
{
    const BaseData data = {
                .a = 1,
                .b = 3,
                .x = 15,
                .y = 65535,
                .c = 128,
                .z = -1, 
                .d = {1,1,1}
    };

    /* Explique a que se debe los tamanios de cada una de las estructuras */

    printf("base     struct size  %lu \n", sizeof(BaseData));
    printf("reorder  struct size  %lu \n", sizeof(ReorderData));
    printf("extended struct size  %lu \n", sizeof(ExtendedData));
    printf("packed   struct size  %lu \n\n", sizeof(BaseDataPacked));

    /* explique por que las expresiones que calculan  limit y limit_aux generan el mismo resutado */
    /* hint : investigar sobre reglas de aritmetica de punteros */
    
    char *limit = ((char *) &data + sizeof(BaseData));
    char *limit_aux =(char *) (&data + 1);
    printf("limit     value is %p \n", limit); 
    printf("limit_aux value is %p \n\n", limit_aux);


    /* Explique los valores que se muestran en pantalla en cada iteracion del for */
    int i = 0;
    for (char *c = (char *) &data; c < limit; c++, i++ ){
        printf("byte %02d : 0x%02hhx \n", i, *c);
    }
    /* En primer lugar, en cada iteracion se imprime el numero de byte. Esto esta manejado por la variable "i",
     simplemente es un numero entero que se imprime en cada ciclo, completado con un 0 al inicio para numeros
     de un solo digito (esto por el modificador "02" antes de "d", que indica que rellene con un cero para
     formar numeros de dos digitos de ser necesario). Luego del caracter ":", lo que se imprime en cada ciclo
     es el contenido de la direccion a la que apunta el puntero "c", con la salvedad de que se imprime en
     formato hexadecimal (el formato indicado para la impresion es "0x", y el mismo modificador "02" utilizado
     antes). EL bucle esta limitado a 20 repeticiones, ya que el tamaño de limit es de 20 bytes.
     Por lo tanto, recordando la inicializacion de valores de data y como se guardaron sus datos:
     const BaseData data = {
                .a = 1,
                .b = 3,
                .x = 15,
                .y = 65535,
                .c = 128,
                .z = -1,
                .d = {1,1,1}
    };
     Tamaño: 20 bytes = (a,b,"","") + (x) + (y,c,"") + (z,"","") + (d, "")
                      =      4      +  4  +    4     +     4     +    4   (bytes)
     Vemos que se van imprimiendo los valores de las variables de la estructura en hexadecimal, con "basura"
     de por medio, debido al padding:

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

     Resulta extraño el comportamiento del arreglo d, ya que al parecer no se ha guardado en el ultimo bloque
     de 4 bytes, sino que ha guardado 2 elementos en el bloque en el que esta "z", y el ultimo elemento en
     otro bloque separado. Al parecer ese arreglo "d" no se esta alineando.
     */

}
