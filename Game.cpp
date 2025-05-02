#include "Game.h"
#include "Map.h"
#include "Bloc.h"
#include "Menu.h"

Game::Game() : fps_(60), tps_(20), speed_(1.0f), frameCount_(0), width_(1600), height_(900), uiWidth_(200), blockSize_(5), isRunning_(false)
{
	window_.create(sf::VideoMode(width_, height_), "Minecraft2");
	window_.setFramerateLimit(fps_);
	map_ = new Map(width_ - uiWidth_, height_, blockSize_);
	menu_ = new Menu(this, map_, uiWidth_);
}


Game::~Game()
{
	delete map_;
	delete menu_;
}

void Game::run()
{
	while (window_.isOpen())
	{
		handleEvents();
		if (isRunning_)
		{
			frameCount_++;
			//std::cout << frameCount_ << std::endl;
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

		menu_->handleEvent(event, window_);
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
	menu_->drawUI(window_);
	map_->draw(window_);
	window_.display();
}
