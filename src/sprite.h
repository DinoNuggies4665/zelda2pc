#ifndef SPRITE_H
#define SPRITE_H

#include <SFML/Graphics.hpp>

class Sprite {
private:
	void clipTexture(int _x1, int _y1, int _x2, int _y2);
	void changeSprite(const char* _sprite, bool loop = false);
	void addSprite(const char* _name, int _x1, int _y1, int _x2, int _y2);
	void addAnimation();

	int frame;
	sf::Sprite sprite;
	sf::Texture texture;
public:
};

#endif