#include "game.h"

// Private Functions
void Game::pollEvents() {
	while (this->window->pollEvent(ev)) {
		switch (this->ev.type) {
			case sf::Event::Closed:
				this->window->close();
				break;
			case sf::Event::KeyPressed:
				if (ev.key.code == sf::Keyboard::Z and !this->player.isJumping and !this->player.isAttacking)
					this->player.frame = 0;
				if (ev.key.code == sf::Keyboard::X and this->player.canAttack) {
					this->player.isAttacking = true;
					this->player.canAttack = false;
					this->player.frame = 0;
					if (this->player.dir == 1)
						this->player.dir = 3;
					else if (this->player.dir == 0)
						this->player.dir = 2;
				}
				if (ev.key.code == sf::Keyboard::Right) {
					if (!this->player.isAttacking)
						this->player.dir = 1;
					else {
						if (this->player.canAttack)
							this->player.isAttacking = false;
					}
				}
				else if (ev.key.code == sf::Keyboard::Left) {
					if (!this->player.isAttacking)
						this->player.dir = 0;
					else {
						if (this->player.canAttack)
							this->player.isAttacking = false;
					}
				}
				break;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			this->window->close();
	}
}
void Game::camera() {
	if (this->player.x >= (Global::WIDTH / 2) - 6 and this->player.x < Global::SCENE_WIDTH - (Global::WIDTH / 2) - 6) {
		this->view.move(this->player.vx, 0);
		this->HUD.move(this->player.vx, 0);
	}
	if (this->player.x < (Global::WIDTH / 2) - 6) {
		this->view.setCenter(Global::WIDTH / 2, Global::HEIGHT / 2);
		this->HUD.setPosition(0, 0);
	}
	else if (this->player.x > Global::SCENE_WIDTH - (Global::WIDTH / 2) - 6) {
		this->view.setCenter(Global::SCENE_WIDTH - Global::WIDTH / 2, Global::HEIGHT / 2);
		this->HUD.setPosition(Global::SCENE_WIDTH - Global::WIDTH, 0);
	}
}
void Game::changeScene(int _scene) {
	switch (_scene) {
		case 0:
			this->player.ground = 200;
			this->sceneExitR = 1;
			this->sceneExitL = 2;
			this->backgroundTexture.loadFromFile("assets/level.png");
			this->background.setTexture(this->backgroundTexture);
			this->background.setTextureRect(sf::IntRect(1, -13, Global::SCENE_WIDTH, Global::HEIGHT));
			break;
		case 1:
			this->player.ground = 184;
			this->sceneExitR = 2;
			this->sceneExitL = 0;
			this->backgroundTexture.loadFromFile("assets/encounters.png");
			this->background.setTexture(this->backgroundTexture);
			this->background.setTextureRect(sf::IntRect(1, -3, Global::SCENE_WIDTH, Global::HEIGHT));
			break;
		case 2:
			this->player.ground = 200;
			this->sceneExitR = 0;
			this->sceneExitL = 1;
			this->backgroundTexture.loadFromFile("assets/encounters.png");
			this->background.setTexture(this->backgroundTexture);
			this->background.setTextureRect(sf::IntRect(1, 220, Global::SCENE_WIDTH, Global::HEIGHT));
			break;
	}
}
void Game::updateScene() {
	if (this->player.x + 7 < 0) {
		this->changeScene(this->sceneExitL);
		this->player.init(1);
	}
	else if (this->player.x + 7 > Global::SCENE_WIDTH) {
		this->changeScene(this->sceneExitR);
		this->player.init(0);
	}
}

// Public Functions
Game::Game() {
	this->HUD.setSize(sf::Vector2f(Global::WIDTH, 24));
	this->HUD.setFillColor(sf::Color::Black);
	this->HUD.setPosition(this->player.x - Global::WIDTH / 2 + 7, 0);

	this->view.setSize(Global::WIDTH, Global::HEIGHT);
	this->view.setCenter(this->player.x + 7, Global::HEIGHT / 2);
	this->videoMode = sf::VideoMode(Global::WIN_WIDTH, Global::WIN_HEIGHT);
	this->window = new sf::RenderWindow(this->videoMode, "Game", sf::Style::Titlebar | sf::Style::Close);
	this->window->setPosition(sf::Vector2i(sf::VideoMode::getDesktopMode().width / 2 - Global::WIN_HEIGHT / 2 - 49, sf::VideoMode::getDesktopMode().height / 2 - Global::WIN_HEIGHT / 2));
	this->window->setView(this->view);

	this->window->setKeyRepeatEnabled(false);
	this->window->setFramerateLimit(60);

	this->changeScene(0);

	//this->enemy[0] = new SlimeRed(Global::WIDTH / 2, 0, 1);
}

Game::~Game() {
	delete this->window;
}

bool Game::running() {
	return this->window->isOpen();
}

void Game::update() {
	this->pollEvents();
	this->camera();
	this->updateScene();
	this->player.update();
}

void Game::render() {
	this->window->setView(this->view);
	this->window->clear(sf::Color::White);

	this->window->draw(this->background);
	this->window->draw(this->HUD);
	this->player.render(this->window);
	
	this->window->display();
}
