CC = g++
CFLAGS = -c -Wall
OBJECTS = main.o menu.o character.o enemyKamikaze.o bullet.o window.o credits.o
LIBRARY = -lncurses 

demo: $(OBJECTS)
	$(CC) -o main $(OBJECTS) $(LIBRARY)
	./main

demo.o: main.cpp
	$(CC) $(CFLAGS) main.cpp

menu.o: src/menu.cpp
	$(CC) $(CFLAGS) src/menu.cpp

character.o: src/character.cpp
	$(CC) $(CFLAGS) src/character.cpp

enemyKamikaze.o: src/enemyKamikaze.cpp
	$(CC) $(CFLAGS) src/enemyKamikaze.cpp

bullet.o: src/bullet.cpp
	$(CC) $(CFLAGS) src/bullet.cpp

window.o: src/window.cpp
	$(CC) $(CFLAGS) src/window.cpp

credits.o: src/credits.cpp
	$(CC) $(CFLAGS) src/credits.cpp

clean:
	rm *.o main