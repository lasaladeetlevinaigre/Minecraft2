#include "Game.h"
#include "Map.h"
#include "Bloc.h"

Game::Game() : fps_(60), tps_(20), speed_(1.0f), frameCount_(0), width_(1600), height_(900), blockSize_(5), isRunning_(true)
{
	window_.create(sf::VideoMode(width_, height_), "Minecraft2");
	window_.setFramerateLimit(fps_);
	map_ = new Map(width_, height_, blockSize_);
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
		if (event.type == sf::Event::Closed) {
			std::cout << "Game closed" << std::endl;
			isRunning_ = false;
			window_.close();
		}
		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Escape) {
				std::cout << "Game closed" << std::endl;
				isRunning_ = false;
				window_.close();
			}
			if (event.key.code == sf::Keyboard::Space)
			{
				if (isRunning_) {
					std::cout << "Game paused" << std::endl;
					isRunning_ = false;
				}
				else {
					std::cout << "Game resumed" << std::endl;
					isRunning_ = true;
				}
			}
			if (event.key.code == sf::Keyboard::S) {
				// summon sand block
				int x = rand() % map_->getWidth();
				int y = rand() % map_->getHeight();
				if (map_->inBounds(x, y)) {
					map_->setBlocInCurrentFrame(x, y, new Bloc(x, y, sf::Color::Yellow));
					std::cout << "Summoned sand block at (" << x << ", " << y << ")" << std::endl;
				}
				else {
					std::cout << "Invalid position for sand block: (" << x << ", " << y << ")" << std::endl;
				}
			}
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
