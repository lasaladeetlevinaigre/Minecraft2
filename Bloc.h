#pragma once

#include <SFML/Graphics.hpp>

class Bloc {
	sf::Color color_;
	int x_;
	int  y_;
public:
	Bloc(int x, int y, sf::Color color) : color_(color), x_(x), y_(y) {}

	void setX(int x) { x_ = x; }
	void setY(int y) { y_ = y; }

	void draw(sf::RenderWindow& window, int blockSize) const {
		sf::RectangleShape rectangle(sf::Vector2f(blockSize, blockSize));
		rectangle.setPosition(x_ * blockSize, y_ * blockSize);
		rectangle.setFillColor(color_);
		window.draw(rectangle);
	}

	// Déplacement et mise à jour du bloc
	void update(Map& map) {
		if (map.inBounds(x_, y_ + 1) && !map.getBlock(x_, y_ + 1)) {
			y_ += 1;
			map.setBlocInNextFrame(x_, y_, this);
		} else {
			// Si le bloc ne bouge pas, le recopier tel quel dans la nouvelle frame
			map.setBlocInNextFrame(x_, y_, this);
		}
	}
};