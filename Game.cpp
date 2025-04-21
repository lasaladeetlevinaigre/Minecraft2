#include "Game.h"
#include "Map.h"

Game::Game() : window_(sf::VideoMode(800, 600), "Minecraft2"), fps_(60), tps_(20), speed_(1.0f), frameCount_(0), width_(800), height_(600), isRunning_(true)
{
	window_.setFramerateLimit(fps_);
	map_ = new Map();
}


Game::~Game()
{
	delete map_;
}

void Game::run()
{
	while (window_.isOpen())
	{
		handleEvents();
		if (isRunning_)
		{
			frameCount_++;
			std::cout << frameCount_ << std::endl;
			update();
		}
		render();
	}
}
void Game::handleEvents()
{
	sf::Event event;
	while (window_.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			window_.close();
		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Escape)
				window_.close();
			if (event.key.code == sf::Keyboard::Space)
				isRunning_ != isRunning_;
		}
		//menu_->handlEvents(event);
	}
}
void Game::update()
{
	map_->update();
	//menu_->update();
}
void Game::render()
{
	window_.clear(sf::Color::Black);
	map_->draw(window_);
	//menu_->drawUI();
	window_.display();
}
