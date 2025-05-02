#include "Mushroom.h"
#include "Map.h"

Mushroom::Mushroom(int x, int y, int initialCooldown) : Bloc(x, y, MUSHROOM, sf::Color::Magenta) {
    initialCooldown_ = initialCooldown;
    spreadCooldown_ = initialCooldown_;
}
void Mushroom::update(Map* map) {
    if (--spreadCooldown_ <= 0) {
        spreadCooldown_ = 30;

        for (int dx = -1; dx <= 1; dx++) {
            for (int dy = -1; dy <= 1; dy++) {
                if (dx == 0 && dy == 0) continue;

                int nx = getX() + dx;
                int ny = getY() + dy;

                if (map->inBounds(nx, ny)) {
                    Bloc* adjacent = map->getBlock(nx, ny);

                    if (adjacent == nullptr) {
                        // Vérifie s'il y a des blocs STONE autour de la case vide
                        int stoneCount = 0;
                        for (int rx = -1; rx <= 1; rx++) {
                            for (int ry = -1; ry <= 1; ry++) {
                                if (rx == 0 && ry == 0) continue;
                                int xx = nx + rx;
                                int yy = ny + ry;
                                if (map->inBounds(xx, yy)) {
                                    Bloc* neighbor = map->getBlock(xx, yy);
                                    if (neighbor && neighbor->getType() == STONE) {
                                        stoneCount++;
                                    }
                                }
                            }
                        }
                        // Si au moins un STONE autour, on propage un champignon
                        if (stoneCount > 0) {
                            map->setBlocInNextFrame(nx, ny, new Mushroom(nx, ny, initialCooldown_));
                        }
                    }
                }
            }
        }
    }

    // Vérifie s'il y a un bloc vide en dessous et aucune stone autour
    int x = getX();
    int y = getY();
    int stoneNeighbors = 0;
    for (int dx = -1; dx <= 1; dx++) {
        for (int dy = -1; dy <= 1; dy++) {
            if (dx == 0 && dy == 0) continue;
            int nx = x + dx;
            int ny = y + dy;
            if (map->inBounds(nx, ny)) {
                Bloc* b = map->getBlock(nx, ny);
                if (b && b->getType() == STONE) {
                    stoneNeighbors++;
                }
            }
        }
    }

    if (stoneNeighbors == 0 && map->inBounds(x, y + 1) && map->getBlock(x, y + 1) == nullptr) {
        setY(y + 1);
    }

    map->setBlocInNextFrame(getX(), getY(), this);
}
