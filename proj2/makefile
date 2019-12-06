main: main.o player.o game.o
	g++ -o main.o player.o game.o

main.o: main.cpp player.hpp game.hpp
	g++ main.cpp player.cpp game.cpp -o main.o

player.o: player.hpp
	g++ player.hpp player.cpp -o player.o

game.o: game.hpp 
	g++ game.hpp game.cpp -o game.o
