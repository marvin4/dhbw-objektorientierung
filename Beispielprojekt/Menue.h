#pragma once
#include "Klassen.h"
#include<Gosu/Font.hpp>
#include<Gosu/Gosu.hpp>

enum Status
{
	inaktiv,aktiv,einstellungen,spielende
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
private:
	void text(std::string s);
	void text(std::string s,Gosu::Color c);
};

