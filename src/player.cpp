#include "player.h"

// Private Functions
void Player::init(int _dir) {
	if (_dir == 0) {
		this->x = 16;
		this->dir = 1;
	}
	else if (_dir == 1) {
		this->x = Global::SCENE_WIDTH - 16;
		this->dir = 0;
	}
	else if (_dir == 2) {
		this->x = Global::SCENE_WIDTH / 2 - 7;
		this->dir = 1;
	}
	this->y = this->ground - 32;
	this->vx = 0;
	this->vy = 0;
	this->canAttack = true;
	this->isIdle = true;
	this->isDucking = false;
	this->isJumping = false;
	this->isAttacking = false;
	this->doDamage = false;
	this->offsetX = 0;	
	this->texture.loadFromFile("assets/link.png");
	this->sprite.setTexture(this->texture);
	this->sprite.setTextureRect(sf::IntRect(1, 11, 16, 32));
	this->sprite.setPosition(this->x, this->y);
	this->frame = 0;
}

void Player::input() {
	if (this->canAttack) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
			this->isAttacking = false;
			this->dir = 1;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
			this->dir = 0;
			this->isAttacking = false;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
			this->isAttacking = false;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::X))
			this->isAttacking = false;
	}

	// Right
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) and !this->isDucking and !this->isAttacking) {
		this->isIdle = false;
		this->offsetX = 0;
		if (!this->isJumping)
			this->changeSprite("WalkRight", true);
		else
			this->changeSprite("JumpRight");
		if (this->vx < this->SPEED)
			this->vx += this->ACCELERATION;
	}

	// Left
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) and !this->isDucking and !this->isAttacking) {
		this->isIdle = false;
		this->offsetX = 0;
		if (!this->isJumping)
			this->changeSprite("WalkLeft", true);
		else
			this->changeSprite("JumpLeft");
		if (this->vx > -this->SPEED)
			this->vx -= this->ACCELERATION;
	}

	// Not Right or Left
	else {
		if (!this->isAttacking) {
			this->isIdle = true;

			if (this->isJumping) {
				if (this->dir == 1)
					this->changeSprite("JumpRight");
				else if (this->dir == 0)
					this->changeSprite("JumpLeft");
			}
			else {
				if (this->dir == 1)
					this->changeSprite("IdleRight");
				else if (this->dir == 0)
					this->changeSprite("IdleLeft");
			}
			if (this->dir < 2)
				this->offsetX = 0;
		}
	}

	// Down
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		if (this->canAttack)
			this->isDucking = true;
	}
	else {
		if (this->canAttack)
			this->isDucking = false;
	}

	// Jump
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z) and !this->isJumping) {
		this->frame = 0;
		this->isAttacking = false;
		this->canAttack = true;
		this->vy = this->JUMP_STRENGTH;
		this->isJumping = true;
	}
}

void Player::clipTexture(int _x1, int _y1, int _x2, int _y2) {
	this->sprite.setTextureRect(sf::IntRect(_x1, _y1, _x2, _y2));
}

