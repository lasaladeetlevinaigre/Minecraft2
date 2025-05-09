// Fish.h
// Auteur : Benjamin Escuder
// Défini une entité poisson

#ifndef FISH_H
#define FISH_H

#include <string>
#include <SFML/Graphics.hpp>

class Map;

class Fish {
    int x_, y_;
    std::string name_;
    sf::Color initialColor_;
    sf::Color color_;

    int direction_; // -1: gauche, 1: droite
    int changeDirCooldown_; // temps avant de pouvoir changer de direction
    int swimCooldown_; // temps avant de se deplacer

    int flashCooldown_; // permet de gerer le clignotement lorsque le poisson suffoque
    int timeLeftToLive_;

    unsigned int age_;
    int reproductionCooldown_;
    int staringMateSince_; // avant de se reproduire, on reste statique à coté du partenaire qqs instants
    bool isAlive_;

public:
	Fish(int x, int y, std::string name, sf::Color color);
	void update(Map* map);
	void draw(sf::RenderWindow& window, int blockSize) const;
    bool isAlive() const { return isAlive_; }

    unsigned int getAge() const { return age_; }
    int getX() const { return x_; }
    int getY() const { return y_; }

    sf::Color getInitialColor() const { return initialColor_; }

    void setColor(sf::Color color) { color_ = color; }

    int staringMateSince() const { return staringMateSince_; }
    void setStaringTime(int st) { staringMateSince_ = st; }

    int getReproductionCooldown() const { return reproductionCooldown_; }
    void setReproductionCooldown(int cd) { reproductionCooldown_ = cd; }

};


#endif // !FISH_H
