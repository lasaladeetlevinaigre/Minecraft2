// Map.h
// Auteur : Benjamin Escuder
// Description : La classe Map gère la grille de blocs, leur rendu et leur mise à jour

#ifndef MAP_H
#define MAP_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

class Bloc;
class Fish;

class Map
{
private:
	// Taille de la carte
	int width_;
	int height_;

	// Taille d'un bloc en pixel
    int blockSize_;

	// Grille de blocs
    std::vector<std::vector<Bloc*>> currentGrid_;
    std::vector<std::vector<Bloc*>> nextGrid_;

	int nbWaterBloc_;
	std::vector<Fish *> fishes_;

public:
	// Constructeur et destructeur
	Map(int screenWidth, int screenHeight, int blockSize);
	~Map();

	void update(); // Gère la mise à jour de la carte
	void draw(sf::RenderWindow& window) const; // Gère le rendu de la carte

	void setBlocInNextFrame(int x, int y, Bloc* bloc); 
	void setBlocInCurrentFrame(int x, int y, Bloc* bloc);
	void removeBloc(int x, int y);

	void addFish(Fish *fish);

	void clear(); // Efface la carte

	bool inBounds(int x, int y) const; // Vérifie si les coordonnées sont dans les limites de la carte

	// Accesseurs
	Bloc* getBlock(int x, int y);
	Bloc* getBlockInNextGrid(int x, int y);
	int getWidth() const { return width_; }
	int getHeight() const { return height_; }
	int getBlockSize() const { return blockSize_; }
};


#endif // !MAP_H
