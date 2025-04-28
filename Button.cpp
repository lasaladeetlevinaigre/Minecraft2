#include "Button.h"
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;


Button::Button(ButtonAction action,
	int x, int y,
	int width, int height,
	const std::string& label,
	const sf::Font& font,
	int fontSize,
	sf::Color textColor,
	sf::Color outlineColor,
	std::vector<sf::Color> bgColor)
	: callbackAction_(action),
	width_(width),
	height_(height),
	x_(x),
	y_(y),
	text_(label),
	font_(font),
	fontSize_(fontSize),
	textColor_(textColor),
	outlineColor_(outlineColor),
	bgColor_(bgColor),
	selected_(false)
{
	// Configuration du rectangle
	rect_.setSize(sf::Vector2f(width_, height_));
	rect_.setPosition(x_, y_);
	rect_.setOutlineThickness(2);
	rect_.setOutlineColor(outlineColor_);
	rect_.setFillColor(bgColor_[0]);

	// Configuration du texte
	sfText_.setFont(font);
	sfText_.setString(label);
	sfText_.setCharacterSize(fontSize);
	sfText_.setFillColor(textColor_);

	// Centrer du texte
	sf::FloatRect textRect = sfText_.getLocalBounds();
	sfText_.setOrigin(textRect.left + textRect.width / 2.0f,
		textRect.top + textRect.height / 2.0f);
	sfText_.setPosition(x_ + width_ / 2.0f, y_ + height_ / 2.0f);

}
void Button::setText(const std::string& text) {
	text_ = text;
	sfText_.setString(text);
	sf::FloatRect textRect = sfText_.getLocalBounds();
	sfText_.setOrigin(textRect.left + textRect.width / 2.0f,
		textRect.top + textRect.height / 2.0f);
	sfText_.setPosition(x_ + width_ / 2.0f, y_ + height_ / 2.0f);
}

bool Button::contains(int x, int y) const {
	return (x >= x_ && x <= x_ + width_ && y >= y_ && y <= y_ + height_);
}

void Button::draw(sf::RenderWindow& window) {
	if (selected_)
		rect_.setFillColor(bgColor_[1]);
	else
		rect_.setFillColor(bgColor_[0]);

	window.draw(rect_);
	window.draw(sfText_);
}

