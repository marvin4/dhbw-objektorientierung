#include "stdafx.h"
#include "Menue.h"
const std::string SpielendeNachricht="Spiel zu Ende";

void Menue::text(std::string s,Gosu::Color c)
{
	if (c == NULL) {
		c = this->textfarbe;
	}
	this->schrift->draw_text(s,pos.x, pos.y,5, this->scale, this->scale,c);
	this->pos.y = this->pos.y + 40 *this->scale;
}

Status Menue::get_status()
{
	return Status();
}

//bool Menue::set_windowSize(unsigned int maxHoehe,unsigned int maxBreite,unsigned int hoehe,unsigned int breite)
//{
//	int r = false;
//	hoehe = Gosu::clamp(hoehe, unsigned int(0), maxHoehe);
//	breite = Gosu::clamp(breite, unsigned int(0), maxBreite);
//	if ((hoehe < breite)&&(breite-hoehe>160)&&(hoehe>100)) {
//		r = true;
//		
//	}
//	return r;
//}

//Menue::Menue()
//{
//	this->status = einstellungen;
//	this->menueHoehe = 600;
//	this->menueBreite = 800;
//}

void Menue::set_schrift(std::shared_ptr<Gosu::Font> s)
{
	this->schrift = s;
}

void Menue::draw()
{
	int text_scale;
	switch (this->status)
	{
	case(einstellungen):
		this->text("WIP");
		break;
	case(aktiv):
		this->text("Funktionen:",this->textHervorheben);
		this->text("E: Einstellungen");
		this->text("M: Diese Menü ausblenden");
		this->text("Steuerung:",this->textHervorheben);
		this->text("Bewgung: Pfeiltasten");
		this->text("Rotieren: Bild hoch/runter");
		break;
	case(spielende):
		this->text("Spielzuende:", this->textHervorheben);
		this->text("E: Einstellungen");
		this->text("Enter: neues Spiel");
		text_scale = this->spielfeldLaenge / this->schrift->text_width(SpielendeNachricht);
		this->schrift->draw_text_rel(SpielendeNachricht,this->spielfeldLaenge/2,this->spielfeldLaenge/2,5,0.5,0.5,text_scale,text_scale,Gosu::interpolate(this->textHervorheben,Gosu::Color(0x70d00000)),Gosu::AM_INTERPOLATE);
		Gosu::rot
		break;
	default:
		this->text("M: Menü anzeigen");
		break;
	}
}

void Menue::set_pos(koord p)
{
	this->pos = p;
}
