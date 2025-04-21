#ifndef BLOC_H
#define BLOC_H

#include <SFML/Graphics.hpp>

class Map;

class Bloc {
private:
    int x_, y_;
    sf::Color color_;

public:
    Bloc(int x, int y, const sf::Color& color)
        : x_(x), y_(y), color_(color) {}

    virtual ~Bloc() = default;  // Destructeur virtuel

    virtual void update(Map& map) = 0;
    void draw(sf::RenderWindow& window, float cellSize) const;

	int getX() const { return x_; }
	int getY() const { return y_; }
};

#endif // !BLOC_H