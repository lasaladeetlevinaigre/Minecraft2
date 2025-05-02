#include "Map.h"
#include "Bloc.h"
#include "Sand.h"
#include "Stone.h"
#include "Mushroom.h"

Map::Map(int screenWidth, int screenHeight, int blockSize)
	: width_(screenWidth / blockSize), height_(screenHeight / blockSize), blockSize_(blockSize) {

	// Initialisation de la grille
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
	// Parcours de la grille du bas vers le haut
	for (int y = height_ - 1; y >= 0; --y) {
		for (int x = 0; x < width_; ++x) {

			if (currentGrid_[y][x]) {
				currentGrid_[y][x]->update(this);
			}
		}
	}

	// Nettoyage de currentGrid_
	int nbBlocks = 0;
	for (auto& row : currentGrid_) {
		for (auto& block : row) {
			block = nullptr; // pas de fuite mémoire si on a bien gérer la suppression des blocs 
		}
	}

	std::vector<std::vector<Bloc*>> temp = currentGrid_;
	currentGrid_ = nextGrid_;
	nextGrid_ = temp;
}

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
void Map::removeBloc(int x, int y) {
	if (inBounds(x, y)) {
		delete currentGrid_[y][x]; // Libération de la mémoire
		currentGrid_[y][x] = nullptr;
	}
}

void Map::clear() {
	for (int y = 0; y < height_; ++y) {
		for (int x = 0; x < width_; ++x) {
			delete currentGrid_[y][x]; // Libération de la mémoire
			currentGrid_[y][x] = nullptr;
		}
	}
}


Bloc* Map::getBlock(int x, int y) {
	if (inBounds(x, y)) {
		return currentGrid_[y][x];
	}
	return nullptr;
}
bool Map::inBounds(int x, int y) const {
	return x >= 0 && x < width_ && y >= 0 && y < height_;
}
