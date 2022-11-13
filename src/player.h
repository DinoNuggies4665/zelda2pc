#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>

#include "globals.h"

class Player {
public:
	Player();
	~Player();
	void init(int _dir);

	float x, y, vx, vy;
	int ground, dir; // dir: 0 = left, 1 = right
	bool isJumping, canAttack, isAttacking, doDamage, isGrounded;

	int frame;

	void update();
	void render(sf::RenderWindow* _window);
private:
	void input();
	void collision();
	void physics();

	void clipTexture(int _x1, int _y1, int _x2, int _y2);
	void changeSprite(const char* _sprite, bool _loop = false);
	sf::Sprite sprite;
	sf::Texture texture;
	int offsetX, attackFrame;
	bool isDucking, isIdle;

	const float SPEED = 1.5, ACCELERATION = 0.1, DECELERATION = 0.2, JUMP_STRENGTH = -5, TERMINAL_VELOCITY = 10, WEIGHT = 0.3;
};

#endif