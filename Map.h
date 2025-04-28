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
	Map(int screenWidth, int screenHeight, int blockSize);
	~Map();
	void update();
	void draw(sf::RenderWindow& window) const;
	void setBlocInNextFrame(int x, int y, Bloc* bloc);
	void setBlocInCurrentFrame(int x, int y, Bloc* bloc);
	void removeBloc(int x, int y);
	void clear();
	Bloc* getBlock(int x, int y);
	bool inBounds(int x, int y) const;

	int getWidth() const { return width_; }
	int getHeight() const { return height_; }
	int getBlockSize() const { return blockSize_; }

};


#endif // !MAP_H
