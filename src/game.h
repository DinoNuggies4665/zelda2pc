#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include "globals.h"
#include "player.h"
#include "enemy.h"

class Game {
private:
	void pollEvents();
	void camera();
	void changeScene(int _scene);
	void updateScene();

	sf::RenderWindow* window;
	sf::VideoMode videoMode;
	sf::View view;
	sf::Event ev;

	Player player;
	sf::RectangleShape HUD;

	sf::Sprite background;
	sf::Texture backgroundTexture;
	int sceneWidth, sceneExitR, sceneExitL;
public:
	Game();
	~Game();

	Enemy* enemy[];

	bool running();
	void update();
	void render();
};

#endif