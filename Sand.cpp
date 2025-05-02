#include "Sand.h"
#include "Map.h"

Sand::Sand(int x, int y) : Bloc(x, y, sf::Color::Yellow) {}

void Sand::update(Map& map) {
    Bloc* dessous = map.getBlock(x_, y_ + 1);
    Bloc* dgauche = map.getBlock(x_ - 1, y_ + 1);
    Bloc* ddroit = map.getBlock(x_ + 1, y_ + 1);
    if (dessous == nullptr) {
        map.setBlocInNextFrame(x_, y_ + 1,this);
    }
    else if (dgauche == nullptr) {
        map.setBlocInNextFrame(x_ - 1, y_ + 1, this);
    }

    else if (ddroit == nullptr) {
        map.setBlocInNextFrame(x_ + 1, y_ + 1, this);
    }
    else {
        map.setBlocInNextFrame(x_, y_, this);
    }
}