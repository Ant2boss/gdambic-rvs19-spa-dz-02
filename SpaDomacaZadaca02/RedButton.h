#pragma once
#include<SFML/Graphics.hpp>
class RedButton {
	sf::RenderWindow* RenWin;
	sf::RectangleShape Button;

	sf::Vector2f ButtonSize;
	sf::Vector2f ButtonPos;
	bool ButtonState;

	void MakeButton();
	sf::Vector2f GetMousePos();

public:
	RedButton(sf::RenderWindow*, int xpos, int ypos, int xsize, int ysize);

	void SetButtonPos(int x, int y);
	void SetButtonShape(int x, int y);

	sf::Vector2f getPosition();

	bool IsHovered();
	bool IsPressed();

	void FlipButtonState();
	bool GetButtonState();

	void draw();
};

