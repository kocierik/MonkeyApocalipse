demo: main.o menu.o actor.o
	g++ -o main main.o menu.o actor.o -lncurses 
	./main
demo.o: main.cpp
	g++ -c main.cpp
menu.o: src/menu.cpp
	g++ -c src/menu.cpp
actor.o: src/actor.cpp
	g++ -c src/actor.cpp
clean:
	rm *.o main