// Game.cpp
// Auteur : Benjamin Escuder

#include "Game.h"
#include "Bloc.h"

// Initialise les différents éléments du jeu
Game::Game() : width_(1600), height_(900), uiWidth_(200), blockSize_(10),
isRunning_(false), map_(width_ - uiWidth_, height_, blockSize_), menu_(this, &map_, uiWidth_)
{
	window_.create(sf::VideoMode(width_, height_), "Minecraft2", sf::Style::Close);
	window_.setFramerateLimit(120);

	// Affichage des commandes dans la console
	std::cout << "================== Commandes de la simulation ====================\n";
	std::cout << "[ESPACE]  : Mettre en pause la simulation\n";
	std::cout << "[ECHAP]   : Quitter la simulation\n";
	std::cout << "[N]       : Avancer d'une frame\n";
	std::cout << "[+] / [-] : Modifier la taille de la brosse de dessin\n";
	std::cout << "[R]       : Ajouter un bloc de sable aleatoirement sur la carte\n";
	std::cout << "[C]       : Effacer la carte\n";
	std::cout << "[S]       : Placer du sable\n";
	std::cout << "[P]       : Placer une pierre\n";
	std::cout << "[M]       : Placer un champignon\n";
	std::cout << "[W]       : Placer de l'eau\n";
	std::cout << "[F]       : Faire apparaitre un poisson aleatoirement sur la carte\n";
	std::cout << "==================================================================\n";


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
		// Gère les événements de la fenêtre
		sf::Event event;
		while (window_.pollEvent(event))
		{
			menu_.handleEvent(event, window_); // Envoie l'event au menu qui le traite
		}

		if (isRunning_)
		{
			// Gère la logique du jeu
			map_.update();
		}

		// Gère le rendu des elements
		window_.clear(sf::Color::Black);
		map_.draw(window_);
		menu_.drawUI(window_);
		window_.display();
	}
}