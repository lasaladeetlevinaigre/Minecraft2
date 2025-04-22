#include "Menu.h"
#include "Game.h"
#include "Map.h"
#include "Bloc.h"
#include <iostream>

Menu::Menu(Game* game, Map* map, int uiWidth) : game_(game), map_(map), uiWidth_(uiWidth), state_(MenuState::Idle)
{
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

	Button button_toggle_running = Button(ButtonAction::ToggleRunning,
		game_->getWidth() - uiWidth_ + 10, 10,
		uiWidth_-20, 30,
		"Pause",
		font_,
		18,
		sf::Color::White,
		sf::Color::Black,
		std::vector<sf::Color>{ sf::Color(150, 150, 150), sf::Color(80, 80, 80) });

	buttons_.push_back(button_toggle_running);

	buttons_.push_back(Button(ButtonAction::SummonRandomSand,
		game_->getWidth() - uiWidth_ + 10, 50,
		uiWidth_ - 20, 30,
		"Summon Rnd Sand",
		font_,
		18,
		sf::Color::White,
		sf::Color::Black,
		std::vector<sf::Color>{ sf::Color(80, 80, 80), sf::Color(150, 150, 150) }));

	

		


	

}

void Menu::drawUI(sf::RenderWindow& window) const {

	// Définir un rectangle background
	sf::RectangleShape rect_;
	rect_.setSize(sf::Vector2f(uiWidth_, game_->getHeight()));
	rect_.setPosition(game_->getWidth() - uiWidth_, 0);
	rect_.setFillColor(sf::Color(50, 50, 50, 200));
	window.draw(rect_);

	for (auto button : buttons_) {
		button.draw(window);
	}

}
void Menu::handleEvent(const sf::Event& event, sf::RenderWindow& window) {

	// FErmer le jeu
	if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) {
		std::cout << "Game closed" << std::endl;
		game_->setRunning(false);
		window.close();
	}

	// MEttre en pause / lecture
	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space) {
		toggleRunning();
		for (auto& button : buttons_) {
			if (button.getAction() == ButtonAction::ToggleRunning)
				button.isSelected() ? button.setSelected(false) : button.setSelected(true);
		}
	}

	// Faire apparaitre un bloc de sable
	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::S) {
		summonRandomSand();
	}


	if (event.type == sf::Event::MouseButtonPressed) {
		// Cout coord
		std::cout << "Mouse button pressed at (" << event.mouseButton.x << ", " << event.mouseButton.y << ")" << std::endl;

		for (auto& button : buttons_) {
			if (button.contains(event.mouseButton.x, event.mouseButton.y)) {
				ButtonAction action = button.getAction();

				// Appeler la méthode correspondante
				switch (action) {
					case ButtonAction::ToggleRunning:
						toggleRunning();
						button.isSelected() ? button.setSelected(false) : button.setSelected(true);
						break;
					case ButtonAction::SummonRandomSand:
						summonRandomSand();
						break;
				}
			}
		}
	}
}
void Menu::toggleRunning() {
	if (game_->isRunning()) {
		std::cout << "Game paused" << std::endl;
		game_->setRunning(false);
	}
	else {
		std::cout << "Game resumed" << std::endl;
		game_->setRunning(true);
	}
}
void Menu::summonRandomSand() {
	int x = rand() % map_->getWidth();
	int y = rand() % map_->getHeight();
	if (map_->inBounds(x, y)) {
		map_->setBlocInCurrentFrame(x, y, new Bloc(x, y, sf::Color::Green));
		std::cout << "Summoned sand block at (" << x << ", " << y << ")" << std::endl;
	}
}