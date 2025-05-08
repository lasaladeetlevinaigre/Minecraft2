// Auteur : Benjamin Escuder

#include "Map.h"
#include "Bloc.h"
#include "Fish.h"


// Initialisation de la grille
Map::Map(int screenWidth, int screenHeight, int blockSize)
	: width_(screenWidth / blockSize), height_(screenHeight / blockSize), blockSize_(blockSize), nbWaterBloc_(0) {

	std::cout << "Map dimensions : " << width_ << " x " << height_ << std::endl;
	currentGrid_.resize(height_, std::vector<Bloc*>(width_, nullptr));
	nextGrid_.resize(height_, std::vector<Bloc*>(width_, nullptr));
}

Map::~Map() {
	for (auto& row : currentGrid_) {
		for (auto& block : row) {
			delete block;
		}
	}
	for (auto& row : nextGrid_) {
		for (auto& block : row) {
			delete block;
		}
	}
	for (Fish* fish : fishes_) {
		delete fish;
	}
}

void Map::update() {

	// On construit la grille suivante que l'on remplace par la courante
	// Parcours de la grille du bas vers le haut pour la gravité

	// On ne fait pas les blocs d'eau pour le moment
	for (int y = height_ - 1; y >= 0; --y) {
		for (int x = 0; x < width_; ++x) {
			if (currentGrid_[y][x] && currentGrid_[y][x]->getType() != WATER) {
				currentGrid_[y][x]->update(this);
			}
		}
	}
	// On met à jour les blocs d'eau dans un second temps
	int nombre_water_bloc = nbWaterBloc_;
	int maxFishCount = nombre_water_bloc / 100; // 1 poisson pour 100 blocs d'eau MAX

	nbWaterBloc_ = 0;
	for (int y = height_ - 1; y >= 0; --y) {
		for (int x = 0; x < width_; ++x) {
			if (currentGrid_[y][x] && currentGrid_[y][x]->getType() == WATER) {
				currentGrid_[y][x]->update(this);
				nbWaterBloc_++;

				// on limite l'apparition spontannée de poissons
				if (fishes_.size() < maxFishCount && rand() % 500000 == 0) { // 0.0002% chance de spawn à chaque frame
					addFish(new Fish(x, y, "Steve", sf::Color(255, 140, 60, 255)));
				}
			}
		}
	}

	// On met à jour les entités
	for (int i = 0; i < fishes_.size();) {
		fishes_[i]->update(this);

		if (!fishes_[i]->isAlive()) {
			// fish est mort
			delete fishes_[i];
			fishes_.erase(fishes_.begin() + i); // debut + "numero" du poisson
		}
		else {
			i++;
		}
	}

	
	// Nettoyage de currentGrid_
	int nbBlocks = 0;
	for (auto& row : currentGrid_) {
		for (auto& block : row) {
			block = nullptr; // pas de fuite mémoire si on a bien gérer la suppression des blocs 
		}
	}

	// On échange currentGrid_ et nextGrid_
	std::vector<std::vector<Bloc*>> temp = currentGrid_;
	currentGrid_ = nextGrid_;
	nextGrid_ = temp;
}


// Dessin de la grille courante
void Map::draw(sf::RenderWindow& window) const {
	for (int y = 0; y < height_; ++y) {
		for (int x = 0; x < width_; ++x) {
			if (currentGrid_[y][x]) {
				currentGrid_[y][x]->draw(window, blockSize_);
			}
		}
	}
	for (Fish *fish : fishes_) {
		fish->draw(window, blockSize_);
	}

}

void Map::setBlocInCurrentFrame(int x, int y, Bloc* block) {
	if (inBounds(x, y)) {
		if (currentGrid_[y][x]) {
			delete currentGrid_[y][x]; // Libération de la mémoire
		}
		currentGrid_[y][x] = block;
	}
}

void Map::setBlocInNextFrame(int x, int y, Bloc* block) {
	if (inBounds(x, y)) {
		if (nextGrid_[y][x]) {
			delete nextGrid_[y][x]; // Libération de la mémoire
		}
		nextGrid_[y][x] = block;
	}
}

// Efface un bloc de la carte
void Map::removeBloc(int x, int y) {
	if (inBounds(x, y)) {
		delete currentGrid_[y][x]; // Libération de la mémoire
		currentGrid_[y][x] = nullptr;
	}
}

void Map::addFish(Fish *fish) {
	fishes_.push_back(fish);
}

// Efface tous les blocs de la carte
void Map::clear() {
	for (int y = 0; y < height_; ++y) {
		for (int x = 0; x < width_; ++x) {
			delete currentGrid_[y][x]; // Libération de la mémoire
			currentGrid_[y][x] = nullptr;
		}
		for (Fish* fish : fishes_) {
			delete fish;
		}
		fishes_.clear();
	}
}

// Récupère le bloc à la position (x, y)
Bloc* Map::getBlock(int x, int y) {
	if (inBounds(x, y)) {
		return currentGrid_[y][x];
	}
	return nullptr;
}
Bloc* Map::getBlockInNextGrid(int x, int y) {
	if (inBounds(x, y)) {
		return nextGrid_[y][x];
	}
	return nullptr;
}

// Vérifie les coords (x, y) sont dans la carte
bool Map::inBounds(int x, int y) const {
	return x >= 0 && x < width_ && y >= 0 && y < height_;
}
