all:
	clear
	ccache g++ -c src/main.cpp -o build/main.o
	ccache g++ -c src/game.cpp -o build/game.o
	ccache g++ -c src/scene.cpp -o build/scene.o
	ccache g++ -c src/sprite.cpp -o build/sprite.o
	ccache g++ -c src/player.cpp -o build/player.o
	ccache g++ build/main.o build/game.o build/scene.o build/sprite.o build/player.o -lsfml-graphics -lsfml-window -lsfml-system
	./a.out
