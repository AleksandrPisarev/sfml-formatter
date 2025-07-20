#include "Formatter.h"

Formatter::Formatter()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML window");
	font.loadFromFile("./fonts/arialbd.ttf");

	header.setFont(font);
	header.setString("values formatter");
	header.setCharacterSize(24);

	subtitle.setFont(font);
	subtitle.setCharacterSize(18);
	subtitle.setString("input your value");
	subtitle.setPosition(sf::Vector2f(0, 30));

	for (int i = 0; i < 12; i++) 
	{
		Button button(SIZE_BTN, font);
		if (i == 10) button.setText(".");
		else if (i == 11) button.setText("C");
		else button.setText(std::to_string(i));
		button.setPosition(sf::Vector2f(i * 60, 100));
		buttons.push_back(button);
	}

	for (int i = 0; i < 5; i++) 
	{
		Button field(SIZE_FIELD, "0", font);
		sf::Text textName;

		textName.setFont(font);
		textName.setCharacterSize(18);
		textName.setString(names[i]);
		textName.setFillColor(sf::Color::White);

		field.setPosition(sf::Vector2f(65, (150) + (i * 50)));
		fields.push_back(field);
		textName.setPosition(sf::Vector2f(0, (150) + (i * 50)));
		fieldsName.push_back(textName);
	}
}

void Formatter:: run()
{
	while (window.isOpen())
	{
		processEvent();
		update();
		render();
	}
}

void Formatter::processEvent()
{
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window.close();

        if (event.type == sf::Event::MouseButtonPressed)
        {
            if (event.mouseButton.button == sf::Mouse::Left) {
                battonsInt();
                fieldsInt();
            }
        }
        else {
            for (int i = 0; i < buttons.size(); i++) {
                buttons[i].off();
            }
        }
    }
}

void Formatter::update()
{
    auto activeNumber = std::stod(fields[activeField].getText().toAnsiString());
    for (int i = activeField - 1, index = 10; i >= 0; i--, index *= 10) {
        if (i == 3)
        {
            fields[i].setText(std::to_string(activeNumber * 1000));
            activeNumber *= 1000;
            index = 1;
        }
        else fields[i].setText(std::to_string(activeNumber * index));
    }
    for (int i = activeField + 1, index = 10; i < fields.size(); i++, index *= 10) {
        if (i == 4)
        {
            fields[i].setText(std::to_string((std::stod(fields[i - 1].getText().toAnsiString()) / 1000)));
        }
        else fields[i].setText(std::to_string(activeNumber / index));
    }

    for (int i = 0; i < fields.size(); i++) {
        fields[i].off();
    }

    fields[activeField].on();
}

void Formatter::render()
{
    window.clear();
    window.draw(header);
    window.draw(subtitle);

    for (auto name : fieldsName) {
        window.draw(name);
    }

    for (auto field : fields) {
        field.draw(window);
    }

    for (auto btn : buttons) {
        btn.draw(window);
    }

    window.display();
}

void Formatter::battonsInt()
{
    for (int i = 0; i < buttons.size(); i++) {
        auto mousePosition = event.mouseButton;
        if (mousePosition.x >= buttons[i].getPosition().x &&
            mousePosition.x <= buttons[i].getPosition().x + SIZE_BTN.x &&
            mousePosition.y >= buttons[i].getPosition().y &&
            mousePosition.y <= buttons[i].getPosition().y + SIZE_BTN.y) {
            buttons[i].on();
            titlesInt(i);
        }
    }
}

void Formatter::fieldsInt()
{
    for (int i = 0; i < fields.size(); i++) {
        auto mousePosition = event.mouseButton;
        if (mousePosition.x >= fields[i].getPosition().x &&
            mousePosition.x <= fields[i].getPosition().x + SIZE_FIELD.x &&
            mousePosition.y >= fields[i].getPosition().y &&
            mousePosition.y <= fields[i].getPosition().y + SIZE_FIELD.y) {
            activeField = i;
        }
    }
}

void Formatter::titlesInt(int i)
{
    auto currentString = fields[activeField].getText();
    if (i == 10) {
        fields[activeField].setText(currentString + ".");
    }
    else if (i == 11) {
        fields[activeField].setText("0");
    }
    else {
        auto num = buttons[i].getText().toAnsiString();

        auto currentNum = std::stod(fields[activeField].getText().toAnsiString());
        if (currentNum == 0) currentString = "";
        fields[activeField].setText(currentString + num);
    }
}