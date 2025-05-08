// Fish.cpp
// Auteur: Benjamin Escuder
#include "Fish.h"
#include "Map.h"
#include "Bloc.h"

Fish::Fish(int x, int y, std::string name, sf::Color color)
	: x_(x), y_(y), name_(name), color_(color), initialColor_(color),
	direction_(rand() % 2 ? 1 : -1), // Direction al�atoire au d�but
	swimCooldown_(30),
	timeLeftToLive_(250),
	changeDirCooldown_(60),
	isAlive_(true),
	flashCooldown_(20) {
}


void Fish::update(Map* map) {

	// V�rifier si Fish est toujours dans l'eau
	if (!map->inBounds(x_, y_) || !map->getBlockInNextGrid(x_, y_) ||
		map->getBlockInNextGrid(x_, y_)->getType() != WATER) {
		// Hors de l'eau

		// Suffoqu� par un bloc ==> on essaye de monter
		if (map->getBlockInNextGrid(x_, y_)	// suffoqu� par un bloc
			&& map->inBounds(x_, y_ - 1) && (!map->getBlockInNextGrid(x_, y_ - 1) || // soit le bloc au dessus est vide
			(map->getBlockInNextGrid(x_, y_ - 1)->getType() == WATER)		         // soit il y a un bloc d'eau dans lequel Fish peut monter
			)) {
			y_ -= 1;
		}

		// Suffoqu� par manque d'eau, on est dans l'air ==> Gravit�
		if (map->inBounds(x_, y_+1) && (!map->getBlockInNextGrid(x_, y_+1) || // soit le bloc dessous est vide
			(map->getBlockInNextGrid(x_, y_ + 1)->getType() == WATER )		  // soit il y a un bloc d'eau dans lequel Fish peut tomber
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
			// On fait clignoter le poisson en rouge � l'aide de flashCooldown, 
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
		changeDirCooldown_ = 60 + rand() % 60; // al�atoire pour rendre le mvnt plus naturel
	}

	// NAGE
	if (--swimCooldown_ <= 0) {
		// Essayer de se d�placer HORIZONTALEMENT
		if (map->inBounds(x_ + direction_, y_) &&
			map->getBlockInNextGrid(x_ + direction_, y_) &&
			map->getBlockInNextGrid(x_ + direction_, y_)->getType() == WATER) {
			x_ += direction_;
		}
		// Dans la direction oppos�e
		else if (map->inBounds(x_ - direction_, y_) &&
			map->getBlockInNextGrid(x_ - direction_, y_) &&
			map->getBlockInNextGrid(x_ - direction_, y_)->getType() == WATER) {
			direction_ *= -1;
			x_ += direction_;
		}

		// Mouvement VERTICAL
		if (rand() % 2 == 0) { // 50 % de chance de changer d'hauteur
			bool justBelowSurface = !map->inBounds(x_, y_ - 1) || 
				(map->getBlockInNextGrid(x_, y_ - 1) && map->getBlockInNextGrid(x_, y_ - 1)->getType() != WATER);
			
			// Priorit� � la descente si on est pr�s de la surface
			int verticalDir = (justBelowSurface || rand() % 2 > 0) ? 1 : -1;  // 50% chance de monter ou descendre

			if (map->inBounds(x_, y_ + verticalDir) &&
				map->getBlockInNextGrid(x_, y_ + verticalDir) &&
				map->getBlockInNextGrid(x_, y_ + verticalDir)->getType() == WATER) {
				y_ += verticalDir;
			}
		}

		swimCooldown_ = 5 + rand() % 30; // Vitesse de la nage al�atoire pour rendre le mvnt plus naturel
	}

}

// On dessine le poisson comme un carr� � ses coordonn�es
void Fish::draw(sf::RenderWindow& window, int blockSize) const {
	sf::RectangleShape rectangle(sf::Vector2f(blockSize, blockSize));
	rectangle.setPosition(x_ * blockSize, y_ * blockSize);
	rectangle.setFillColor(color_);
	window.draw(rectangle);
}