// Bloc.h
// Auteur : Antoine Horion
// Description :
// Classe de base pour les blocs du jeu
// Chaque bloc a une couleur, une position (x, y) et un type (pierre, sable, champignon,eau)
// La classe est abstraite et doit être dérivée pour créer des blocs spécifiques


#ifndef BLOC_H
#define BLOC_H

#include <SFML/Graphics.hpp>

class Map;

// Enumération pour les types de blocs
enum BlocType{
	STONE,
	SAND,
	MUSHROOM,
	WATER
};

class Bloc {
	sf::Color color_;
	int x_;
	int  y_;
	BlocType type_;

public:
	// Constructeur
	Bloc(int x, int y, BlocType type, sf::Color color) : color_(color), type_(type), x_(x), y_(y) {}

	// Méthode virtuelle pure pour mettre à jour le bloc
	virtual void update(Map* map) = 0;
	
	void setX(int x) { x_ = x; }
	void setY(int y) { y_ = y; }
	void setColor(sf::Color color) { color_ = color; }

	// Méthode pour afficher le bloc
	void draw(sf::RenderWindow& window, int blockSize) const;

	int getX() const { return x_; }
	int getY() const { return y_; }
	sf::Color getColor() const { return color_; }
	BlocType getType() const { return type_; }
};

#endif // !BLOC_H