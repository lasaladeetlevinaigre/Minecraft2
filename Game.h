#ifndef GAME_H
#define GAME_H
#include <SFML/Graphics.hpp>

class Map;

class Game
{
	sf::RenderWindow window_;
	int fps_, tps_;
	float speed_;
	int frameCount_;
	int width_, height_;

	Map* map_;

	bool isRunning_;
public:
	Game();
	~Game();
	void run();
	void handleEvents();
	void update();
	void render();
};

#endif // GAME_H