#include "GridOrganizama.h"
#include <cmath>
//Debug
#include<iostream>

void GridOrganizama::GetMem() {
	this->RelMem();
	this->MatricaOrganizama = new bool[this->DimenzijaGrida * this->DimenzijaGrida];

	for (int i = 0; i < this->DimenzijaGrida * this->DimenzijaGrida; i++) this->MatricaOrganizama[i] = false;

}

void GridOrganizama::RelMem() {
	if (this->MatricaOrganizama != nullptr) delete[] this->MatricaOrganizama;
}

void GridOrganizama::NapraviCeliju() {
	sf::Vector2f Dimenzija;
	Dimenzija.x = this->DimenzijaCelije;
	Dimenzija.y = this->DimenzijaCelije;
	this->Celija.setSize(Dimenzija);
	this->Celija.setOrigin(Dimenzija.x / 2, Dimenzija.y / 2);
	this->Celija.setFillColor(sf::Color::Black);
	this->Celija.setOutlineThickness(2);
}

GridOrganizama::GridOrganizama(sf::RenderWindow* RW, int DimenzijeGrida, int DimenzijeCelije, bool Prazno) {
	this->RenWin = RW;
	this->DimenzijaGrida = DimenzijeGrida;
	this->DimenzijaCelije = DimenzijeCelije;
	this->OznacenaCelija.x = -1;
	this->OznacenaCelija.y = -1;

	this->GetMem();
	this->NapraviCeliju();

	if (!Prazno) {
		for (int i = 0; i < this->DimenzijaGrida * this->DimenzijaGrida; i++) {
			if (GenRand(1, 100) <= 25) this->MatricaOrganizama[i] = true;
		}
	}
}

GridOrganizama::~GridOrganizama() {
	this->RelMem();
}

sf::Vector2f GridOrganizama::GetPozicijaMisa() {
	sf::Vector2f temp;

	temp.x = sf::Mouse::getPosition().x - this->RenWin->getPosition().x - 5;
	temp.y = sf::Mouse::getPosition().y - this->RenWin->getPosition().y - 25;

	return temp;
}

sf::Vector2i GridOrganizama::GetLastOznacenaCelija() {
	return this->OznacenaCelija;
}

int GridOrganizama::GetDimenzijaCelije() {
	return this->DimenzijaCelije;
}

int GridOrganizama::GetBrojSusjeda(int pomx, int pomy) {
	int brSusjeda = 0;
	for (int y = pomy - 1; y <= pomy + 1; y++) {
		for (int x = pomx - 1; x <= pomx + 1; x++) {
			if (y < 0 || y >= this->DimenzijaGrida) continue;
			if (x < 0 || x >= this->DimenzijaGrida) continue;

			if (y == pomy && x == pomx) continue;

			if (this->at(x, y)) brSusjeda++;
		}
	}
	return brSusjeda;
}

void GridOrganizama::SetDimezijaCelije(int newDim) {
	this->DimenzijaCelije = newDim;
	this->NapraviCeliju();
}

void GridOrganizama::GetMisemOdabranuCeliju(sf::Vector2f PocetakCrtanja) {
	sf::Vector2f PozMisa = this->GetPozicijaMisa();

	sf::Vector2f UdaljenostOdPocetka;
	UdaljenostOdPocetka.x = PozMisa.x - PocetakCrtanja.x;
	UdaljenostOdPocetka.y = PozMisa.y - PocetakCrtanja.y;

	this->OznacenaCelija.x = std::round(UdaljenostOdPocetka.x / this->DimenzijaCelije);
	this->OznacenaCelija.y = std::round(UdaljenostOdPocetka.y / this->DimenzijaCelije);

	//Provjera ako je "odabrana kocka unutar grid-a"
	if (this->OznacenaCelija.x < 0 || this->OznacenaCelija.y < 0 || this->OznacenaCelija.x >= this->DimenzijaGrida || this->OznacenaCelija.y >= this->DimenzijaGrida) {
		this->OznacenaCelija.x = -1;
		this->OznacenaCelija.y = -1;
	}

}

bool& GridOrganizama::at(int x, int y) {

	int index = y * this->DimenzijaGrida + x;
	if (index < 0 || index >= this->DimenzijaGrida * this->DimenzijaGrida) throw "Greska!";

	return this->MatricaOrganizama[index];
}

void GridOrganizama::ProvediPravilaGeneracije() {
	bool* PomocnaMatrica = new bool[this->DimenzijaGrida * this->DimenzijaGrida];
	int tindex = 0;
	for (int y = 0; y < this->DimenzijaGrida; y++) {
		for (int x = 0; x < this->DimenzijaGrida; x++) {
			int BrojSusjeda = this->GetBrojSusjeda(x,y);
			//std::cout << "BS: " << x << "/" << y << " -> " << BrojSusjeda << std::endl;	DEBUG
			if (BrojSusjeda < 2 || BrojSusjeda > 3) PomocnaMatrica[tindex] = false;
			else if (BrojSusjeda == 3) PomocnaMatrica[tindex] = true;
			else PomocnaMatrica[tindex] = this->at(x, y);

			tindex++;
		}
	}

	this->RelMem();
	this->MatricaOrganizama = PomocnaMatrica;

}

void GridOrganizama::draw(sf::Vector2f PocetakCrtanja) {
	sf::Vector2f MjestoCrtanja;
	this->GetMisemOdabranuCeliju(PocetakCrtanja);

	for (int y = 0; y < this->DimenzijaGrida; y++) {
		for (int x = 0; x < this->DimenzijaGrida; x++) {
			MjestoCrtanja.x = PocetakCrtanja.x + (x * this->DimenzijaCelije);
			MjestoCrtanja.y = PocetakCrtanja.y + (y * this->DimenzijaCelije);

			if (MjestoCrtanja.x < 0 || MjestoCrtanja.x >= this->RenWin->getSize().x) continue;
			if (MjestoCrtanja.y < 0 || MjestoCrtanja.y >= this->RenWin->getSize().y) continue;			

			if (this->at(x, y)) this->Celija.setFillColor(sf::Color::Green);
			else if(this->OznacenaCelija.x == x && this->OznacenaCelija.y == y) this->Celija.setFillColor(sf::Color::Red);

			this->Celija.setPosition(MjestoCrtanja);
			this->RenWin->draw(this->Celija);
			this->Celija.setFillColor(sf::Color::Black);
		}
	}

}

int GenRand(int min, int max) {
	return rand() % (max - min + 1) + min;
}
