// Auteur : Benjamin Escuder et Antoine Horion

#include "Menu.h"
#include "Game.h"
#include "Map.h"
#include "Bloc.h"
#include "Sand.h"
#include "Stone.h"
#include "Mushroom.h"
#include "Water.h"
#include "Fish.h"
#include <iostream>


// Inverse l'état du jeu
void toggleRunning(Game* game) {
	if (game->isRunning()) {
		std::cout << "Game paused" << std::endl;
		game->setRunning(false);
	}
	else {
		std::cout << "Game resumed" << std::endl;
		game->setRunning(true);
	}
}

// Constructeur de la classe Menu
Menu::Menu(Game* game, Map* map, int uiWidth) : game_(game), map_(map), uiWidth_(uiWidth), state_(MenuState::Idle), isDrawingNow_(false), brushRadius_(0) {
	// Initialiser l'état du menu
	state_ = MenuState::Idle;
	isDrawingNow_ = false;
	brushRadius_ = 1;
	mushroomCD_ = 30;

	// Initialiser la largeur de l'interface utilisateur
	uiWidth_ = uiWidth;

	// Initialiser la police
	if (!font_.loadFromFile("Arial.ttf")) {
		std::cerr << "Error loading font" << std::endl;
	}
	createButtons();

}

void Menu::createButtons() {
	// Créer les boutons avec leurs actions
	/*
	Rappel constructeur Button :
	Button(ButtonAction action,
			int x, int y,
			int width, int height,
			const std::string & label,
			const sf::Font & font,
			int fontSize,
			sf::Color textColor,
			sf::Color outlineColor,
			std::vector<sf::Color> bgColor);
	*/

	int y = 10; // Position y de départ pour les boutons

	Button button_toggle_running = Button(ButtonAction::ToggleRunning,
		game_->getWidth() - uiWidth_ + 10, y,
		uiWidth_ - 20, 30,
		"Pause",
		font_,
		18,
		sf::Color::White,
		sf::Color::Black,
		std::vector<sf::Color>{ sf::Color(150, 150, 150), sf::Color(80, 80, 80) });

	buttons_.push_back(button_toggle_running);
	y += 40; // Espace entre les boutons


	buttons_.push_back(Button(ButtonAction::ShowBrushSize,
		game_->getWidth() - uiWidth_ + 10, y,
		uiWidth_ - 20, 30,
		"Brush size: 2",
		font_,
		18,
		sf::Color::White,
		sf::Color(50, 50, 50, 200),
		std::vector<sf::Color>{ sf::Color(50, 50, 50, 200), sf::Color(50, 50, 50, 200) }));
	y += 40;


	// Modifier la taille du pinceau
	buttons_.push_back(Button(ButtonAction::DecreaseBrushRadius,
		game_->getWidth() - uiWidth_ + 10, y,
		uiWidth_/2 - 15, 30,
		"Decrease",
		font_,
		18,
		sf::Color::White,
		sf::Color::Black,
		std::vector<sf::Color>{ sf::Color(80, 80, 80), sf::Color(150, 150, 150) }));
	buttons_.push_back(Button(ButtonAction::IncreaseBrushRadius,
		game_->getWidth() - uiWidth_ + uiWidth_/2 + 5, y,
		uiWidth_/2 - 15, 30,
		"Increase",
		font_,
		18,
		sf::Color::White,
		sf::Color::Black,
		std::vector<sf::Color>{ sf::Color(80, 80, 80), sf::Color(150, 150, 150) }));
	y += 40;

	// Affichage actuel du cooldown du champignon 
	buttons_.push_back(Button(ButtonAction::ShowMushroomCooldown,
		game_->getWidth() - uiWidth_ + 10, y,
		uiWidth_ - 20, 30,
		"Mushroom cooldown: " + std::to_string(mushroomCD_),
		font_,
		18,
		sf::Color::White,
		sf::Color(50, 50, 50, 200),
		std::vector<sf::Color>{ sf::Color(50, 50, 50, 200), sf::Color(50, 50, 50, 200) }));
	y += 40;

	// Bouton pour diminuer le cooldown
	buttons_.push_back(Button(ButtonAction::DecreaseMushroomCD,
		game_->getWidth() - uiWidth_ + 10, y,
		uiWidth_ / 2 - 15, 30,
		"Decrease",
		font_,
		18,
		sf::Color::White,
		sf::Color::Black,
		std::vector<sf::Color>{ sf::Color(80, 80, 80), sf::Color(150, 150, 150) }));

	// Bouton pour augmenter le cooldown
	buttons_.push_back(Button(ButtonAction::IncreaseMushroomCD,
		game_->getWidth() - uiWidth_ + uiWidth_ / 2 + 5, y,
		uiWidth_ / 2 - 15, 30,
		"Increase",
		font_,
		18,
		sf::Color::White,
		sf::Color::Black,
		std::vector<sf::Color>{ sf::Color(80, 80, 80), sf::Color(150, 150, 150) }));
	y += 40;



	buttons_.push_back(Button(ButtonAction::AddSandBloc,
		game_->getWidth() - uiWidth_ + 10, y,
		uiWidth_ - 20, 30,
		"Place Sand",
		font_,
		18,
		sf::Color::White,
		sf::Color::Black,
		std::vector<sf::Color>{ sf::Color(80, 80, 80), sf::Color(150, 150, 150) }));
	y += 40;

	buttons_.push_back(Button(ButtonAction::AddStoneBloc,
		game_->getWidth() - uiWidth_ + 10, y,
		uiWidth_ - 20, 30,
		"Place Stone",
		font_,
		18,
		sf::Color::White,
		sf::Color::Black,
		std::vector<sf::Color>{ sf::Color(80, 80, 80), sf::Color(150, 150, 150) }));
	y += 40;

	buttons_.push_back(Button(ButtonAction::AddMushroomBloc,
		game_->getWidth() - uiWidth_ + 10, y,
		uiWidth_ - 20, 30,
		"Place Mushroom",
		font_,
		18,
		sf::Color::White,
		sf::Color::Black,
		std::vector<sf::Color>{ sf::Color(80, 80, 80), sf::Color(150, 150, 150) }));
	y += 40;

	buttons_.push_back(Button(ButtonAction::AddWaterBloc,
		game_->getWidth() - uiWidth_ + 10, y,
		uiWidth_ - 20, 30,
		"Place Water",
		font_,
		18,
		sf::Color::White,
		sf::Color::Black,
		std::vector<sf::Color>{ sf::Color(80, 80, 80), sf::Color(150, 150, 150) }));
	y += 40;

	buttons_.push_back(Button(ButtonAction::RemoveBloc,
		game_->getWidth() - uiWidth_ + 10, y,
		uiWidth_ - 20, 30,
		"Remove Block",
		font_,
		18,
		sf::Color::White,
		sf::Color::Black,
		std::vector<sf::Color>{ sf::Color(80, 80, 80), sf::Color(150, 150, 150) }));
	y += 40;

	buttons_.push_back(Button(ButtonAction::ClearMap,
		game_->getWidth() - uiWidth_ + 10, y,
		uiWidth_ - 20, 30,
		"Clear Map",
		font_,
		18,
		sf::Color::White,
		sf::Color::Black,
		std::vector<sf::Color>{ sf::Color(80, 80, 80), sf::Color(150, 150, 150) }));
	y += 40;

	buttons_.push_back(Button(ButtonAction::Quit,
		game_->getWidth() - uiWidth_ + 10, y,
		uiWidth_ - 20, 30,
		"Quit",
		font_,
		18,
		sf::Color::White,
		sf::Color::Black,
		std::vector<sf::Color>{ sf::Color(80, 80, 80), sf::Color(150, 150, 150) }));
	y += 40;

}

