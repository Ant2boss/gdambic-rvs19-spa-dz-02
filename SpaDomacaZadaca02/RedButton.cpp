#include "RedButton.h"

void RedButton::MakeButton() {
	this->Button.setFillColor(sf::Color::Red);
	this->Button.setSize(this->ButtonSize);
	this->Button.setPosition(this->ButtonPos);
}

sf::Vector2f RedButton::GetMousePos() {
	sf::Vector2f temp;

	temp.x = sf::Mouse::getPosition().x - this->RenWin->getPosition().x - 5;
	temp.y = sf::Mouse::getPosition().y - this->RenWin->getPosition().y - 25;

	return temp;
}

RedButton::RedButton(sf::RenderWindow* RW, int xpos, int ypos, int xsize, int ysize) {
	this->RenWin = RW;
	this->SetButtonShape(xsize, ysize);
	this->SetButtonPos(xpos, ypos);

	this->MakeButton();
}

void RedButton::SetButtonPos(int x, int y) {
	this->ButtonPos.x = x;
	this->ButtonPos.y = y;

	this->MakeButton();
}

void RedButton::SetButtonShape(int x, int y) {
	this->ButtonSize.x = x;
	this->ButtonSize.y = y;

	this->MakeButton();
}

sf::Vector2f RedButton::getPosition() {
	return this->Button.getPosition();
}

bool RedButton::IsHovered() {
	sf::Vector2f Mouse = this->GetMousePos();
	if (Mouse.x < this->ButtonPos.x || Mouse.x > this->ButtonPos.x + this->ButtonSize.x) return false;
	if (Mouse.y < this->ButtonPos.y || Mouse.y > this->ButtonPos.y + this->ButtonSize.y) return false;

	return true;
}

bool RedButton::IsPressed() {
	return (this->IsHovered() && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left));
}

void RedButton::FlipButtonState() {
	this->ButtonState = !this->ButtonState;
}

bool RedButton::GetButtonState() {
	return this->ButtonState;
}

void RedButton::draw() {
	if (this->ButtonState) this->Button.setFillColor(sf::Color::Color(255, 0, 0));
	else this->Button.setFillColor(sf::Color::Color(128, 0, 0));

	this->RenWin->draw(this->Button);
}
