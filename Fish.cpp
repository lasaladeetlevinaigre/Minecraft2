// Fish.cpp
// Auteur: Benjamin Escuder
#include "Fish.h"
#include "Map.h"
#include "Bloc.h"

Fish::Fish(int x, int y, std::string name, sf::Color color)
	: x_(x), y_(y), name_(name), color_(color), initialColor_(color),
	direction_(rand() % 2 ? 1 : -1), // Direction aléatoire au début
	swimCooldown_(30),
	timeLeftToLive_(250),
	changeDirCooldown_(60),
	isAlive_(true),
	age_(0),
	staringMateSince_(0),
	reproductionCooldown_(1000),
	flashCooldown_(20) {
}


void Fish::update(Map* map) {
	age_++;
	// Vérifier si Fish est toujours dans l'eau
	if (!map->inBounds(x_, y_) || !map->getBlockInNextGrid(x_, y_) ||
		map->getBlockInNextGrid(x_, y_)->getType() != WATER) {
		// Hors de l'eau

		// Suffoqué par un bloc ==> on essaye de monter
		if (map->getBlockInNextGrid(x_, y_)	// suffoqué par un bloc
			&& map->inBounds(x_, y_ - 1) && (!map->getBlockInNextGrid(x_, y_ - 1) || // soit le bloc au dessus est vide
			(map->getBlockInNextGrid(x_, y_ - 1)->getType() == WATER)		         // soit il y a un bloc d'eau dans lequel Fish peut monter
			)) {
			y_ -= 1;
		}

		// Suffoqué par manque d'eau, on est dans l'air ==> Gravité
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
			// On fait clignoter le poisson en rouge à l'aide de flashCooldown, 
			if (--flashCooldown_ <= 10)
				color_ = initialColor_;
			else
				color_ = sf::Color::Red;

			if (flashCooldown_ < 0)
				flashCooldown_ = 20;
		}
		return;
	}
	timeLeftToLive_ = 250;
	color_ = initialColor_;
	


	// REPRODUCTION
	int maturity_age = 1000;
	int min_distance_to_reproduce = 2;
	int min_staring_time = 100;

	// On choisi une couleur random à la majorité
	if (age_ == maturity_age) {
		sf::Color color_tab[5] = {
			sf::Color(245, 93, 5),
			sf::Color(5, 217, 250)
		};
		initialColor_ = color_tab[rand() % 2];
	}

	// Voir si on est en recherche d'un partenaire
	bool spawnAllowed = map->getFishes().size() < 2 * map->getMaxFishCount();
	if (age_ >= maturity_age && --reproductionCooldown_ <= 0 && spawnAllowed) {
		// Je suis prêt à me reproduire
		float minDistance = std::numeric_limits<float>::max(); // init minDistance à la valeur max d'un float
		Fish* closestMate = nullptr;

		// Trouver le partenaire le plus proche capable de se reproduire
		for (Fish *other : map->getFishes()) {
			if (other != this && other->isAlive() && other->getAge() >= maturity_age && other->getReproductionCooldown() <= 0) {
				float dist = (x_ - other->getX()) * (x_ - other->getX()) + (y_ - other->getY()) * (y_ - other->getY());
				if (dist < minDistance) {
					minDistance = dist;
					closestMate = other;
				}
			}
		}

		// Si un partenaire est suffisament proche, on essaye de se reproduire
		if (minDistance <= min_distance_to_reproduce) {

			// Si on se regarde depuis assez longtemps
			if (staringMateSince_ >= min_staring_time && closestMate->staringMateSince() >= min_staring_time) {
				// On se reproduit avec closestMate
				
				// Reset des compteur
				reproductionCooldown_ = 500;
				closestMate->setReproductionCooldown(500);
				staringMateSince_ = 0;
				closestMate->setStaringTime(0);

				// Couleur du bébé aléatoire entre les deux parents
				if (rand() % 2 == 0) {
					map->addFish(new Fish(x_, y_, "Steve Jr", closestMate->getInitialColor()));
				}
				else {
					map->addFish(new Fish(closestMate->getX(), closestMate->getY(), "Steve Jr", initialColor_));
				}
				return;
			}
			else {
				// On ne se regarde pas depuis assez longtemps
				staringMateSince_++;
				return; // on ne se déplace pas
			}
		}
		else {
			// Personne n'est capable de se reproduire aux alentours
			staringMateSince_ = 0;
		}
	}



	// NAGE

	// Dhangement de direction
	if (--changeDirCooldown_ <= 0) {
		if (rand() % 5 == 0) { // 20% de chance de dhanger de direction
			direction_ *= -1;
		}
		changeDirCooldown_ = 60 + rand() % 60; // aléatoire pour rendre le mvnt plus naturel
	}

	if (--swimCooldown_ <= 0) {
		// Essayer de se déplacer HORIZONTALEMENT
		if (map->inBounds(x_ + direction_, y_) &&
			map->getBlockInNextGrid(x_ + direction_, y_) &&
			map->getBlockInNextGrid(x_ + direction_, y_)->getType() == WATER) {
			x_ += direction_;
		}
		// Dans la direction opposée
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
			
			// Priorité à la descente si on est près de la surface
			int verticalDir = (justBelowSurface || rand() % 2 > 0) ? 1 : -1;  // 50% chance de monter ou descendre

			if (map->inBounds(x_, y_ + verticalDir) &&
				map->getBlockInNextGrid(x_, y_ + verticalDir) &&
				map->getBlockInNextGrid(x_, y_ + verticalDir)->getType() == WATER) {
				y_ += verticalDir;
			}
		}

		swimCooldown_ = 5 + rand() % 30; // Vitesse de la nage aléatoire pour rendre le mvnt plus naturel
	}
}

// On dessine le poisson comme un carré à ses coordonnées
void Fish::draw(sf::RenderWindow& window, int blockSize) const {
	sf::RectangleShape rectangle(sf::Vector2f(blockSize, blockSize));
	rectangle.setPosition(x_ * blockSize, y_ * blockSize);
	rectangle.setFillColor(color_);
	window.draw(rectangle);
}