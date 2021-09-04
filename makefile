CC = g++
CFLAGS = -c -Wall
OBJECTS = main.o engineGame.o character.o drawWindow.o player.o enemy.o coordinate.o gun.o
LIBRARY = -lncurses

main: $(OBJECTS)
	$(CC) -o main $(OBJECTS) $(LIBRARY)

main.o: main.cpp models/engineGame.hpp models/character.hpp models/drawWindow.hpp models/player.hpp models/enemy.hpp models/coordinate.hpp models/gun.hpp
	$(CC) $(CFLAGS) main.cpp

engineGame.o: models/engineGame.cpp models/engineGame.hpp
	$(CC) $(CFLAGS) models/engineGame.cpp

character.o: models/character.cpp models/character.hpp
	$(CC) $(CFLAGS) models/character.cpp

player.o: models/player.cpp models/player.hpp
	$(CC) $(CFLAGS) models/player.cpp

drawWindow.o: models/drawWindow.cpp models/drawWindow.hpp
	$(CC) $(CFLAGS) models/drawWindow.cpp

enemy.o: models/enemy.cpp models/enemy.hpp
	$(CC) $(CFLAGS) models/enemy.cpp

coordinate.o: models/coordinate.cpp models/coordinate.hpp
	$(CC) $(CFLAGS) models/coordinate.cpp

gun.o: models/gun.cpp models/gun.hpp
	$(CC) $(CFLAGS) models/gun.cpp

clean:
	rm *.o main

launch:
	./main

format:
	clang-format -i -style=google ./**/*.cpp ./**/*.hpp
