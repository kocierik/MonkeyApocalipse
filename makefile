CC = g++
CFLAGS = -c -Wall -Wextra -pedantic
OBJECTS = main.o menu.o character.o enemyKamikaze.o window.o

demo.o: $(OBJECTS)
	$(CC) -o main $(OBJECTS) -lncurses 
	./main
# $< rappresenta la fonte, quindi main.cpp | $@ indica l'obiettivo della compilazione
main.o: main.cpp
	$(CC) $(CFLAGS) $< $@ 

menu.o: src/menu.cpp src/menu.h
	$(CC) $(CFLAGS) src/menu.cpp menu.o

character.o: src/character.cpp src/character.h
	$(CC) $(CFLAGS) src/character.cpp character.o

enemyKamikaze.o: src/enemyKamikaze.cpp src/enemyKamikaze.h
	$(CC) $(CFLAGS) src/enemyKamikaze.cpp enemyKamikaze.o

window.o: src/window.cpp src/window.h
	$(CC) $(CFLAGS) src/window.cpp window.o

clean:
	rm *.o main
