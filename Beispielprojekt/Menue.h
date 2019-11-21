#pragma once
#include "Klassen.h"
#include<Gosu/Font.hpp>
#include<Gosu/Gosu.hpp>

enum Status
{
	inaktiv,aktiv,einstellungen,spielende
};

struct Farbschema {
	std::string name = "standard";
	std::vector < Gosu::Color> farben = { Gosu::Color(0xffdf0000),Gosu::Color(0xff0000df) ,Gosu::Color(0xff00df00) ,Gosu::Color(0xffdfdf00),Gosu::Color(0xff700000),
	Gosu::Color(0xff007000),Gosu::Color(0xff000070),Gosu::Color(0xffff7000),Gosu::Color(0xff007070)
	};
};
struct Design {
	std::string name;
};

class Menue
{
	int menueHoehe=600, menueBreite=200;
	int winkel;
	//Status status=einstellungen;
	Status status = einstellungen;
	std::shared_ptr<Gosu::Font> schrift=nullptr;
	Koord pos = {0,0};
	Status vStatus = aktiv;
public:
	double scale=1;
	void update();
	int windowHoehe = 600, windowBreite = 800,spielfeldLaenge = 600,hintergrund=0;
	Gosu::Color textfarbe = Gosu::Color::BLACK;
	Gosu::Color textHervorheben = Gosu::Color::RED;
	Status get_status();
	void set_status(Status s);
	Status get_vStatus();
	//bool set_windowSize(unsigned int maxHoehe, unsigned int maxBreite, unsigned int hoehe = 600, unsigned int breite = 800);//not needed anymore
	/*Menue();*/
	void set_schrift(std::shared_ptr<Gosu::Font> s);
	void draw();
	void set_pos(Koord p);
	void resize(int hoehe,int breite,int laenge);
private:
	void text(std::string s);
	void text(std::string s,Gosu::Color c);
};

