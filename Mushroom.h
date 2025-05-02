#pragma once
#include <SFML/Graphics.hpp>
#include "bloc.h"

class Mushroom : public Bloc {
    int spreadCooldown_;
    int initialCooldown_;
public:
    Mushroom(int x, int y, int initialCooldown);
    void update(Map* map);
};