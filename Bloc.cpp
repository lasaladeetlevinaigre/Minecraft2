#include "Bloc.h"



void Bloc::draw(sf::RenderWindow& window, float cellSize) const {

	sf::RectangleShape rectangle(sf::Vector2f(cellSize, cellSize));
	rectangle.setPosition(x_ * cellSize, y_ * cellSize);
	rectangle.setFillColor(color_);

	window.draw(rectangle);
}