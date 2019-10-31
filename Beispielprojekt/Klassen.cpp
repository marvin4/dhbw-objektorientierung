#include "stdafx.h"
#include "Klassen.h"

std::vector < Gosu::Color > farben= { Gosu::Color::BLUE,Gosu::Color::BLUE,Gosu::Color::RED,Gosu::Color::GREEN,Gosu::Color::YELLOW };
std::vector<std::array<std::array<bool, 4>, 4>> formen = { {{true,false,false,false},{true,false,false,false},{true,false,false,false},{true,false,false,false}} };


	uint16_t Spielfeld::hoehe() {
		return this->zustand.size();
	}
	void Spielfeld::reset() {
		for (std::array<Feld,SPIELFELD_BREITE>& zeile_ref : this->zustand) {
			for (Feld& elem_ref : zeile_ref) {
				elem_ref.status = 0;
			}
		}
		this->score = 0;
		this->startzeit = time(NULL);
		srand(time(NULL));
	}
	double Spielfeld::dauer() {
		return difftime(time(NULL), this->startzeit);
	}

	Spielstein::Spielstein() {
		this->farbe = farben.at(rand()%farben.size());
	}

	bool AktiverSpielstein::platzieren() {
		return true;
	}
	AktiverSpielstein::AktiverSpielstein(AktiverSpielstein const& kopie) {
		*this = kopie;
		this->positionAufSpielfeld.x = (SPIELFELD_BREITE / 2);
		this->positionAufSpielfeld.y = (SPIELFELD_BREITE / 2);
	}