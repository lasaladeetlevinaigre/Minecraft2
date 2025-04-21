#include "Map.h"
#include "Bloc.h"  // Inclusion complète ici

Map::Map()
    : width_(800), height_(600), blockSize_(20) {
    initGrid();
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
void Map::initGrid() {
	currentGrid_.resize(height_, std::vector<Bloc*>(width_, nullptr));
	nextGrid_.resize(height_, std::vector<Bloc*>(width_, nullptr));
}
void Map::update() {
	for (int y = 0; y < height_; ++y) {
		for (int x = 0; x < width_; ++x) {
			if (currentGrid_[y][x]) {
				currentGrid_[y][x]->update(*this);
			}
		}
	}
	swapGrids();
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
void Map::setBloc(int x, int y, Bloc* block) {
	if (inBounds(x, y)) {
		currentGrid_[y][x] = block;
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
void Map::swapGrids() {
	std::swap(currentGrid_, nextGrid_);
	for (auto& row : nextGrid_) {
		for (auto& block : row) {
			delete block;
			block = nullptr;
		}
	}
}