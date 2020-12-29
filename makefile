CC =g++

CFLAGS =-c -Wall

OBJECTS = main.o menu.o character.o enemyKamikaze.o window.o

demo: $(OBJECTS)
	$(CC) -o main main.o menu.o character.o enemyKamikaze.o window.o -lncurses 
	./main
demo.o: main.cpp
	$(CC) $(CFLAGS) main.cpp
menu.o: src/menu.cpp
	$(CC) $(CFLAGS) src/menu.cpp
character.o: src/character.cpp
	$(CC) $(CFLAGS) src/character.cpp
enemyKamikaze.o: src/enemyKamikaze.cpp
	$(CC) $(CFLAGS) src/enemyKamikaze.cpp
window.o: src/window.cpp
	$(CC) $(CFLAGS) src/window.cpp
clean:
	rm *.o main