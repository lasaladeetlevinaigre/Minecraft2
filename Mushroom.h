// Mushroom.h
// Auteur : Antoine Horion
// Description : La classe Mushroom h�rite de la classe Bloc et
// repr�sente un champignon qui se propage sur la carte

#ifndef MUSHROOM_H
#define MUSHROOM_H

#include <SFML/Graphics.hpp>
#include "bloc.h"

class Mushroom : public Bloc {
	// Temps avant que le champignon ne se propage
	int spreadCooldown_;
	int initialCooldown_;
	bool hooked_; // Permet de savoir si un champignon a d�j� �t� accroch� � une pierre
public:

	// Constructeur
	Mushroom(int x, int y, int initialCooldown);

	// Mettre � jour la propagation
	void update(Map* map);
};

#endif // !MUSHROOM_H