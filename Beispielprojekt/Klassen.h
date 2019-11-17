#pragma once
#include <cstdint>
#include <Gosu/Image.hpp>
#include <Gosu/Graphics.hpp>
#include <Gosu/Fwd.hpp>
#include <ctime>
#include <cstdlib>
#include <array>
#include <vector>
#include <Gosu/Math.hpp>
#include <iostream>

const int SPIELFELD_BREITE=10;

const std::vector<bool> formen4 = {1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,/**/1,1,0,0,1,0,0,0,1,0,0,0,0,0,0,0,/**/1,1,0,0,0,1,0,0,0,1,0,0,0,0,0,0/*
							    */,1,1,1,0,0,1,0,0,0,0,0,0,0,0,0,0/**/,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,/**/1,1,0,0,0,1,1,0,0,0,0,0,0,0,0,0/*
							    */,0,1,1,0,1,1,0,0,0,0,0,0,0,0,0,0 };//4-teilige Figuren
const std::vector<bool> formen5_1= { 1,1,1,0,0,1,0,0,0,1,0,0,0,0,0,0,/**/1,1,0,0,1,0,0,0,1,1,0,0,0,0,0,0,/**/1,1,0,0,1,1,0,0,0,1,0,0,0,0,0,0/**/
							      ,1,0,0,0,1,1,0,0,1,0,0,0,1,0,0,0/**/,0,1,0,0,1,1,0,0,1,0,0,0,1,0,0,0,/**/1,1,1,0,1,0,0,0,1,0,0,0,0,0,0,0/**/
								  ,0,1,0,0,1,1,1,0,0,1,0,0,0,0,0,0 
};//5-teilige Figuren 1 Set
struct Feld {
	bool status;
	Gosu::Color farbe;
};
struct Koord {
	 int x, y;
};
class Spielstein {
protected:
	//std::array<std::array<bool, 4>, 4> form;
	Gosu::Color farbe;
public:
	//Spielstein();
	//void draw();
	std::array<std::array<bool,4>,4>form;
	bool spalteBelegt(int spalte);
	bool zeileBelegt(int zeile);
	int zeilen();
	int spalten();
	void rotiere();
};
class Spielfeld
{
	
	Gosu::Image bild;
	std::array<std::array<Feld,SPIELFELD_BREITE>,SPIELFELD_BREITE> zustand;
	int64_t score;
	time_t startzeit;
	Koord refpos = {0,0};//obere linke Ecke
	int anzPlatzSpielsteine;
	
	//int hoehePxlSpielfeld;
	//int hoehePxlAbschnitt;
	//Spielstein naechsterSpielstein;
public:
	std::vector<bool> formen;
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
	bool hatPlatzFuerSpielstein(Spielstein spielstein);
};


class AktiverSpielstein : public Spielstein {
	Koord positionAufSpielfeld;//Position von linker Ecke aus
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
	void neu(std::vector<bool>& formen);
	
};
