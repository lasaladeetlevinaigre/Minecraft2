#include "Water.h"
#include "Map.h"
#include <cstdlib>

Water::Water(int x, int y) : Bloc(x, y, WATER, sf::Color::Blue), wasGoingLeft_(false), wasGoingRight_(false) {
    // set random color
    /*
	int r = rand() % 256;
	int g = rand() % 256;
	int b = rand() % 256;
	setColor(sf::Color(r, g, b));
    */
}

void Water::update(Map* map) {
    int x = getX();
    int y = getY();

    // Gravit�
    if (map->inBounds(x, y + 1) && map->getBlockInNextGrid(x, y + 1) == nullptr) {
        map->setBlocInNextFrame(x, y + 1, this);
        setY(y + 1);
        return;
    }


	// V�rifier si on peut aller � gauche ou � droite HORIZONTALEMENT
	bool canLeft = map->inBounds(x - 1, y) && map->getBlockInNextGrid(x - 1, y) == nullptr && // la case est vide
		(map->getBlock(x - 1, y) && map->getBlock(x - 1, y)->getType() != WATER || !map->getBlock(x - 1, y)); // la case n'�tait pas de l'eau
	bool canRight = map->inBounds(x + 1, y) && map->getBlockInNextGrid(x + 1, y) == nullptr && // la case est vide
		(map->getBlock(x + 1, y) && map->getBlock(x + 1, y)->getType() != WATER || !map->getBlock(x + 1, y)); // la case n'�tait pas de l'eau



    // Regarder si on peut descendre en bas � gauche ou en bas � droite
    bool canBttmLeft = canLeft && map->inBounds(x - 1, y + 1) && map->getBlockInNextGrid(x - 1, y + 1) == nullptr;
    bool canBttmRight = canRight && map->inBounds(x + 1, y + 1) && map->getBlockInNextGrid(x + 1, y + 1) == nullptr;


	// Si on peut descendre en diagonale, on descend
    if (canBttmLeft && canBttmRight) {
        // priorit� � l'inertie
        if (wasGoingLeft_ && !wasGoingRight_) {
            map->setBlocInNextFrame(x - 1, y + 1, this);
            wasGoingLeft_ = true; wasGoingRight_ = false;
            setX(x - 1);
            setY(y + 1);
            return;
        }
        else if (wasGoingRight_ && !wasGoingLeft_) {
            map->setBlocInNextFrame(x + 1, y + 1, this);
            wasGoingLeft_ = false; wasGoingRight_ = true;
            setX(x + 1);
            setY(y + 1);
            return;

        }
        else {
            // on choisi al�atoirement entre gauche et droite
            if (rand() % 2 == 0) {
                map->setBlocInNextFrame(x - 1, y + 1, this);
                wasGoingLeft_ = true; wasGoingRight_ = false;
                setX(x - 1);
                setY(y + 1);
            }
            else {
                map->setBlocInNextFrame(x + 1, y + 1, this);
                wasGoingLeft_ = false; wasGoingRight_ = true;
                setX(x + 1);
                setY(y + 1);
            }
        }
        return;
    }
    else if (canBttmLeft) {
        map->setBlocInNextFrame(x - 1, y + 1, this);
        wasGoingLeft_ = true; wasGoingRight_ = false;
        setX(x - 1);
        setY(y + 1);
        return;
    }
    else if (canBttmRight) {
        map->setBlocInNextFrame(x + 1, y + 1, this);
        wasGoingLeft_ = false; wasGoingRight_ = true;
        setX(x + 1);
        setY(y + 1);
        return;
    }


	// si on peut aller � gauche ou � droite HORIZONTALMENT

	if (canLeft && canRight) {
        // priorit� � l'inertie
        if (wasGoingLeft_ && !wasGoingRight_) {
			map->setBlocInNextFrame(x - 1, y, this);
			wasGoingLeft_ = true; wasGoingRight_ = false;
			setX(x - 1);
			return;
		}
		else if (wasGoingRight_ && !wasGoingLeft_) {
			map->setBlocInNextFrame(x + 1, y, this);
			wasGoingLeft_ = false; wasGoingRight_ = true;
			setX(x + 1);
			return;

        }
        else {
            // on choisi al�atoirement entre gauche et droite
            if (rand() % 2 == 0) {
                map->setBlocInNextFrame(x - 1, y, this);
                wasGoingLeft_ = true; wasGoingRight_ = false;
                setX(x - 1);
            }
            else {
                map->setBlocInNextFrame(x + 1, y, this);
                wasGoingLeft_ = false; wasGoingRight_ = true;
                setX(x + 1);
            }
        }
		return;
	}
	else if (canLeft) {
		map->setBlocInNextFrame(x - 1, y, this);
		wasGoingLeft_ = true; wasGoingRight_ = false;
		setX(x - 1);
		return;
	}
	else if (canRight) {
		map->setBlocInNextFrame(x + 1, y, this);
		wasGoingLeft_ = false; wasGoingRight_ = true;
		setX(x + 1);
		return;
	}


	// V�rifier si on peut rester en place
	if (map->getBlockInNextGrid(x, y) == nullptr) {
		map->setBlocInNextFrame(x, y, this);
        wasGoingLeft_ = false; wasGoingRight_ = false;
		return;
	}

	// On ne peut descendre, aller sur les cot�s ni rester au meme endroit => on doit monter$
	// faire une boucle, on monte tant qu'on ne peut pas s'arreter, et on regarde � chaque fois � gauche et � droite
	// si on peut pas s'�chapper de la mont�e

    int newY = y - 1;
    while (map->inBounds(x, newY)) {

        // V�rifier si on peut s'arr�ter � ce niveau
        if (map->getBlockInNextGrid(x, newY) == nullptr) {
            // OK on peut s'arreter ici
            map->setBlocInNextFrame(x, newY, this);
            setY(newY);
            return;
        }

        // V�rifier si on peut s'�chapper horizontalement depuis ce niveau
        bool canLeft = map->inBounds(x - 1, newY) && map->getBlockInNextGrid(x - 1, newY) == nullptr;
        bool canRight = map->inBounds(x + 1, newY) && map->getBlockInNextGrid(x + 1, newY) == nullptr;

        if (canLeft || canRight) {
            if (canLeft && canRight) {
                if (rand() % 2 == 0) {
                    map->setBlocInNextFrame(x - 1, newY, this);
                    wasGoingLeft_ = true; wasGoingRight_ = false;
                    setX(x - 1);
                }
                else {
                    map->setBlocInNextFrame(x + 1, newY, this);
					wasGoingLeft_ = false; wasGoingRight_ = true;
                    setX(x + 1);
                }
            }
            else if (canLeft) {
                map->setBlocInNextFrame(x - 1, newY, this);
				wasGoingLeft_ = true; wasGoingRight_ = false;
                setX(x - 1);
            }
            else {
                map->setBlocInNextFrame(x + 1, newY, this);
				wasGoingLeft_ = false; wasGoingRight_ = true;
                setX(x + 1);
            }
            setY(newY);
            return;
        }

        // Continuer � monter
        newY--;
    }

    // si on est ici, on a atteint le haut de la map sans trouver de place
    std::cout << "WATER BLOCK TRAPPED AT TOP OF MAP: " << x << "," << y << std::endl;
    setColor(sf::Color::Red);
    map->setBlocInNextFrame(x, y, this);  // Le laisser sur place (il sera ptt �cras�)


    return;




}