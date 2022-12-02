CFLAGS = -Wall -Werror -pedantic
src = ./src
bin = ./bin
out = ./out

$(bin)/MemoryMapping.out: $(out)/main.o $(out)/measurements.o
	mkdir -p $(bin)/
	gcc $(CFLAGS) -o $@ $(out)/main.o $(out)/measurements.o

$(out)/main.o: $(src)/main.c $(src)/measurements.h
	mkdir -p $(out)/
	gcc $(CFLAGS) -c -o $@ $(src)/main.c

$(out)/measurements.o: $(src)/measurements.c $(src)/measurements.h
	gcc $(CFLAGS) -c -o $@ $(src)/measurements.c

clean:
	rm -rf $(bin)/ $(out)/