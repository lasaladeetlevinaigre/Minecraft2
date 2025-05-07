// Game.h
// Auteur : Benjamin Escuder
// Description : Classe principale du jeu, gère le rendu, l'affichage de la fenêtre, le menu, les événements


#ifndef GAME_H
#define GAME_H
#include <SFML/Graphics.hpp>
#include "Map.h"
#include "Menu.h"


class Game
{
	sf::RenderWindow window_;
	int uiWidth_;

	int width_, height_; // Taille de la fenêtre
	int blockSize_;	     // Nombre de pixels par bloc

	Map map_;
	Menu menu_;

	bool isRunning_;
public:
	// Constructeur et destructeur
	Game();
	~Game();

	// Gère la lecture/pause de la simulation
	bool isRunning() const { return isRunning_; }
	void setRunning(bool running) { isRunning_ = running; }

	void run(); // Gère l'initialisation de la fenêtre et la simulation

	// Accesseurs
	int getWidth() const { return width_; }
	int getHeight() const { return height_; }
};

#endif // GAME_H