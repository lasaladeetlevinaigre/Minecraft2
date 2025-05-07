// Game.h
// Auteur : Benjamin Escuder
// Description : Classe principale du jeu, g�re le rendu, l'affichage de la fen�tre, le menu, les �v�nements


#ifndef GAME_H
#define GAME_H
#include <SFML/Graphics.hpp>
#include "Map.h"
#include "Menu.h"


class Game
{
	sf::RenderWindow window_;
	int uiWidth_;

	int width_, height_; // Taille de la fen�tre
	int blockSize_;	     // Nombre de pixels par bloc

	Map map_;
	Menu menu_;

	bool isRunning_;
public:
	// Constructeur et destructeur
	Game();
	~Game();

	// G�re la lecture/pause de la simulation
	bool isRunning() const { return isRunning_; }
	void setRunning(bool running) { isRunning_ = running; }

	void run(); // G�re l'initialisation de la fen�tre et la simulation

	// Accesseurs
	int getWidth() const { return width_; }
	int getHeight() const { return height_; }
};

#endif // GAME_H