void Menu::drawUI(sf::RenderWindow& window) const {

	// Définir un rectangle background
	sf::RectangleShape rect_;
	rect_.setSize(sf::Vector2f(uiWidth_, game_->getHeight()));
	rect_.setPosition(game_->getWidth() - uiWidth_, 0);
	rect_.setFillColor(sf::Color(50, 50, 50, 200));
	window.draw(rect_);

	// Dessiner chaque bouton par dessus
	for (auto button : buttons_) {
		button.draw(window);
	}
}


// Place un bloc de sable aléatoirement sur la carte
void summonRandomSand(Map* map) {
	int x = rand() % map->getWidth();
	int y = rand() % map->getHeight();
	if (map->inBounds(x, y)) {
		map->setBlocInCurrentFrame(x, y, new Sand(x, y));
	}
}

// Place un poisson aléatoirement sur la carte
void summonRandomFish(Map* map) {
	// on essaye 100 cases max pour placer un poisson
	for (int i = 0; i < 100; ++i) {
		int x = rand() % map->getWidth();
		int y = rand() % map->getHeight();

		if (!map->inBounds(x, y))
			continue;

		Bloc* bloc = map->getBlock(x, y);
		if (bloc && bloc->getType() == WATER) {
			map->addFish(new Fish(x, y, "Steve", sf::Color(255, 140, 60, 255)));
			break;
		}
	}
}

