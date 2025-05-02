#include "Mushroom.h"
#include "Map.h"

Mushroom::Mushroom(int x, int y, int spreadCooldown = 30) : Bloc(x, y, sf::Color::Red) {
    spreadCooldown_ = spreadCooldown;
}

void Mushroom::update(Map& map) {
    if (--spreadCooldown_<= 0) {
        spreadCooldown_ = 30;

        for (int dx = -1; dx <= 1; dx++) {
            for (int dy = -1; dy <= 1; dy++) {
                if (dx == 0 && dy == 0) continue;

                int nx = x_ + dx;
                int ny = y_ + dy;

                if (map.inBounds(nx, ny)) {
                    Bloc* adjacent = map.getBlock(nx, ny);

                    if (adjacent == nullptr) {
                        for (int rx = -1; rx <= 1; rx++) {
                            for (int ry = -1; ry <= 1; ry++) {
                                if (rx == 0 && ry == 0) continue;
                                int xx = nx + rx;
                                int yy = ny + ry;
                                if (map.inBounds(xx, yy) && dynamic_cast<Stone*>(map.getBlock(xx, yy))) {
                                    map.setBlocInNextFrame(nx, ny, new Mushroom(nx, ny));
                                    break;
                                }
                            }
                        }
                    }
                }
            }
        }
        
    }
    map.setBlocInNextFrame(x_, y_, this);
}