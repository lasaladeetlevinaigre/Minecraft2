// Sand.h
// Auteur : Antoine Horion
// Description : La classe Sand h�rite de la classe Bloc et repr�sente un bloc de sable

#ifndef SAND_H
#define SAND_H

#include <SFML/Graphics.hpp>
#include "Bloc.h"

class Sand : public Bloc {
public:
	// Constructeur
    Sand(int x, int y);

	// Mettre � jour la propagation
    void update(Map* map);
};

#endif // !SAND_H