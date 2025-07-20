#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "windows.h"
#include "Button.h"
#include "Const.h"

class Formatter
{
	sf::RenderWindow window;
	sf::Font font;
	sf::Text header;
	sf::Text subtitle;
	std::vector<Button> buttons;
	std::vector<Button> fields;
	std::vector<sf::Text> fieldsName;
	std::string names[5] = { "mm", "sm", "dm", "m", "km" };
	sf::Event event;
	int activeField = 0;

public:
	Formatter();
	void run();
private:
	void processEvent();
	void update();
	void render();

	void battonsInt();
	void fieldsInt();
	void titlesInt(int);
};

