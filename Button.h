// Button.h
// Auteur : Benjamin Escuder
// Description : Classe pour créer des boutons pour le menu
// Chaque bouton a une action associée, une position, une taille, un texte,
// des couleurs et d'autres paramètres d'affichage


#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>


// Enumération des actions possibles pour les boutons
enum class ButtonAction {
    None,
    ToggleRunning,
    SummonRandomSand,
    AddSandBloc,
    AddStoneBloc,
    AddMushroomBloc,
    AddWaterBloc,
    RemoveBloc,
    ShowBrushSize,
	IncreaseBrushRadius,
	DecreaseBrushRadius,
    ShowMushroomCooldown,
    IncreaseMushroomCD,
    DecreaseMushroomCD,
	ClearMap,
	SaveMap,
	LoadMap,
	Quit
};

class Button {
private:
	ButtonAction callbackAction_; // Action associée au bouton
    int width_;
    int height_;
    int x_;
    int y_;
    std::string text_;
    sf::Font font_;
    int fontSize_;
	sf::Color textColor_; // Couleur du texte
	sf::Color outlineColor_; // Couleur de contour
	std::vector<sf::Color> bgColor_; // Couleurs de fond lors que le bouton est sélectionné ou non
    bool selected_;

	sf::RectangleShape rect_; // Rectangle représentant le bouton
	sf::Text sfText_; // Texte affiché sur le bouton

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

    // Dessine le bouton sur la fenêtre
    void draw(sf::RenderWindow& window);

    // Retourne vrai si le point en (x, y) est dans le bouton
    bool contains(int x, int y) const;


	// Change l'état de sélection du bouton
    void setSelected(bool sel) {
        selected_ = sel;
		rect_.setFillColor(bgColor_[selected_ ? 1 : 0]); // Change la couleur de fond
    }

    void setText(const std::string& text);


    // Accesseurs
	ButtonAction getAction() const {
		return callbackAction_;
	}
	bool isSelected() const {
		return selected_;
	}
};

#endif // BUTTON_H