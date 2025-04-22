#include "Map.h"
#include "Bloc.h"  // Inclusion complète ici

Map::Map(int screenWidth, int screenHeight, int blockSize)
	: width_(screenWidth / blockSize), height_(screenHeight / blockSize), blockSize_(blockSize) {
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
	std::cout << "Map dimensions : " << width_ << " x " << height_ << std::endl;
	currentGrid_.resize(height_, std::vector<Bloc*>(width_, nullptr));
	nextGrid_.resize(height_, std::vector<Bloc*>(width_, nullptr));

	currentGrid_[20][20] = new Bloc(20, 20, sf::Color::Red);
}

int countNonNulBlocks(const std::vector<std::vector<Bloc*>>& grid) {
	int count = 0;
	for (const auto& row : grid) {
		for (const auto& block : row) {
			if (block != nullptr) {
				count++;
			}
		}
	}
	return count;
}


void Map::update() {
	for (int y = height_ - 1; y >= 0; --y) {
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

void Map::setBlocInCurrentFrame(int x, int y, Bloc* block) {
	if (inBounds(x, y)) {
		currentGrid_[y][x] = block;
	}
}

void Map::setBlocInNextFrame(int x, int y, Bloc* block) {
	if (inBounds(x, y)) {
		nextGrid_[y][x] = block;
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

	// Nettoyage de currentGrid_
	int nb = 0;
	for (auto& row : currentGrid_) {
		for (auto& block : row) {
			if(block)
				nb++;
			block = nullptr; // pas de fuite mémoire si on a bien gérer la création de nextGrid
		}
	}
	std::vector<std::vector<Bloc*>> temp = currentGrid_;
	currentGrid_ = nextGrid_;
	nextGrid_ = temp;
	std::cout << nb << " blocks on grid" << std::endl;
}