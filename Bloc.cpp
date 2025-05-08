// Bloc.cpp
// Auteur: Antoine Horion
#include "Bloc.h"

// Dessine un bloc sur la fenêtre de rendu.
void Bloc::draw(sf::RenderWindow& window, int blockSize) const {
	sf::RectangleShape rectangle(sf::Vector2f(blockSize, blockSize));
	rectangle.setPosition(x_ * blockSize, y_ * blockSize);
	rectangle.setFillColor(color_);
	window.draw(rectangle);
}