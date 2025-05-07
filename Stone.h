// Stone.h
// Auteur : Antoine Horion
// Description : La classe Stone h�rite de la classe Bloc et repr�sente un bloc de pierre

#ifndef STONE_H
#define STONE_H

#include <SFML/Graphics.hpp>
#include "Bloc.h"

class Stone : public Bloc {
public:
    Stone(int x, int y);
    void update(Map* map);
};

#endif // !STONE_H