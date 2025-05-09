// Menu.h
// Auteur : Antoine Horion et Benjamin Escuder
// Description : La classe Menu gère l'interface utilisateur du jeu, y compris les boutons
// et les événements de la souris et du clavier


#ifndef MENU_H
#define MENU_H


#include <SFML/Graphics.hpp>
#include <vector>
#include "Button.h"

// États possibles du menu
enum class MenuState {
    Idle,
    EditingSand,
    EditingStone,
    EditingMushroom,
    EditingWater,
    Deleting
};

class Game;
class Map;

class Menu {
private:
    Game* game_;
    Map* map_;
	MenuState state_; // État du menu

	int uiWidth_; // Largeur de l'interface utilisateur en px

    sf::Font font_;
	std::vector<Button> buttons_; // Boutons de l'interface utilisateur

    // Méthodes internes
    void createButtons(); // Permet d'initialisé la liste de bouttons

    // Entrer-Sortir des modes d'édition respectifs à chaque matériau
    void setEditingSand();
    void setEditingStone();
    void setEditingMushroom();
    void setEditingWater();
    void setRemovingBloc();

    void clearingMap(); // Pour réinitialiser toute la carte et le menu

    void updateBrushPreview(sf::RenderWindow& window);

	bool isDrawingNow_;
	int brushRadius_;
    int mushroomCD_; // Contrôle le CoolDown des Mushroom placés

    sf::RectangleShape previewBox_;

public:
	// Constructeur
    Menu(Game* game, Map* map, int uiWidth);

	// Affiche l'interface utilisateur
    void drawUI(sf::RenderWindow& window) const;

	// Gère les événements de la souris ET du clavier
    void handleEvent(const sf::Event& event, sf::RenderWindow& window);
};

#endif // !MENU_H
