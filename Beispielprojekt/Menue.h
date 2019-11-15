#pragma once
#include "Klassen.h"
#include<Gosu/Font.hpp>
#include<Gosu/GraphicsBase.hpp>

enum Status
{
	inaktiv,aktiv,einstellungen,spielende
};

	

class Menue
{
	int menueHoehe=600, menueBreite=200;
	//Status status=einstellungen;
	Status status = spielende;
	std::shared_ptr<Gosu::Font> schrift=nullptr;
	koord pos = {0,0};
	
public:
	double scale=1;
	int windowHoehe = 600, windowBreite = 800,spielfeldLaenge = 600;
	Gosu::Color textfarbe = Gosu::Color::BLACK;
	Gosu::Color textHervorheben = Gosu::Color::RED;
	Status get_status();
	//bool set_windowSize(unsigned int maxHoehe, unsigned int maxBreite, unsigned int hoehe = 600, unsigned int breite = 800);//not needed anymore
	/*Menue();*/
	void set_schrift(std::shared_ptr<Gosu::Font> s);
	void draw();
	void set_pos(koord p);
private:
	void text(std::string s,Gosu::Color c =NULL);
};

