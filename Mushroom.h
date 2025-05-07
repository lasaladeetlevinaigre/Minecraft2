#pragma once
#include <SFML/Graphics.hpp>
#include "bloc.h"

class Mushroom : public Bloc {
    int spreadCooldown_;
    int initialCooldown_;
    bool hooked_;
public:
    Mushroom(int x, int y, int initialCooldown, bool hooked);
    void update(Map* map);
};