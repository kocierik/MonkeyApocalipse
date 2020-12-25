demo: main.o menu.o
	g++ -lncurses -o main main.o menu.o 
	./main
demo.o: main.cpp
	g++ -c main.cpp
menu.o: menu.cpp
	g++ -c menu.cpp
clean:
	rm *.o main