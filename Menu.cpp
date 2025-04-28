#include "Menu.h"
#include "Game.h"
#include "Map.h"
#include "Bloc.h"
#include <iostream>



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


Menu::Menu(Game* game, Map* map, int uiWidth) : game_(game), map_(map), uiWidth_(uiWidth), state_(MenuState::Idle), isDrawingNow_(false), brushRadius_(0) {
	// Initialiser l'état du menu
	state_ = MenuState::Idle;
	isDrawingNow_ = false;
	brushRadius_ = 1;

	// Initialiser la largeur de l'interface utilisateur
	uiWidth_ = uiWidth;

	// Initialiser la police
	if (!font_.loadFromFile("NunitoSans.ttf")) {
		std::cerr << "Error loading font" << std::endl;
	}
	createButtons();
}

void Menu::createButtons() {
	// Créer les boutons avec leurs actions
	/*
	// Rappel déclarataion de Button :
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

	buttons_.push_back(Button(ButtonAction::None,
		game_->getWidth() - uiWidth_ + 10, y,
		uiWidth_ - 20, 30,
		"Brush size: 2",
		font_,
		18,
		sf::Color::White,
		sf::Color(50, 50, 50),
		std::vector<sf::Color>{ sf::Color(50, 50, 50), sf::Color(50, 50, 50) }));
	y += 40;


	// Modifier la taille du pinceau
	buttons_.push_back(Button(ButtonAction::IncreaseBrushRadius,
		game_->getWidth() - uiWidth_ + 10, y,
		uiWidth_/2 - 15, 30,
		"++ pinceau",
		font_,
		18,
		sf::Color::White,
		sf::Color::Black,
		std::vector<sf::Color>{ sf::Color(80, 80, 80), sf::Color(150, 150, 150) }));

	buttons_.push_back(Button(ButtonAction::DecreaseBrushRadius,
		game_->getWidth() - uiWidth_ + uiWidth_/2 + 5, y,
		uiWidth_/2 - 15, 30,
		"-- pinceau",
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

	buttons_.push_back(Button(ButtonAction::RemoveBloc,
		game_->getWidth() - uiWidth_ + 10, y,
		uiWidth_ - 20, 30,
		"Erase Block",
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



	

		


	

}

void Menu::drawUI(sf::RenderWindow& window) const {

	// Définir un rectangle background
	sf::RectangleShape rect_;
	rect_.setSize(sf::Vector2f(uiWidth_, game_->getHeight()));
	rect_.setPosition(game_->getWidth() - uiWidth_, 0);
	rect_.setFillColor(sf::Color(50, 50, 50, 200));
	window.draw(rect_);

	// Dessiner chaque bouton
	for (auto button : buttons_) {
		button.draw(window);
	}
}


void summonRandomSand(Map* map) {
	int x = rand() % map->getWidth();
	int y = rand() % map->getHeight();
	if (map->inBounds(x, y)) {
		map->setBlocInCurrentFrame(x, y, new Bloc(x, y, sf::Color::Yellow));
		//std::cout << "Summoned sand block at (" << x << ", " << y << ")" << std::endl;
	}
}

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

	// Faire apparaitre un bloc de sable
	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::S) {
		summonRandomSand(map_);
	}

	// 
	if (event.type == sf::Event::MouseButtonPressed) {
		// Vérifier si le curseur est sur la carte
		if (event.mouseButton.x < game_->getWidth() - uiWidth_ && (
			state_ == MenuState::EditingSand ||
			state_ == MenuState::EditingStone ||
			state_ == MenuState::EditingMushroom ||
			state_ == MenuState::Deleting)) {
			isDrawingNow_ = true;
	
		}
	}
	
	// Déplacement de la souris
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
								map_->setBlocInCurrentFrame(x + i, y + j, new Bloc(x + i, y + j, sf::Color::Yellow));
							}
						}
					}
					break;

				case MenuState::EditingStone:
					// Adapter à la taille du pinceau
					for (int i = -brushRadius_; i <= brushRadius_; ++i) {
						for (int j = -brushRadius_; j <= brushRadius_; ++j) {
							if (map_->inBounds(x + i, y + j)) {
								map_->setBlocInCurrentFrame(x + i, y + j, new Bloc(x + i, y + j, sf::Color(150, 150, 150)));
							}
						}
					}
					break;

				case MenuState::EditingMushroom:
					// Adapter à la taille du pinceau
					for (int i = -brushRadius_; i <= brushRadius_; ++i) {
						for (int j = -brushRadius_; j <= brushRadius_; ++j) {
							if (map_->inBounds(x + i, y + j)) {
								map_->setBlocInCurrentFrame(x + i, y + j, new Bloc(x + i, y + j, sf::Color(255, 0, 255)));
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
		//std::cout << "Mouse button released at (" << event.mouseButton.x << ", " << event.mouseButton.y << ")" << std::endl;

		// Vérifier si un bouton a été cliqué
		for (auto& button : buttons_) {
			if (button.contains(event.mouseButton.x, event.mouseButton.y)) {
				ButtonAction action = button.getAction();

				// Appeler la méthode correspondante
				switch (action) {
					case ButtonAction::ToggleRunning:
						toggleRunning(game_);
						button.isSelected() ? button.setSelected(false) : button.setSelected(true);
						break;

					case ButtonAction::SummonRandomSand:
						summonRandomSand(map_);
						break;

					case ButtonAction::AddSandBloc:
						// Mettre à jour l'état du menu
						if (state_ != MenuState::EditingSand) {

							// On commence à dessiner
							state_ = MenuState::EditingSand;

							button.setSelected(true);
							for (auto& b : buttons_) {
								if (b.getAction() == ButtonAction::AddMushroomBloc ||
									b.getAction() == ButtonAction::AddStoneBloc ||
									b.getAction() == ButtonAction::RemoveBloc)
									b.setSelected(false);
							}
						}
						else {
							// On arrête de dessiner
							state_ = MenuState::Idle;
							button.setSelected(false);
						}
						break;

					case ButtonAction::AddStoneBloc:
						// Mettre à jour l'état du menu
						if (state_ != MenuState::EditingStone) {

							// On commence à dessiner
							state_ = MenuState::EditingStone;

							button.setSelected(true);
							for (auto& b : buttons_) {
								if (b.getAction() == ButtonAction::AddMushroomBloc ||
									b.getAction() == ButtonAction::AddSandBloc ||
									b.getAction() == ButtonAction::RemoveBloc)
									b.setSelected(false);
							}
						}
						else {
							// On arrête de dessiner
							state_ = MenuState::Idle;
							button.setSelected(false);
						}
						break;

					case ButtonAction::AddMushroomBloc:
						// Mettre à jour l'état du menu
						if (state_ != MenuState::EditingMushroom) {

							// On commence à dessiner
							state_ = MenuState::EditingMushroom;

							button.setSelected(true);
							for (auto& b : buttons_) {
								if (b.getAction() == ButtonAction::AddStoneBloc ||
									b.getAction() == ButtonAction::AddSandBloc ||
									b.getAction() == ButtonAction::RemoveBloc)
									b.setSelected(false);
							}
						}
						else {
							// On arrête de dessiner
							state_ = MenuState::Idle;
							button.setSelected(false);
						}
						break;
					case ButtonAction::RemoveBloc:
						// Mettre à jour l'état du menu
						if (state_ != MenuState::Deleting) {

							// On commence à dessiner
							state_ = MenuState::Deleting;

							button.setSelected(true);
							for (auto& b : buttons_) {
								if (b.getAction() == ButtonAction::AddMushroomBloc ||
									b.getAction() == ButtonAction::AddStoneBloc ||
									b.getAction() == ButtonAction::AddSandBloc)
									b.setSelected(false);
							}
						}
						else {
							// On arrête de dessiner
							state_ = MenuState::Idle;
							button.setSelected(false);
						}
						break;
					case ButtonAction::IncreaseBrushRadius:
						// Augmenter le rayon du pinceau
						if (brushRadius_ < 9)
							brushRadius_++;
						for(auto& b: buttons_)
							if (b.getAction() == ButtonAction::None)
								b.setText("Brush size: " + std::to_string(brushRadius_*2+1));

						break;
					case ButtonAction::DecreaseBrushRadius:
						// Diminuer le rayon du pinceau
						if (brushRadius_ > 0)
							brushRadius_--;
						for (auto& b : buttons_)
							if (b.getAction() == ButtonAction::None)
								b.setText("Brush size: " + std::to_string(brushRadius_*2+1));
						break;
					case ButtonAction::ClearMap:
						// Effacer la carte
						map_->clear();
						std::cout << "Map cleared" << std::endl;
						for (auto& b : buttons_) {
							if (b.getAction() == ButtonAction::AddMushroomBloc ||
								b.getAction() == ButtonAction::AddStoneBloc ||
								b.getAction() == ButtonAction::AddSandBloc ||
								b.getAction() == ButtonAction::RemoveBloc)
								b.setSelected(false);
						}
						break;
				}
			}
		}

		if (isDrawingNow_) {
			// On arrête de dessiner
			isDrawingNow_ = false;
		}
	}
}