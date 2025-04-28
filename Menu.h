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

    bool isDrawingNow_;
	int brushRadius_;

public:
    Menu(Game* game, Map* map, int uiWidth);

    void drawUI(sf::RenderWindow& window) const;

    void handleEvent(const sf::Event& event, sf::RenderWindow& window);
};