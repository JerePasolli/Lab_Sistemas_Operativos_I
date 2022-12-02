CFLAGS = -Wall -Werror -pedantic -g
src = ./src
bin = ./bin
out = ./out

$(bin)/myshell: $(out)/main.o $(out)/utils.o $(out)/executeCommands.o $(out)/executeBinarys.o
	mkdir -p $(bin)/
	gcc $(CFLAGS) -o $@ $(out)/main.o $(out)/utils.o $(out)/executeCommands.o $(out)/executeBinarys.o

$(out)/main.o: $(src)/main.c $(src)/executeCommands.h
	mkdir -p $(out)/
	gcc $(CFLAGS) -c -o $@ $(src)/main.c

$(out)/utils.o: $(src)/utils.c $(src)/utils.h
	gcc $(CFLAGS) -c -o $@ $(src)/utils.c

$(out)/executeCommands.o: $(src)/executeCommands.c $(src)/executeCommands.h $(src)/utils.h $(src)/executeBinarys.h
	gcc $(CFLAGS) -c -o $@ $(src)/executeCommands.c

$(out)/executeBinarys.o: $(src)/executeBinarys.c $(src)/executeBinarys.h $(src)/utils.h
	gcc $(CFLAGS) -c -o $@ $(src)/executeBinarys.c

clean:
	rm -rf $(bin)/ $(out)/