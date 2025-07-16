#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "windows.h"
#include "Button.h"
using namespace std;

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML window");
    sf::Font font;
    sf::Text header;
    sf::Text subtitle;
   
    const sf::Vector2f SIZE_BTN(50.f, 30.f);
    
    std::vector<Button> buttons;
    for (int i = 0; i < 12; i++) {
        Button button(SIZE_BTN, font);
        if (i == 10) button.setText(".");
        else if (i == 11) button.setText("C");
        else button.setText(std::to_string(i));
        button.setPosition(sf::Vector2f(i * 60, 100));
        buttons.push_back(button);
    }

    vector<Button> fields;
    std::vector<sf::Text> fieldsName;
    int activeField = 0;
    string names[5] = { "mm", "sm", "dm", "m", "km" };



    const sf::Vector2f SIZE_FIELD(300.f, 30.f);

    for (int i = 0; i < 5; i++) {
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

    font.loadFromFile("./fonts/arialbd.ttf");

    subtitle.setFont(font);
    subtitle.setCharacterSize(18);
    subtitle.setString("input your value");
    subtitle.setPosition(sf::Vector2f(0, 30));
    header.setFont(font);
    header.setString("values formatter");
    header.setCharacterSize(24);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    auto mousePosition = event.mouseButton;
                    for (int i = 0; i < buttons.size(); i++){
                        if (mousePosition.x >= buttons[i].getPosition().x &&
                            mousePosition.x <= buttons[i].getPosition().x + SIZE_BTN.x &&
                            mousePosition.y >= buttons[i].getPosition().y &&
                            mousePosition.y <= buttons[i].getPosition().y + SIZE_BTN.y) {
                            buttons[i].on();
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
                    }
                    for (int i = 0; i < fields.size(); i++) {
                        if (mousePosition.x >= fields[i].getPosition().x &&
                            mousePosition.x <= fields[i].getPosition().x + SIZE_FIELD.x &&
                            mousePosition.y >= fields[i].getPosition().y &&
                            mousePosition.y <= fields[i].getPosition().y + SIZE_FIELD.y) {
                            activeField = i;
                        }
                    }
                }
            }
            else {
                for (int i = 0; i < buttons.size(); i++) {
                    buttons[i].off();
                }
            }
        }
        auto activeNumber = std::stod(fields[activeField].getText().toAnsiString());
        for (int i = activeField-1, index=10; i >= 0; i--, index*=10) {
            fields[i].setText(std::to_string(activeNumber * index));
        }
        for (int i = activeField + 1, index = 10; i < fields.size(); i++, index *= 10) {
            fields[i].setText(std::to_string(activeNumber / index));
        }

        for (int i = 0; i < fields.size(); i++) {
            fields[i].off();
        }

        fields[activeField].on();

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

    return EXIT_SUCCESS;
}