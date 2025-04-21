#ifndef MAP_H
#define MAP_H
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

class Bloc;

class Map
{
private:
	int width_;
	int height_;
    int blockSize_;
    std::vector<std::vector<Bloc*>> currentGrid_;
    std::vector<std::vector<Bloc*>> nextGrid_;


public:
	Map();
	~Map();
	void initGrid();
	void update();
	void draw(sf::RenderWindow& window) const;
	void setBloc(int x, int y, Bloc* block);
	Bloc* getBlock(int x, int y);
	bool inBounds(int x, int y) const;
	void swapGrids();
};


#endif // !MAP_H
