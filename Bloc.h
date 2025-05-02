#pragma once

#include <SFML/Graphics.hpp>

class Map;

enum BlocType{
	STONE,
	SAND,
	MUSHROOM
};

class Bloc {
	sf::Color color_;
	int x_;
	int  y_;
	BlocType type_;
public:
	Bloc(int x, int y, BlocType type, sf::Color color) : color_(color), type_(type), x_(x), y_(y) {}
	virtual ~Bloc() {};

	virtual void update(Map* map) = 0;

	void setX(int x) { x_ = x; }
	void setY(int y) { y_ = y; }

	void draw(sf::RenderWindow& window, int blockSize) const {
		sf::RectangleShape rectangle(sf::Vector2f(blockSize, blockSize));
		rectangle.setPosition(x_ * blockSize, y_ * blockSize);
		rectangle.setFillColor(color_);
		window.draw(rectangle);
	}

	int getX() const { return x_; }
	int getY() const { return y_; }
	sf::Color getColor() const { return color_; }
	BlocType getType() const { return type_; }



};