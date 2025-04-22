#ifndef GAME_H
#define GAME_H
#include <SFML/Graphics.hpp>

class Map;
class Menu;

class Game
{
	sf::RenderWindow window_;
	int uiWidth_;

	int fps_, tps_;
	float speed_;
	int frameCount_;

	int width_, height_;
	int blockSize_;

	Map* map_;
	Menu* menu_;

	bool isRunning_;
public:
	Game();
	~Game();

	bool isRunning() const { return isRunning_; }
	void setRunning(bool running) { isRunning_ = running; }

	void run();
	void handleEvents();
	void update();
	void render();

	int getWidth() const { return width_; }
	int getHeight() const { return height_; }
};

#endif // GAME_H