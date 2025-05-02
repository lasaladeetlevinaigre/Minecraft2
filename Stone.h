#pragma once
#include <SFML/Graphics.hpp>
#include "Bloc.h"

class Stone : public Bloc {
public:
    Stone(int x, int y);
    void update(Map& map);
};