#ifndef WATER_H
#define WATER_H

#include <SFML/Graphics.hpp>
#include "Bloc.h"

class Water : public Bloc {
	// Inertie
	bool wasGoingLeft_;
	bool wasGoingRight_;
public:
	// Constructeur
	Water(int x, int y);

	// Mettre à jour la propagation
	void update(Map* map) override;
};

#endif // !WATER_H