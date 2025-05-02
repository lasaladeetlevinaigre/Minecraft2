#include "Sand.h"
#include "Map.h"

Sand::Sand(int x, int y) : Bloc(x, y, SAND, sf::Color::Yellow) {}



void Sand::update(Map* map) {
    int x = getX();
    int y = getY();

    // En dessous
    if (map->inBounds(x, y + 1) && map->getBlock(x, y + 1) == nullptr) {
        map->setBlocInNextFrame(x, y + 1, this);
        setY(y + 1);
        return;
    }

    // Choisir al�atoirement entre gauche et droite
    bool canLeft = map->inBounds(x - 1, y + 1) && map->getBlock(x - 1, y + 1) == nullptr && map->getBlock(x - 1, y) == nullptr;
    bool canRight = map->inBounds(x + 1, y + 1) && map->getBlock(x + 1, y + 1) == nullptr && map->getBlock(x + 1, y) == nullptr;

    if (canLeft && canRight) {
        if (rand() % 2 == 0) {
            map->setBlocInNextFrame(x - 1, y + 1, this);
            setX(x - 1);
            setY(y + 1);
        }
        else {
            map->setBlocInNextFrame(x + 1, y + 1, this);
            setX(x + 1);
            setY(y + 1);
        }
        return;
    }
    else if (canLeft) {
        map->setBlocInNextFrame(x - 1, y + 1, this);
        setX(x - 1);
        setY(y + 1);
        return;
    }
    else if (canRight) {
        map->setBlocInNextFrame(x + 1, y + 1, this);
        setX(x + 1);
        setY(y + 1);
        return;
    }

    // Sinon, reste en place
    map->setBlocInNextFrame(x, y, this);
}