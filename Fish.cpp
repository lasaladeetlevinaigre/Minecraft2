#include "Fish.h"
#include "Map.h"
#include "Bloc.h"

Fish::Fish(int x, int y, std::string name, sf::Color color)
	: x_(x), y_(y), name_(name), color_(color), initialColor_(color),
	direction_(rand() % 2 ? 1 : -1), // Direction aléatoire
	swimCooldown_(30),
	timeLeftToLive_(250),
	changeDirCooldown_(60),
	isAlive_(true),
	flashCooldown_(20) {
}


void Fish::update(Map* map) {

	// Vérifier si Fish est toujours dans l'eau
	if (!map->inBounds(x_, y_) || !map->getBlockInNextGrid(x_, y_) ||
		map->getBlockInNextGrid(x_, y_)->getType() != WATER) {
		// Hors de l'eau

		// Suffoqué par un bloc => on monte
		if (map->getBlockInNextGrid(x_, y_)	// suffoqué par un bloc
			&& map->inBounds(x_, y_ - 1) && (!map->getBlockInNextGrid(x_, y_ - 1) ||	// soit le bloc au dessus est vide
			(map->getBlockInNextGrid(x_, y_ - 1)->getType() == WATER)		// soit il y a un bloc d'eau dans lequel Fish peut monter
			)) {
			y_ -= 1;
		}

		// Suffoqué par manque d'eau => on est dans l'air => Gravité
		if (map->inBounds(x_, y_+1) && (!map->getBlockInNextGrid(x_, y_+1) ||	// soit le bloc dessous est vide
			(map->getBlockInNextGrid(x_, y_ + 1)->getType() == WATER )		// soit il y a un bloc d'eau dans lequel Fish peut tomber
			)){
			y_ += 1;
		}

		if (--timeLeftToLive_ <= 0) {
			// Le poisson est mort :(
			isAlive_ = false;
			return;
		}
		else {
			// Le poisson suffoque !!
			// On fait clignoter le poisson en rouge,
			if (--flashCooldown_ <= 10)
				color_ = initialColor_;
			else
				color_ = sf::Color(255, 0, 0, 255);

			if (flashCooldown_ < 0)
				flashCooldown_ = 20;
		}
		return;
	}
	timeLeftToLive_ = 250;
	color_ = initialColor_;

	// Dhangement de direction
	if (--changeDirCooldown_ <= 0) {
		if (rand() % 5 == 0) { // 20% de chance de dhanger de direction
			direction_ *= -1;
		}
		changeDirCooldown_ = 60 + rand() % 60; // aléatoire pour rendre le mvnt plus naturel
	}

	// NAGE
	if (--swimCooldown_ <= 0) {
		// Essayer de se déplacer HORIZONTALEMENT
		if (map->inBounds(x_ + direction_, y_) &&
			map->getBlockInNextGrid(x_ + direction_, y_) &&
			map->getBlockInNextGrid(x_ + direction_, y_)->getType() == WATER) {
			x_ += direction_;
		}
		// Direction opposée
		else if (map->inBounds(x_ - direction_, y_) &&
			map->getBlockInNextGrid(x_ - direction_, y_) &&
			map->getBlockInNextGrid(x_ - direction_, y_)->getType() == WATER) {
			direction_ *= -1;
			x_ += direction_;
		}

		// Mouvement VERTICAL
		if (rand() % 3 == 0) { // 33 % de chance de cahnger d'hauteur
			bool justBelowSurface = !map->inBounds(x_, y_ - 1) || 
				(map->getBlockInNextGrid(x_, y_ - 1) && map->getBlockInNextGrid(x_, y_ - 1)->getType() != WATER);
			
			// Priorité descente si près de la surface
			int verticalDir = (justBelowSurface || rand() % 3 > 0) ? 1 : -1;  // 50% chance de monter/descendre

			if (map->inBounds(x_, y_ + verticalDir) &&
				map->getBlockInNextGrid(x_, y_ + verticalDir) &&
				map->getBlockInNextGrid(x_, y_ + verticalDir)->getType() == WATER) {
				y_ += verticalDir;
			}
		}

		swimCooldown_ = 10 + rand() % 20; // Vitesse de la nage aléatoire pour rendre le mvnt plus naturel
	}

}

void Fish::draw(sf::RenderWindow& window, int blockSize) const {
	sf::RectangleShape rectangle(sf::Vector2f(blockSize, blockSize));
	rectangle.setPosition(x_ * blockSize, y_ * blockSize);
	rectangle.setFillColor(color_);
	window.draw(rectangle);
}