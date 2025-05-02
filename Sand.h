#pragma once
#include <SFML/Graphics.hpp>
#include "Bloc.h"

class Sand : public Bloc {
public:
    Sand(int x, int y);
    void update(Map* map);
};