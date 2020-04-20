#include <SFML/Graphics.hpp>
#include <iostream>
#include "GridOrganizama.h"
#include "RedButton.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(1280, 720), "Hello, SFML world!");
	window.setFramerateLimit(60);

	sf::Vector2f t;

	GridOrganizama GRID(&window, 100, 50, false);

	sf::Vector2f GridOrigin;
	GridOrigin.x = 0;
	GridOrigin.y = 0;

	bool Drzen = false;
	sf::Vector2f PozicijaMisaUProslomFrame;

	sf::Clock Vrijeme;

	sf::RectangleShape GUI;
	t.y = window.getSize().y;
	t.x = 128;
	GUI.setSize(t);
	GUI.setOrigin(t.x, 0);
	GUI.setPosition(window.getSize().x, 0);

	sf::Texture textGUI;
	if (!textGUI.loadFromFile("GUI_texture.png")) {
		std::cout << "Greska prilikom otvranaja slike!" << std::endl;
		return -1;
	}

	GUI.setTexture(&textGUI);

	RedButton AButton(&window, window.getSize().x - 128, window.getSize().y - 150, 128, 128);
	bool GumbJeStisnut = false;

	sf::RectangleShape ProgressBar;
	ProgressBar.setFillColor(sf::Color::Blue);
	ProgressBar.setPosition(AButton.getPosition().x, AButton.getPosition().y - 50);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			//Zoom / od-zoom sa kotacicem misa
			if (event.type == sf::Event::MouseWheelMoved) {
				if (event.mouseWheel.delta < 0) GRID.SetDimezijaCelije(GRID.GetDimenzijaCelije() - 1);
				if (event.mouseWheel.delta > 0) GRID.SetDimezijaCelije(GRID.GetDimenzijaCelije() + 1);
			}
		}

		//User interface
		if (AButton.IsPressed() && GumbJeStisnut == false) {
			AButton.FlipButtonState();
			GumbJeStisnut = true;
		}
		else if (!AButton.IsPressed() && GumbJeStisnut == true) GumbJeStisnut = false;

		//Dok se drzi lijevi klik, mijenjaj poziciju Grid-a
		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && Drzen == false) {
			PozicijaMisaUProslomFrame = GRID.GetPozicijaMisa();
			Drzen = true;
		}
		if (Drzen) {
			//Ukoliko se mis pomaknuo, pomakni i grid za tu promjenu
			GridOrigin.x += GRID.GetPozicijaMisa().x - PozicijaMisaUProslomFrame.x;
			GridOrigin.y += GRID.GetPozicijaMisa().y - PozicijaMisaUProslomFrame.y;
			//Potrebno je azurirati poziciju misa
			PozicijaMisaUProslomFrame = GRID.GetPozicijaMisa();
		}
		if (!sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && Drzen == true) Drzen = false;

		//Ukoliko se drzi desni klik misa, stavljaj organizme
		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right)) {
			sf::Vector2i XY = GRID.GetLastOznacenaCelija();
			if (XY.x != -1 && XY.y != -1) GRID.at(XY.x, XY.y) = true;
		}

		if (Vrijeme.getElapsedTime().asSeconds() >= 2) {
			Vrijeme.restart();
			GRID.ProvediPravilaGeneracije();
		}

		//Popunjavanje progress bara
		float Duljina = Vrijeme.getElapsedTime().asMilliseconds() * (128.0 / 2000.0);
		t.x = Duljina;
		t.y = 25;
		ProgressBar.setSize(t);

		//Zaustavljanje generacija
		if (AButton.GetButtonState()) {
			Vrijeme.restart();
		}

		window.clear();

		GRID.draw(GridOrigin);
		window.draw(GUI);
		window.draw(ProgressBar);
		AButton.draw();

		window.display();
	}

	return 0;
}