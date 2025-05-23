// Mushroom.cpp
// Auteur : Antoine Horion
#include "Mushroom.h"
#include "Map.h"

Mushroom::Mushroom(int x, int y, int initialCooldown) : Bloc(x, y, MUSHROOM, sf::Color::Magenta) {
    initialCooldown_ = initialCooldown;
    spreadCooldown_ = initialCooldown_;
    hooked_ = false;
}
void Mushroom::update(Map* map) {
    // Compte les nombre de voisins STONE
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

    // Le champignon s'accroche s'il a un voisin STONE
    if (stoneNeighbors > 0) {
        hooked_ = true;
    }

    //Comportement non accroch�
    if (hooked_ == false) {
        // Tombe si pas de voisin STONE et vide ou WATER en en dessous
        Bloc* below = map->getBlock(x, y + 1);
        if (stoneNeighbors == 0 && map->inBounds(x, y + 1) && (below == nullptr || (below && below->getType() == WATER))) {
            setY(y + 1);
        }
        map->setBlocInNextFrame(getX(), getY(), this);
    }
    //Comportement accroch�
    if (hooked_ == true) {
        if (stoneNeighbors > 0) {
            map->setBlocInNextFrame(getX(), getY(), this);
        }
        else {
            map->removeBloc(getX(), getY());
        }
    }

    //Propagation
    if (--spreadCooldown_ <= 0) {
        spreadCooldown_ = initialCooldown_;

        for (int dx = -1; dx <= 1; dx++) {
            for (int dy = -1; dy <= 1; dy++) {
                if (dx == 0 && dy == 0) continue;

                int nx = getX() + dx;
                int ny = getY() + dy;

                if (map->inBounds(nx, ny)) {
                    Bloc* adjacent = map->getBlock(nx, ny);
                    //Si le bloc adjaent est vide ou de l'eau
                    if (adjacent == nullptr || (adjacent && adjacent->getType() == WATER)) {
                        // V�rifie s'il y a des blocs STONE autour de la case libre
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
                        // Si au moins un STONE autour, on propage un champignon sur cette vase vide
                        if (stoneCount > 0) {
                            map->setBlocInNextFrame(nx, ny, new Mushroom(nx, ny, initialCooldown_));
                        }
                    }
                }
            }
        }
    }
}




