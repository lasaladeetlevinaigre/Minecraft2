#include "Stone.h"
#include "Map.h"

Stone::Stone(int x, int y) : Bloc(x, y, STONE, sf::Color(128, 128, 128)) {}

void Stone::update(Map* map) {
    map->setBlocInNextFrame(getX(), getY(), this);
}