#pragma once
#include <cstdint>
#include <Gosu/Image.hpp>
#include <Gosu/Graphics.hpp>
#include <Gosu/Fwd.hpp>
#include <ctime>
#include <cstdlib>
#include <array>
#include <Gosu/Math.hpp>

const int SPIELFELD_BREITE=10;

struct Feld {
	bool status;
	Gosu::Color farbe;
};
struct koord {
	 int x, y;
};
class Spielstein {
	
protected:
	//std::array<std::array<bool, 4>, 4> form;
	bool form[4][4];
	Gosu::Color farbe;
public:
	//Spielstein();
	//void draw();
	bool spalteBelegt(int spalte);
	bool zeileBelegt(int zeile);
};
class Spielfeld
{
	
	Gosu::Image bild;
	std::array<std::array<Feld,SPIELFELD_BREITE>,SPIELFELD_BREITE> zustand;
	int64_t score;
	time_t startzeit;
	koord refpos = {0,0};//obere linke Ecke
	int anzPlatzSpielsteine;
	//int hoehePxlSpielfeld;
	//int hoehePxlAbschnitt;
	//Spielstein naechsterSpielstein;
public:
	 int hoehe();
	void reset();
	double dauer();//Zeit seit start in s
	bool platzbelegt( int y,  int x);
	void platziereAbschnitt( int y, int x,Gosu::Color c);
	void loescheAbschnitt( int y,  int x);
	void addZuScore(int64_t punktzahl);
	void upanzPlatzSpielsteine();
	//bool platzieren(std::array<std::array<bool,4>,4> form,koord pos);
	//void platzieren(AktiverSpielstein& aktiverSpielstein);
	void draw(int hoehePxl);
	//Spielstein nehmeSpielstein();
	std::array<std::array<Feld, SPIELFELD_BREITE>, SPIELFELD_BREITE> get_zustand();
	int64_t get_score();
	int get_anzPlatzSpielsteine();
};


class AktiverSpielstein : public Spielstein {
	koord positionAufSpielfeld;//Position von linker Ecke aus
public:
	//AktiverSpielstein(AktiverSpielstein const& kopie);//nutzbar falls Spielsteine erstellt werden aber nicht direkt auf dem Spielfeld sind
	AktiverSpielstein();
	bool platzieren(Spielfeld& spielbrett);
	void rechtsRotieren();
	void linksRotieren();
	void linksBewegen();
	void rechtsBewegen();
	void obenBewegen();
	void untenBewegen();
	void draw(int hoehePxl);
	 int get_x();
	 int get_y();
	void neu();
	
};
