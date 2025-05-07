// Auteur : Benjamin Escuder

#include "Game.h"
#include "Bloc.h"

// Initialise les diff�rents �l�ments du jeu
Game::Game() : width_(1600), height_(900), uiWidth_(200), blockSize_(10),
isRunning_(false), map_(width_ - uiWidth_, height_, blockSize_), menu_(this, &map_, uiWidth_)
{
	window_.create(sf::VideoMode(width_, height_), "Minecraft2", sf::Style::Close);
	window_.setFramerateLimit(120);
}

// Destructeur
Game::~Game()
{
}

// Boucle principale du jeu
void Game::run()
{
	while (window_.isOpen())
	{
		// G�re les �v�nements de la fen�tre
		sf::Event event;
		while (window_.pollEvent(event))
		{
			menu_.handleEvent(event, window_); // Envoie l'event au menu qui le traite
		}

		if (isRunning_)
		{
			// G�re la logique du jeu
			map_.update();
		}

		// G�re le rendu de la fen�tre
		window_.clear(sf::Color::Black);
		menu_.drawUI(window_);
		map_.draw(window_);
		window_.display();
	}
}