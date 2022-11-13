#ifndef ENEMY_H
#define ENEMY_H

#include <SFML/Graphics.hpp>

class Enemy {
public:
	Enemy(int _x, int _y, int _dir);
	~Enemy();

	void update();
	void render(sf::Window* _window);
protected:
	virtual void init();
	virtual void input();
	virtual void collision();
	virtual void physics();

	void clipTexture(int _x1, int _y1, int _x2, int _y2);
	void changeSprite(const char* _sprite, bool _loop = false);
	sf::Sprite sprite;
	sf::Texture texture;

	int x, y, dir;
	float vx, vy;
	bool isJumping;
};

/*
class SlimeRed : public Enemy {
public:
	SlimeRed(int _x, int _y, int _dir);
	~SlimeRed();
private:
	void init();
	void input();
	void collision();
	void physics();
};
*/

#endif
