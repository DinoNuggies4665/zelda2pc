#ifndef SCENE_H
#define SCENE_H

#include <SFML/Graphics.hpp>

class Scene {
private:
	sf::Sprite background;
	sf::Texture backgroundTexture;
	int sceneWidth;
public:
	void changeScene(int _scene);
};

#endif