#include "Sand.h"

void Sand::update(Map& map) {
	// regles d'actualisation


	map.setBloc(this->getX(), this->getY(), nullptr); // Enlève le bloc de sable de sa position actuelle

	
	// Place le bloc de sable à la nouvelle position
	int newX = this->getX();
	int newY = this->getY() + 1; // Descend d'une case
	map.setBloc(newX, newY, this);

	return;
}