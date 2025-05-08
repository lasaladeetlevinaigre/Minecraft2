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
    int changeDirCooldown_;
    int swimCooldown_;
    int timeLeftToLive_;
    int flashCooldown_; // permet de gerer le clignotement lorsque le poisson suffoque
    bool isAlive_;

public:
	Fish(int x, int y, std::string name, sf::Color color);
	void update(Map* map);
	void draw(sf::RenderWindow& window, int blockSize) const;

    bool isAlive() const { return isAlive_; }

};


#endif // !FISH_H
