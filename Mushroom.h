#pragma once
#include <SFML/Graphics.hpp>
#include "bloc.h"

class Mushroom : public Bloc {

	int spreadCooldown;

public:
	void update();
};