// Méthode pour gérer un evenement
void Menu::handleEvent(const sf::Event& event, sf::RenderWindow& window) {

	// Fermer le jeu
	if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) {
		std::cout << "Game closed" << std::endl;
		game_->setRunning(false);
		window.close();
	}

	// Mettre en pause / lecture
	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space) {
		toggleRunning(game_);
		for (auto& button : buttons_) {
			if (button.getAction() == ButtonAction::ToggleRunning)
				button.isSelected() ? button.setSelected(false) : button.setSelected(true);
		}
	}

	// Effacer la map avec [C]
	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::C) {
		clearingMap();
	}

	// Next frame avec [N]
	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::N) {
		map_->update();
	}

	// Faire apparaitre un bloc de sable aléatoirement avec [R]
	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::R) {
		summonRandomSand(map_);
	}

	// Faire apparaitre un poisson aléatoirement avec [F]
	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::F) {
		summonRandomFish(map_);
	}

	// Entrer en mode édition de sable avec [S]
	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::S) {
		setEditingSand();
	}

	// Entrer en mode édition de pierre avec [P]
	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::P) {
		setEditingStone();
	}

	// Entrer en mode édition de champignon avec [M]
	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::M) {
		setEditingMushroom();
	}

	// Entrer en mode édition de eau avec [W]
	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::W) {
		setEditingWater();
	}

	// Entrer en mode démolition avec [B]
	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::B) {
		setRemovingBloc();
	}
	

	// Modifier la taille de la brosse avec + et -
	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Add) {
		if (brushRadius_ < 9)
			brushRadius_++;
		for (auto& b : buttons_)
			if (b.getAction() == ButtonAction::ShowBrushSize)
				b.setText("Brush size: " + std::to_string(brushRadius_ * 2 + 1));
	}
	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Subtract) {
		if (brushRadius_ > 0)
			brushRadius_--;
		for (auto& b : buttons_)
			if (b.getAction() == ButtonAction::ShowBrushSize)
				b.setText("Brush size: " + std::to_string(brushRadius_ * 2 + 1));
	}


	// On commence à dessiner avec la souris
	if (event.type == sf::Event::MouseButtonPressed) {
		// Vérifier si le curseur est sur la carte
		if (event.mouseButton.x < game_->getWidth() - uiWidth_ && state_ != MenuState::Idle) {
			isDrawingNow_ = true;
	
		}
	}
	
	// Déplacement de la souris ==> on est peut etre en train de dessiner
	if (event.type == sf::Event::MouseMoved) {

		// Vérifier si le curseur est sur la carte
		if (event.mouseMove.x < game_->getWidth() - uiWidth_ && isDrawingNow_) {
			int x = event.mouseMove.x / map_->getBlockSize();
			int y = event.mouseMove.y / map_->getBlockSize();
			if (map_->inBounds(x, y)) {

				switch (state_) {
				case MenuState::EditingSand:
					// Adapter à la taille du pinceau
					for (int i = -brushRadius_; i <= brushRadius_; ++i) {
						for (int j = -brushRadius_; j <= brushRadius_; ++j) {
							if (map_->inBounds(x + i, y + j)) {
								map_->setBlocInCurrentFrame(x + i, y + j, new Sand(x + i, y + j));
							}
						}
					}
					break;

				case MenuState::EditingStone:
					// Adapter à la taille du pinceau
					for (int i = -brushRadius_; i <= brushRadius_; ++i) {
						for (int j = -brushRadius_; j <= brushRadius_; ++j) {
							if (map_->inBounds(x + i, y + j)) {
								map_->setBlocInCurrentFrame(x + i, y + j, new Stone(x + i, y + j));
							}
						}
					}
					break;

				case MenuState::EditingMushroom:
					// Adapter à la taille du pinceau
					for (int i = -brushRadius_; i <= brushRadius_; ++i) {
						for (int j = -brushRadius_; j <= brushRadius_; ++j) {
							if (map_->inBounds(x + i, y + j)) {
								map_->setBlocInCurrentFrame(x + i, y + j, new Mushroom(x + i, y + j, mushroomCD_));
							}
						}
					}
					break;

				case MenuState::EditingWater:
					// Adapter à la taille du pinceau
					for (int i = -brushRadius_; i <= brushRadius_; ++i) {
						for (int j = -brushRadius_; j <= brushRadius_; ++j) {
							if (map_->inBounds(x + i, y + j)) {
								map_->setBlocInCurrentFrame(x + i, y + j, new Water(x + i, y + j));
							}
						}
					}
					break;

				case MenuState::Deleting:
					// Adapter à la taille du pinceau
					for (int i = -brushRadius_; i <= brushRadius_; ++i) {
						for (int j = -brushRadius_; j <= brushRadius_; ++j) {
							if (map_->inBounds(x + i, y + j)) {
								map_->removeBloc(x + i, y + j);
							}
						}
					}
					break;

				default:
					break;
				}
			}
		}
	}

	// On relache le boutton de la souris
	if (event.type == sf::Event::MouseButtonReleased) {

		// Vérifier si un bouton a été cliqué
		for (auto& button : buttons_) {
			if (button.contains(event.mouseButton.x, event.mouseButton.y)) {
				ButtonAction action = button.getAction();

				// Appeler la méthode correspondante à l'action du bouton
				switch (action) {
					case ButtonAction::ToggleRunning:
						toggleRunning(game_);
						button.isSelected() ? button.setSelected(false) : button.setSelected(true);
						break;

					case ButtonAction::SummonRandomSand:
						summonRandomSand(map_);
						break;

					case ButtonAction::AddSandBloc:
						setEditingSand();
						break;

					case ButtonAction::AddStoneBloc:
						setEditingStone();
						break;

					case ButtonAction::AddMushroomBloc:
						setEditingMushroom();
						break;

					case ButtonAction::AddWaterBloc:
						setEditingWater();
						break;

					case ButtonAction::RemoveBloc:
						setRemovingBloc();
						break;

					case ButtonAction::IncreaseBrushRadius:
						// Augmenter le rayon du pinceau
						if (brushRadius_ < 9)
							brushRadius_++;
						for (auto& b : buttons_)
							if (b.getAction() == ButtonAction::ShowBrushSize)
								b.setText("Brush size: " + std::to_string(brushRadius_ * 2 + 1));

						break;
					case ButtonAction::DecreaseBrushRadius:
						// Diminuer le rayon du pinceau
						if (brushRadius_ > 0)
							brushRadius_--;
						for (auto& b : buttons_)
							if (b.getAction() == ButtonAction::ShowBrushSize)
								b.setText("Brush size: " + std::to_string(brushRadius_ * 2 + 1));
						break;

					//Changer le cooldown des champignons
					case ButtonAction::IncreaseMushroomCD:
						mushroomCD_++;
						for (auto& b : buttons_) {
							if (b.getAction() == ButtonAction::ShowMushroomCooldown)
								b.setText("Mushroom cooldown: " + std::to_string(mushroomCD_));
						}
						break;
					case ButtonAction::DecreaseMushroomCD:
						if (mushroomCD_ > 1)
							mushroomCD_--;
						for (auto& b : buttons_) {
							if (b.getAction() == ButtonAction::ShowMushroomCooldown)
								b.setText("Mushroom cooldown: " + std::to_string(mushroomCD_));
						}
						break;

					case ButtonAction::ClearMap:
						// Effacer la carte
						clearingMap();
						break;

					case ButtonAction::Quit:
						std::cout << "Game closed" << std::endl;
						game_->setRunning(false);
						window.close();
						return;
				}
			}
		}

		// On arrête de dessiner
		if (isDrawingNow_) {
			isDrawingNow_ = false;
		}
	}
}

