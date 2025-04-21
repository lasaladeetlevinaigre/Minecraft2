#pragma once
#include "Bloc.h"
#include "Map.h"
#include <SFML/Graphics.hpp>

class Sand : public Bloc {
private:
    float density;  // Propri�t� sp�cifique au sable

public:
    Sand(int x, int y)
        : Bloc(x, y, sf::Color(194, 178, 128)), density(1.5f) {}  // Couche sable

	void update(Map& map) override; // �crase la d�finition de Bloc::update
};