#pragma once
#include <cstdint>
#include <Gosu/Image.hpp>
#include <Gosu/Graphics.hpp>
#include <Gosu/Fwd.hpp>
#include <ctime>
#include <cstdlib>
#include <array>




const uint16_t SPIELFELD_BREITE=10;

struct Feld {
	bool status;
	Gosu::Color farbe;
};
struct koord {
	unsigned int x, y;
};
class Spielstein {
	
protected:
	//std::array<std::array<bool, 4>, 4> form;
	bool form[4][4];
	Gosu::Color farbe;
public:
	//Spielstein();
	//void draw();
};
class Spielfeld
{
	
	Gosu::Image bild;
	std::array<std::array<Feld,SPIELFELD_BREITE>,SPIELFELD_BREITE> zustand;
	int64_t score;
	time_t startzeit;
	koord refpos = {0,0};//obere linke Ecke
	//uint16_t hoehePxlSpielfeld;
	//uint16_t hoehePxlAbschnitt;
	//Spielstein naechsterSpielstein;
public:
	unsigned int hoehe();
	void reset();
	double dauer();//Zeit seit start in s
	bool platzbelegt(unsigned int y, unsigned int x);
	void platziereAbschnitt(unsigned int y,unsigned int x,Gosu::Color c);
	void loescheAbschnitt(unsigned int y, unsigned int x);
	//bool platzieren(std::array<std::array<bool,4>,4> form,koord pos);
	//void platzieren(AktiverSpielstein& aktiverSpielstein);
	void draw(uint16_t hoehePxl);
	//Spielstein nehmeSpielstein();
	std::array<std::array<Feld, SPIELFELD_BREITE>, SPIELFELD_BREITE> get_zustand();
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
	void draw(uint16_t hoehePxl);
	unsigned int get_x();
	unsigned int get_y();
};
