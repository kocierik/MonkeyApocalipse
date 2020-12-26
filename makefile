demo: main.o menu.o character.o
	g++ -o main main.o menu.o character.o -lncurses 
	./main
demo.o: main.cpp
	g++ -c main.cpp
menu.o: src/menu.cpp
	g++ -c src/menu.cpp
character.o: src/character.cpp
	g++ -c src/character.cpp
clean:
	rm *.o main