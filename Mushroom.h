#pragma once
#include <SFML/Graphics.hpp>
#include "bloc.h"

class Mushroom : public Bloc {
    int spreadCooldown_; 
public:
    Mushroom(int x, int y, int spreadCooldown);
    void update(Map& map);
};