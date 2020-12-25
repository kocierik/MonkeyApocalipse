demo: main.o menu.o actor.o
	g++ -o main main.o menu.o actor.o -lncurses 
	./main
demo.o: main.cpp
	g++ -c main.cpp
menu.o: menu.cpp
	g++ -c menu.cpp
actor.o: actor.cpp
	g++ -c actor.cpp
clean:
	rm *.o main