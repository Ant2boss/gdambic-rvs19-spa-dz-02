#pragma once
#include<SFML/Graphics.hpp>

int GenRand(int min, int max);

class GridOrganizama {
	sf::RenderWindow* RenWin;

	sf::RectangleShape Celija;

	sf::Vector2i OznacenaCelija;

	bool* MatricaOrganizama = nullptr;
	int DimenzijaGrida;
	int DimenzijaCelije;

	void GetMem();
	void RelMem();

	void NapraviCeliju();

	void GetMisemOdabranuCeliju(sf::Vector2f PocetakCrtanja);
public:
	GridOrganizama(sf::RenderWindow* RW, int DimenzijeGrida, int DimenzijeCelije, bool Prazno);
	~GridOrganizama();

	sf::Vector2f GetPozicijaMisa();
	sf::Vector2i GetLastOznacenaCelija();
	int GetDimenzijaCelije();
	int GetBrojSusjeda(int x, int y);

	void SetDimezijaCelije(int newDim);

	bool& at(int x, int y);

	void ProvediPravilaGeneracije();

	void draw(sf::Vector2f PocetakCrtanja);
};

