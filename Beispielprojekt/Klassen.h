#pragma once
#include <Gosu/Image.hpp>
#include <Gosu/Graphics.hpp>
#include <ctime>

const uint16_t SPIELFELD_BREITE=10;
struct Feld {
	bool status;
	Gosu::Color farbe;
};
class Spielfeld
{
	
	Gosu::Image bild;
	std::array<std::array<Feld,SPIELFELD_BREITE>,SPIELFELD_BREITE> zustand;
	int64_t score;
	time_t startzeit;
public:
	uint16_t hoehe();
	void reset();

};