void Player::changeSprite(const char* _sprite, bool _loop) {
	// Static Sprites
	if (_sprite == "IdleRight")
		this->clipTexture(1, 11, 16, 32);
	else if (_sprite == "IdleLeft")
		this->clipTexture(17, 11, -16, 32);
	else if (_sprite == "DuckRight")
		this->clipTexture(84, 11, 16, 32);
	else if (_sprite == "DuckLeft")
		this->clipTexture(100, 11, -16, 32);

	// ======== Animated Sprites ======== //

	// Walking Animations
	else if (_sprite == "WalkRight") {
		if (this->frame > 30 and _loop)
			this->frame = 0;
		else if (this->frame > 20)
			this->clipTexture(63, 11, 16, 32);
		else if (this->frame > 10)
			this->clipTexture(46, 11, 16, 32);
		else if (this->frame > 0)
			this->clipTexture(29, 11, 16, 32);
	}
	else if (_sprite == "WalkLeft") {
		if (this->frame > 30 and _loop)
			this->frame = 0;
		else if (this->frame > 20)
			this->clipTexture(79, 11, -16, 32);
		else if (this->frame > 10)
			this->clipTexture(62, 11, -16, 32);
		else if (this->frame > 0)
			this->clipTexture(45, 11, -16, 32);
	}
	// Jumping Idle Animations
	else if (_sprite == "JumpRight") {
		if (this->frame > 34)
			this->clipTexture(134, 11, 16, 32);
		else if (this->frame > 0)
			this->clipTexture(117, 11, 16, 32);
	}
	else if (_sprite == "JumpLeft") {
		if (this->frame > 34)
			this->clipTexture(150, 11, -16, 32);
		else if (this->frame > 0)
			this->clipTexture(133, 11, -16, 32);
	}

	// Attacking Animations
	else if (_sprite == "AttackRight") {
		if (this->frame > 30) {
			this->clipTexture(1, 73, 24, 32);
			this->offsetX = -8;
		}
		else if (this->frame > 14) {
			this->clipTexture(26, 73, 32, 32);
			this->offsetX = 0;
		}
		else if (this->frame > 0) {
			this->clipTexture(1, 73, 24, 32);
			this->offsetX = -8;
		}
	}
	else if (_sprite == "AttackLeft") {
		if (this->frame > 30) {
			this->clipTexture(25, 73, -24, 32);
			this->offsetX = 0;
		}
		else if (this->frame > 14) {
			this->clipTexture(58, 73, -32, 32);
			this->offsetX = -16;
		}
		else if (this->frame > 0) {
			this->clipTexture(25, 73, -24, 32);
			this->offsetX = 0;
		}
	}
	else if (_sprite == "DuckAttackRight") {
		if (this->frame > 14) {
			this->clipTexture(84, 11, 16, 32);
			this->offsetX = 0;
		}
		else if (this->frame > 0) {
			this->clipTexture(67, 73, 32, 32);
			this->offsetX = 0;
		}
	}
	else if (_sprite == "DuckAttackLeft") {
		if (this->frame > 14) {
			this->clipTexture(100, 11, -16, 32);
			this->offsetX = 0;
		}
		else if (this->frame > 0) {
			this->clipTexture(99, 73, -32, 32);
			this->offsetX = -16;
		}
	}
}

void Player::collision() {
	// Gravity and ground collision
	if (this->y > this->ground - 32) {
		this->y = this->ground - 32;
		this->vy = 0;
		this->isJumping = false;
		this->isGrounded = true;
		if (this->isIdle) {
			if (this->vx > this->DECELERATION)
				this->vx -= this->DECELERATION;
			else if (this->vx < -this->DECELERATION)
				this->vx += this->DECELERATION;
			else
				this->vx = 0;
		}
		if (this->isAttacking and !this->isDucking)
			this->vx = 0;
	}
	else {
		if (this->vy < this->TERMINAL_VELOCITY)
			this->vy += this->WEIGHT;
	}

	if (this->isDucking and !this->isJumping) {
		if (this->dir == 1)
			changeSprite("DuckRight");
		else if (this->dir == 0)
			changeSprite("DuckLeft");
	}

	// Attacking, hitting, and being hit
	if (this->isAttacking) {
		if (this->isDucking) {
			if (this->dir == 3)
				this->changeSprite("DuckAttackRight");
			else if (this->dir == 2)
				this->changeSprite("DuckAttackLeft");

			if (this->frame > 0)
				this->doDamage = true;
			else if (this->frame > 14)
				this->doDamage = false;

			if (this->frame > 29)
				this->canAttack = true;
			if (this->frame > 29) {
				if (this->dir == 3)
					this->dir = 1;
				else if (this->dir == 2)
					this->dir = 0;
				this->isAttacking = false;
			}
		}
		else {
			if (this->dir == 3)
				this->changeSprite("AttackRight");
			else if (this->dir == 2)
				this->changeSprite("AttackLeft");

			if (this->frame > 14)
				this->doDamage = true;
			else if (this->frame > 29)
				this->doDamage = false;

			if (this->frame > 29)
				this->canAttack = true;
			if (this->frame > 68) {
				if (this->dir == 3)
					this->dir = 1;
				else if (this->dir == 2)
					this->dir = 0;
				this->isAttacking = false;
			}
		}
	}
	frame++;
}

void Player::physics() {
	this->x += this->vx;
	this->y += this->vy;
	this->collision();

	this->sprite.setPosition(this->x + this->offsetX, this->y);
}

// Public Functions
Player::Player() {
	this->init(2);
}

Player::~Player() {

}

void Player::update() {
	this->frame += 1;
	this->input();
	this->physics();
}

void Player::render(sf::RenderWindow* _window) {
	_window->draw(this->sprite);
}