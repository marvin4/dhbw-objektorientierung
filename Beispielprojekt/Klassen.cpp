#include "stdafx.h"
#include "Klassen.h"

std::vector < Gosu::Color> farben= { Gosu::Color(0xffff0000),Gosu::Color(0xff0000ff) ,Gosu::Color(0xff00ff00) ,Gosu::Color(0xffffff00)};
//std::vector<std::array<std::array<bool, 4>, 4>> formen;
//{{false,true,false,false},{true,true,true,false},{false,false,false,false},{false,false,false,false}}
//std::vector<bool[4][4]> formen = {};
//formen.push_back({false,true,false,false},{true,true,true,false},{false,false,false,false},{false,false,false,false} );
std::vector<bool> formen = {1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0};

	unsigned int Spielfeld::hoehe() {
		return this->zustand.size();
	}
	void Spielfeld::reset() {
		for (std::array<Feld,SPIELFELD_BREITE>& zeile_ref : this->zustand) {
			for (Feld& elem_ref : zeile_ref) {
				elem_ref.status = false;
			}
		}
		this->score = 0;
		this->startzeit = time(NULL);
		srand(time(NULL));
		
	}
	double Spielfeld::dauer() {
		return difftime(time(NULL), this->startzeit);
	}
	bool Spielfeld::platzbelegt(unsigned int y, unsigned int x) {
		return this->zustand.at(y).at(x).status;
	}
	void Spielfeld::platziereAbschnitt(unsigned int y, unsigned int x, Gosu::Color c) {
		this->zustand.at(y).at(x).farbe = c;
		this->zustand.at(y).at(x).status = true;
	}
	/*bool Spielfeld::platzieren(std::array<std::array<bool, 4>, 4> form, koord pos) {
		bool erfolg = true;

		return erfolg;
	}*/
	void Spielfeld::draw(uint16_t hoehePxl) {
		for (unsigned int y = 0; y < SPIELFELD_BREITE; y++) {
			for (unsigned int x = 0; x < SPIELFELD_BREITE; x++) {
				if (this->zustand.at(y).at(x).status) {
					Gosu::Graphics::draw_rect(x*hoehePxl, y*hoehePxl, hoehePxl, hoehePxl, this->zustand.at(y).at(x).farbe, 3);
				}
			}
		}
	}
	/*Spielstein Spielfeld::nehmeSpielstein()
	{
		return Spielstein();
	}*/

	/*Spielstein::Spielstein() {
		this->farbe = farben.at(rand()%farben.size());
		this->form = formen.at(rand() % formen.size());
	}*/

	bool AktiverSpielstein::platzieren(Spielfeld& spielbrett) {
		//bool erfolg=spielbrett.platzieren(this->form, this->positionAufSpielfeld);

		bool erfolg = true;//verschoben in Klasse Spielfeld
		for (unsigned int i = 0; i < 4; i++) {
			for (unsigned int j = 0; j < 4; j++) {
				if (this->form[i][j] && spielbrett.platzbelegt(this->positionAufSpielfeld.y+i,this->positionAufSpielfeld.x+j)) {
					erfolg = false;
					break;
				}
			}
		}
		if (erfolg) {
			for (unsigned int i = 0; i < 4; i++) {
				for (unsigned int j = 0; j < 4; j++) {
					if (this->form[i][j]) {
						spielbrett.platziereAbschnitt(this->positionAufSpielfeld.y + i, this->positionAufSpielfeld.x + j, this->farbe);
					}
				}
			}
		}

		return erfolg;
	}
	void AktiverSpielstein::rechtsRotieren() {
		auto kopie = this->form;
		for (unsigned int i = 0; i < 4;i++) {
			for (unsigned int j = 0; j < 4;j++) {
				this->form[i][j] = kopie[3-j][i];
			}
		}
	}
	void AktiverSpielstein::linksRotieren() {
		auto kopie = this->form;
		for (unsigned int i = 0; i < 4; i++) {
			for (unsigned int j = 0; j < 4; j++) {
				this->form[i][j] = kopie[j][3-i];
			}
		}
	}
	AktiverSpielstein::AktiverSpielstein() {
		this->positionAufSpielfeld.x = (SPIELFELD_BREITE / 2);
		this->positionAufSpielfeld.y = (SPIELFELD_BREITE / 2);
		this->farbe = farben.at(rand() % farben.size());
		unsigned int random = 16*(rand() % (formen.size()/16));
		for (unsigned int i = 0; i < 4; i++) {
			for (unsigned int j = 0; j < 4; j++) {
				this->form[i][j] = formen.at(random+j+(i*4));
			}
		}
		//this->form = formen.at(rand() % formen.size());
	}
	/*AktiverSpielstein::AktiverSpielstein(AktiverSpielstein const& kopie) {
		*this = kopie;
		this->positionAufSpielfeld.x = (SPIELFELD_BREITE / 2);
		this->positionAufSpielfeld.y = (SPIELFELD_BREITE / 2);
	}*/
	void AktiverSpielstein::draw(uint16_t hoehePxl) {
		for (unsigned int y = 0; y < 4; y++) {
			for (unsigned int x = 0; x < 4; x++) {
				if (this->form[y][x]) {
					Gosu::Graphics::draw_rect(hoehePxl*(x+this->positionAufSpielfeld.x), hoehePxl*(y+this->positionAufSpielfeld.y), hoehePxl, hoehePxl, this->farbe, 4);
				}
			}
		}
	}
	