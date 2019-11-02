#include "stdafx.h"
#include "Klassen.h"

std::vector < Gosu::Color> farben= { Gosu::Color(0xffdf0000),Gosu::Color(0xff0000df) ,Gosu::Color(0xff00df00) ,Gosu::Color(0xffdfdf00),Gosu::Color(0xff700000),
Gosu::Color(0xff007000),Gosu::Color(0xff000070),Gosu::Color(0xffff7000),Gosu::Color(0xff007070)
};
std::vector<bool> formen = {1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,/**/1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,/**/0,1,0,0,1,1,1,0,0,0,0,0,0,0,0,0/*
						 */,1,1,1,0,1,0,0,0,0,0,0,0,0,0,0,0/**/,1,0,0,0,1,1,0,0,0,1,0,0,0,0,0,0,/**/0,1,0,0,1,1,0,0,1,0,0,0,0,0,0,0/*
						 */,1,1,1,0,0,0,1,0,0,0,0,0,0,0,0,0};//4-teilige Figuren

	 int Spielfeld::hoehe() {
		return this->zustand.size();
	}
	void Spielfeld::reset() {
		for (std::array<Feld,SPIELFELD_BREITE>& zeile_ref : this->zustand) {
			for (Feld& elem_ref : zeile_ref) {
				elem_ref.status = false;
			}
		}
		this->startzeit = time(NULL);
		this->score = 0;
		this->anzPlatzSpielsteine = 0;
		srand(time(NULL));
		
	}
	double Spielfeld::dauer() {
		return difftime(time(NULL), this->startzeit);
	}
	bool Spielfeld::platzbelegt( int y,  int x) {
		return this->zustand.at(y).at(x).status;
	}
	void Spielfeld::platziereAbschnitt( int y,  int x, Gosu::Color c) {
		this->zustand.at(y).at(x).farbe = c;
		this->zustand.at(y).at(x).status = true;
	}
	void Spielfeld::loescheAbschnitt( int y,  int x) {
		this->zustand.at(y).at(x).status = false;
	}
	/*void Spielfeld::platzieren(AktiverSpielstein& aktiverSpielstein) {
		if (aktiverSpielstein.platzieren(*this)) {

		}
	}*/
	void Spielfeld::addZuScore(int64_t punktzahl) {
		this->score = this->score + punktzahl;
	}
	void Spielfeld::upanzPlatzSpielsteine() {
		this->anzPlatzSpielsteine = this->anzPlatzSpielsteine + 1;
	}
	std::array<std::array<Feld, SPIELFELD_BREITE>, SPIELFELD_BREITE> Spielfeld::get_zustand() {
		return this->zustand;
	}
	int64_t Spielfeld::get_score() {
		return this->score;
	}
	int Spielfeld::get_anzPlatzSpielsteine() {
		return this->anzPlatzSpielsteine;
	}
	void Spielfeld::draw(int hoehePxl) {
		for ( int y = 0; y < SPIELFELD_BREITE; y++) {
			for ( int x = 0; x < SPIELFELD_BREITE; x++) {
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
	bool Spielstein::spalteBelegt(int spalte) {
		bool r=false;
		if (this->form[0][spalte]|| this->form[1][spalte] ||this->form[2][spalte] || this->form[3][spalte] ) {
			r = true;
		}
		return r;
	}
	bool Spielstein::zeileBelegt(int zeile) {
		bool r = false;
		if (this->form[zeile][0] || this->form[zeile][1] || this->form[zeile][2] || this->form[zeile][3]) {
			r = true;
		}
		return r;
	}

	bool AktiverSpielstein::platzieren(Spielfeld& spielbrett) {
		//bool erfolg=spielbrett.platzieren(this->form, this->positionAufSpielfeld);

		bool erfolg = true;
		for ( int i = 0; i < 4; i++) {
			for ( int j = 0; j < 4; j++) {
				if (this->form[i][j] && spielbrett.platzbelegt(this->positionAufSpielfeld.y+i,this->positionAufSpielfeld.x+j)) {
					erfolg = false;
					break;
				}
			}
		}
		if (erfolg) {
			for ( int i = 0; i < 4; i++) {
				for ( int j = 0; j < 4; j++) {
					if (this->form[i][j]) {
						spielbrett.platziereAbschnitt(this->positionAufSpielfeld.y + i, this->positionAufSpielfeld.x + j, this->farbe);
					}
				}
			}
			/*this->farbe=farben.at(rand() % farben.size());//eventuell unterschiedlich Farbe und Form von vorheriger auswaehlen
			 int random = 16 * (rand() % (formen.size() / 16));//verlegt in Methode neu
			for ( int i = 0; i < 4; i++) {
				for ( int j = 0; j < 4; j++) {
					this->form[i][j] = formen.at(random + j + (i * 4));
				}
			}*/
		}

		return erfolg;
	}
	void AktiverSpielstein::neu() {
		this->farbe=farben.at(rand() % farben.size());//eventuell unterschiedlich Farbe und Form von vorheriger auswaehlen
			int random = 16 * (rand() % (formen.size() / 16));
			for ( int i = 0; i < 4; i++) {
				for ( int j = 0; j < 4; j++) {
					this->form[i][j] = formen.at(random + j + (i * 4));
				}
			}
			this->positionAufSpielfeld.x = Gosu::clamp(this->positionAufSpielfeld.x,0,SPIELFELD_BREITE-4);
			this->positionAufSpielfeld.y = Gosu::clamp(this->positionAufSpielfeld.y, 0, SPIELFELD_BREITE-4);
	}
	void AktiverSpielstein::rechtsRotieren() {//eventuell position um die rotiert wird abhaengig von form machen
		
		for ( int i = 0; i < 2; i++) {
			for ( int j = i; j < (3 - i); j++) {
				bool tmp;
				tmp = this->form[i][j];
				this->form[i][j] = this->form[3-j][i];
				this->form[3-j][i] = this->form[3 - i][3 - j];
				this->form[3 - i][3 - j] = this->form[j][3-i];
				this->form[j][3-i] = tmp;
			}
		}
	}
	void AktiverSpielstein::linksRotieren() {//eventuell position um die rotiert wird abhaengig von form machen
		for ( int i = 0; i < 2; i++) {
			for ( int j = i; j < (3 - i); j++) {
				bool tmp;
				tmp = this->form[i][j];
				this->form[i][j] = this->form[j][3 - i];
				this->form[j][3 - i] = this->form[3 - i][3 - j];
				this->form[3 - i][3 - j] = this->form[3 - j][i];
				this->form[3 - j][i] = tmp;
			}
		}
	}
	AktiverSpielstein::AktiverSpielstein() {
		this->positionAufSpielfeld.x = (SPIELFELD_BREITE / 2);
		this->positionAufSpielfeld.y = (SPIELFELD_BREITE / 2);
		this->farbe = farben.at(rand() % farben.size());
		 int random = 16*(rand() % (formen.size()/16));
		for ( int i = 0; i < 4; i++) {
			for ( int j = 0; j < 4; j++) {
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
	void AktiverSpielstein::draw(int hoehePxl) {
		for ( int y = 0; y < 4; y++) {
			for ( int x = 0; x < 4; x++) {
				if (this->form[y][x]) {
					Gosu::Graphics::draw_rect(hoehePxl*(x+this->positionAufSpielfeld.x), hoehePxl*(y+this->positionAufSpielfeld.y), hoehePxl, hoehePxl, this->farbe, 4);
				}
			}
		}
	}
	void AktiverSpielstein::linksBewegen() {
		int offset = 0;
		for (int i = 0; i < 4; i++) {
			if (this->spalteBelegt(i)) {
				offset = i;
				break;
			}
		}
		if (offset+this->positionAufSpielfeld.x>0) {
			this->positionAufSpielfeld.x = this->positionAufSpielfeld.x - 1;
		}
		else {

		}
	}
	void AktiverSpielstein::rechtsBewegen() {
		int offset = 0;
		for (int i = 3; i>0;i--) {
			if (this->spalteBelegt(i)) {
				offset = i;
				break;
			}
		}
		if (offset+1+this->positionAufSpielfeld.x<SPIELFELD_BREITE) {
			this->positionAufSpielfeld.x = this->positionAufSpielfeld.x + 1;
		}
		else {

		}
	}
	void AktiverSpielstein::obenBewegen() {
		int offset = 0;
		for (int i = 0; i < 4; i++) {
			if (this->zeileBelegt(i)) {
				offset = i;
				break;
			}
		}
		if (offset + this->positionAufSpielfeld.y > 0) {
			this->positionAufSpielfeld.y = this->positionAufSpielfeld.y - 1;
		}
		else {

		}
	}
	void AktiverSpielstein::untenBewegen() {
		int offset = 0;
		for (int i = 3; i > 0; i--) {
			if (this->zeileBelegt(i)) {
				offset = i;
				break;
			}
		}
		if (offset + 1 + this->positionAufSpielfeld.y < SPIELFELD_BREITE) {
			this->positionAufSpielfeld.y = this->positionAufSpielfeld.y + 1;
		}
		else {

		}
	}
	 int AktiverSpielstein::get_x() {
		return this->positionAufSpielfeld.x;
	}
	 int AktiverSpielstein::get_y() {
		return this->positionAufSpielfeld.y;
	}