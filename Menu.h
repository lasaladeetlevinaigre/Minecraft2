// Menu.h
// Auteur : Antoine Horion et Benjamin Escuder
// Description : La classe Menu g�re l'interface utilisateur du jeu, y compris les boutons
// et les �v�nements de la souris et du clavier


#ifndef MENU_H
#define MENU_H


#include <SFML/Graphics.hpp>
#include <vector>
#include "Button.h"

// �tats possibles du menu
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
	MenuState state_; // �tat du menu

	int uiWidth_; // Largeur de l'interface utilisateur en px

    sf::Font font_;
	std::vector<Button> buttons_; // Boutons de l'interface utilisateur

    // M�thodes internes
    void createButtons(); // Permet d'initialis� la liste de bouttons

    // Entrer-Sortir des modes d'�dition respectifs � chaque mat�riau
    void setEditingSand();
    void setEditingStone();
    void setEditingMushroom();
    void setEditingWater();
    void setRemovingBloc();

    void clearingMap(); // Pour r�initialiser toute la carte et le menu

    void updateBrushPreview(sf::RenderWindow& window);

	bool isDrawingNow_;
	int brushRadius_;
    int mushroomCD_; // Contr�le le CoolDown des Mushroom plac�s

    sf::RectangleShape previewBox_;

public:
	// Constructeur
    Menu(Game* game, Map* map, int uiWidth);

	// Affiche l'interface utilisateur
    void drawUI(sf::RenderWindow& window) const;

	// G�re les �v�nements de la souris ET du clavier
    void handleEvent(const sf::Event& event, sf::RenderWindow& window);
};

#endif // !MENU_H
