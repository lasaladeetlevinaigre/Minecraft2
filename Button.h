#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

// Différentes actions des boutons
enum class ButtonAction {
    None,
    ToggleRunning,
    SummonRandomSand,
    AddSandBloc,
    AddStoneBloc,
    AddMushroomBloc,
    RemoveBloc,
	IncreaseBrushRadius,
	DecreaseBrushRadius,
	ClearMap,
	SaveMap,
	LoadMap
};

class Button {
private:
    ButtonAction callbackAction_;
    int width_;
    int height_;
    int x_;
    int y_;
    std::string text_;
    sf::Font font_;
    int fontSize_;
    sf::Color textColor_;
    sf::Color outlineColor_;
    std::vector<sf::Color> bgColor_;
    bool selected_;

    sf::RectangleShape rect_;
    sf::Text sfText_;

public:
    // Constructeur
    Button(ButtonAction action,
        int x, int y,
        int width, int height,
        const std::string& label,
        const sf::Font& font,
        int fontSize,
        sf::Color textColor,
        sf::Color outlineColor,
        std::vector<sf::Color> bgColor);

    // Dessine le bouton sur la cible
    void draw(sf::RenderWindow& window);

    // Retourne true si le curseur est dans le bouton
    bool contains(int x, int y) const;

	ButtonAction getAction() const {
		return callbackAction_;
	}
	bool isSelected() const {
		return selected_;
	}
	void setSelected(bool sel) {
		selected_ = sel;
		if (selected_) {
			rect_.setFillColor(bgColor_[1]);
		}
		else {
			rect_.setFillColor(bgColor_[0]);
		}
	}
    void setText(const std::string& text);
};
