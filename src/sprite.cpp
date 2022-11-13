#include "sprite.h"

void Sprite::clipTexture(int _x1, int _y1, int _x2, int _y2) {
	this->sprite.setTextureRect(sf::IntRect(_x1, _y1, _x2, _y2));
}

void Sprite::addSprite(const char* _name, int _x1, int _y1, int _x2, int _y2) {
	
}

void Sprite::addAnimation() {
	
}

void Sprite::changeSprite(const char* _sprite, bool _loop) {
	// Static Sprites
	if (_sprite == "IdleRight")
		this->clipTexture(1, 11, 16, 32);
	else if (_sprite == "IdleLeft")
		this->clipTexture(1 + 16, 11, -16, 32);

	// Animated Sprites
	else if (_sprite == "WalkRight") {
		if (this->frame > 15 and _loop)
			this->frame = 0;
		else if (this->frame > 10)
			this->clipTexture(63, 11, 16, 32);
		else if (this->frame > 5)
			this->clipTexture(46, 11, 16, 32);
		else if (this->frame > 0)
			this->clipTexture(29, 11, 16, 32);
	}
	else if (_sprite == "WalkLeft") {
		if (this->frame > 15 and _loop)
			this->frame = 0;
		else if (this->frame > 10)
			this->clipTexture(63 + 16, 11, -16, 32);
		else if (this->frame > 5)
			this->clipTexture(46 + 16, 11, -16, 32);
		else if (this->frame > 0)
			this->clipTexture(29 + 16, 11, -16, 32);
	}

	else if (_sprite == "JumpRight") {
		if (this->frame > 20)
			this->clipTexture(134, 11, 16, 32);
		else if (this->frame > 0)
			this->clipTexture(117, 11, 16, 32);
	}
	else if (_sprite == "JumpLeft") {
		if (this->frame > 20)
			this->clipTexture(134 + 16, 11, -16, 32);
		else if (this->frame > 0)
			this->clipTexture(117 + 16, 11, -16, 32);
	}
}