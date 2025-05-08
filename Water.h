// Water.h
// Auteur : Benjamin Escuder
// Description : La classe Water h�rite de la classe Bloc et repr�sente un bloc d'eau

#ifndef WATER_H
#define WATER_H

#include <SFML/Graphics.hpp>
#include "Bloc.h"

class Water : public Bloc {
	// Inertie issue du d�placement pr�cedent
	bool wasGoingLeft_;
	bool wasGoingRight_;
public:
	// Constructeur
	Water(int x, int y);

	// Mettre � jour la propagation
	void update(Map* map) override;
};

#endif // !WATER_H