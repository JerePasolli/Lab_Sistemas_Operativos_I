CFLAGS = -Wall -Werror -pedantic
src = ./src
out = ./out
lib = ./lib
bin = ./bin

$(bin)/main.out: $(out)/main.o $(lib)/libstatic.a $(lib)/libFilesystems.so
	mkdir -p $(bin)
	gcc $(CFLAGS) -o $(bin)/main.out $(out)/main.o $(lib)/libstatic.a -ldl

$(out)/main.o: $(src)/main.c $(src)/Lab2.h
	mkdir -p $(out)
	gcc $(CFLAGS) -c -o $(out)/main.o $(src)/main.c

$(lib)/libstatic.a: $(out)/Actividad1Lab2.o $(out)/Actividad2Lab2.o $(out)/cJSON.o
	mkdir -p $(lib)
	ar -rc $(lib)/libstatic.a $(out)/Actividad1Lab2.o $(out)/Actividad2Lab2.o $(out)/cJSON.o

$(lib)/libFilesystems.so: $(out)/filesystems.o $(out)/cJSON.o
	gcc $(CFLAGS) -shared -fPIC -o $(lib)/libFilesystems.so $(out)/filesystems.o $(out)/cJSON.o

$(out)/Actividad1Lab2.o: $(src)/Actividad1Lab2.c $(src)/Lab2.h $(src)/cJSON.h
	gcc $(CFLAGS) -c -o $(out)/Actividad1Lab2.o $(src)/Actividad1Lab2.c

$(out)/Actividad2Lab2.o: $(src)/Actividad2Lab2.c $(src)/Lab2.h $(src)/cJSON.h
	gcc $(CFLAGS) -c -o $(out)/Actividad2Lab2.o $(src)/Actividad2Lab2.c

$(out)/cJSON.o: $(src)/cJSON.c $(src)/cJSON.h
	gcc $(CFLAGS) -c -o $(out)/cJSON.o $(src)/cJSON.c

$(out)/filesystems.o: $(src)/filesystems.c
	gcc $(CFLAGS) -c -o $(out)/filesystems.o $(src)/filesystems.c

clean:
	rm -rf $(out) $(lib) $(bin)