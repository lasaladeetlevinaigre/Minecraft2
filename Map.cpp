// Auteur : Benjamin Escuder

#include "Map.h"
#include "Bloc.h"
#include "Sand.h"
#include "Stone.h"
#include "Mushroom.h"


// Initialisation de la grille
Map::Map(int screenWidth, int screenHeight, int blockSize)
	: width_(screenWidth / blockSize), height_(screenHeight / blockSize), blockSize_(blockSize) {

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
}

void Map::update() {

	// On construit la grille suivante que l'on remplace par la courante
	// Parcours de la grille du bas vers le haut pour la gravit�

	// On ne fait pas les blocs d'eau pour le moment
	for (int y = height_ - 1; y >= 0; --y) {
		for (int x = 0; x < width_; ++x) {
			if (currentGrid_[y][x] && currentGrid_[y][x]->getType() != WATER) {
				currentGrid_[y][x]->update(this);
			}
		}
	}
	for (int y = height_ - 1; y >= 0; --y) {
		for (int x = 0; x < width_; ++x) {
			if (currentGrid_[y][x] && currentGrid_[y][x]->getType() == WATER) {
				currentGrid_[y][x]->update(this);
			}
		}
	}
	
	// Nettoyage de currentGrid_
	int nbBlocks = 0;
	for (auto& row : currentGrid_) {
		for (auto& block : row) {
			block = nullptr; // pas de fuite m�moire si on a bien g�rer la suppression des blocs 
		}
	}

	// On �change currentGrid_ et nextGrid_
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
}

void Map::setBlocInCurrentFrame(int x, int y, Bloc* block) {
	if (inBounds(x, y)) {
		if (currentGrid_[y][x]) {
			delete currentGrid_[y][x]; // Lib�ration de la m�moire
		}
		currentGrid_[y][x] = block;
	}
}

void Map::setBlocInNextFrame(int x, int y, Bloc* block) {
	if (inBounds(x, y)) {
		if (nextGrid_[y][x]) {
			delete nextGrid_[y][x]; // Lib�ration de la m�moire
		}
		nextGrid_[y][x] = block;
	}
}

// Efface un bloc de la carte
void Map::removeBloc(int x, int y) {
	if (inBounds(x, y)) {
		delete currentGrid_[y][x]; // Lib�ration de la m�moire
		currentGrid_[y][x] = nullptr;
	}
}

// Efface tous les blocs de la carte
void Map::clear() {
	for (int y = 0; y < height_; ++y) {
		for (int x = 0; x < width_; ++x) {
			delete currentGrid_[y][x]; // Lib�ration de la m�moire
			currentGrid_[y][x] = nullptr;
		}
	}
}

// R�cup�re le bloc � la position (x, y)
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

// V�rifie les coords (x, y) sont dans la carte
bool Map::inBounds(int x, int y) const {
	return x >= 0 && x < width_ && y >= 0 && y < height_;
}