// Fonction pour l'édition de sable
void Menu::setEditingSand() {
	Button* button = nullptr; // Récuperer le bouton associé à l'action
	for (auto& b : buttons_) {
		if (b.getAction() == ButtonAction::AddSandBloc) {
			button = &b;
			break;
		}
	}

	// Mettre à jour l'état du menu
	if (state_ != MenuState::EditingSand) {

		// On commence à dessiner
		state_ = MenuState::EditingSand;

		for (auto& b : buttons_) {
			if (b.getAction() != ButtonAction::ToggleRunning)
				b.setSelected(false);
		}
		button->setSelected(true);
	}
	else {
		// On arrête de dessiner
		state_ = MenuState::Idle;
		button->setSelected(false);
	}
}

void Menu::setEditingStone() {
	Button* button = nullptr; // Récuperer le bouton associé à l'action
	for (auto& b : buttons_) {
		if (b.getAction() == ButtonAction::AddStoneBloc) {
			button = &b;
			break;
		}
	}

	// Mettre à jour l'état du menu
	if (state_ != MenuState::EditingStone) {

		// On commence à dessiner
		state_ = MenuState::EditingStone;

		for (auto& b : buttons_) {
			if (b.getAction() != ButtonAction::ToggleRunning)
				b.setSelected(false);
		}
		button->setSelected(true);
	}
	else {
		// On arrête de dessiner
		state_ = MenuState::Idle;
		button->setSelected(false);
	}
}

