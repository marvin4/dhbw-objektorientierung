#pragma once
#include <cstdint>
#include <Gosu/Image.hpp>
#include <Gosu/Graphics.hpp>
#include <ctime>
#include <cstdlib>
#include <array>



std::vector < Gosu::Color > farben = { Gosu::Color::BLUE,Gosu::Color::BLUE,Gosu::Color::RED,Gosu::Color::GREEN,Gosu::Color::YELLOW };
std::vector<std::array<std::array<bool, 4>, 4>> formen;
const uint16_t SPIELFELD_BREITE=10;

struct Feld {
	bool status;
	Gosu::Color farbe;
};
struct koord {
	uint16_t x, y;
};
class Spielfeld
{
	
	Gosu::Image bild;
	std::array<std::array<Feld,SPIELFELD_BREITE>,SPIELFELD_BREITE> zustand;
	int64_t score;
	time_t startzeit;
	koord refpos = {0,0};//obere linke Ecke
public:
	uint16_t hoehe();
	void reset();
	double dauer();//Zeit seit start in s

};
class Spielstein {
	Gosu::Color farbe;

public:
	Spielstein();
	void draw();
};
class AktiverSpielstein : public Spielstein {
	koord positionAufSpielfeld;//Position von linker Ecke aus
public:
	AktiverSpielstein(AktiverSpielstein const& kopie);
	bool platzieren();
};
