#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Button.h"

// États possibles du menu
enum class MenuState {
    Idle,
    EditingSand,
    EditingStone,
    EditingMushroom,
    Deleting
};

class Game;
class Map;

class Menu {
private:
    Game* game_;
    Map* map_;
    MenuState state_;

    int uiWidth_;

    sf::Font font_;
    std::vector<Button> buttons_;

    void createButtons(); // en interne

public:
    Menu(Game* game, Map* map, int uiWidth);

    void drawUI(sf::RenderWindow& window) const;

    void handleEvent(const sf::Event& event, sf::RenderWindow& window);

    void toggleRunning();
	void summonRandomSand();

    // Accès/modification de l’état
	MenuState getState() const {
		return state_;
	}
	void setState(MenuState newState) {
		state_ = newState;
	}
};