void Menu::setEditingMushroom() {
	Button* button = nullptr; // Récuperer le bouton associé à l'action
	for (auto& b : buttons_) {
		if (b.getAction() == ButtonAction::AddMushroomBloc) {
			button = &b;
			break;
		}
	}

	// Mettre à jour l'état du menu
	if (state_ != MenuState::EditingMushroom) {

		// On commence à dessiner
		state_ = MenuState::EditingMushroom;

		for (auto& b : buttons_) {
			if (b.getAction() != ButtonAction::ToggleRunning)
				b.setSelected(false);
		}
		button->setSelected(true);
	}
	else {
		// On arrête de dessiner
		state_ = MenuState::Idle;
		button->setSelected(false);
	}
}

void Menu::setEditingWater() {
	Button* button = nullptr; // Récuperer le bouton associé à l'action
	for (auto& b : buttons_) {
		if (b.getAction() == ButtonAction::AddWaterBloc) {
			button = &b;
			break;
		}
	}

	// Mettre à jour l'état du menu
	if (state_ != MenuState::EditingWater) {

		// On commence à dessiner
		state_ = MenuState::EditingWater;

		for (auto& b : buttons_) {
			if (b.getAction() != ButtonAction::ToggleRunning)
				b.setSelected(false);
		}
		button->setSelected(true);
	}
	else {
		// On arrête de dessiner
		state_ = MenuState::Idle;
		button->setSelected(false);
	}
}

void Menu::setRemovingBloc() {
	Button* button = nullptr; // Récuperer le bouton associé à l'action
	for (auto& b : buttons_) {
		if (b.getAction() == ButtonAction::RemoveBloc) {
			button = &b;
			break;
		}
	}


	// Mettre à jour l'état du menu
	if (state_ != MenuState::Deleting) {

		// On commence à dessiner
		state_ = MenuState::Deleting;

		for (auto& b : buttons_) {
			if (b.getAction() != ButtonAction::ToggleRunning)
				b.setSelected(false);
		}
		button->setSelected(true);
	}
	else {
		// On arrête de dessiner
		state_ = MenuState::Idle;
		button->setSelected(false);
	}
}

void Menu::clearingMap() {
	map_->clear();
	isDrawingNow_ = false;
	state_ = MenuState::Idle;
	std::cout << "Map cleared" << std::endl;
	for (auto& b : buttons_) {
		if (b.getAction() != ButtonAction::ToggleRunning)
			b.setSelected(false);
	}
}