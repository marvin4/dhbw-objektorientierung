#include "stdafx.h"
#include "Menue.h"
const std::string SpielendeNachricht="Spiel zu Ende";

void Menue::text(std::string s)
{
	Gosu::Color c = this->textfarbe;
	this->schrift->draw_text(s, pos.x, pos.y, 5, this->scale, this->scale, c);
	this->pos.y = int(this->pos.y + 40 * this->scale);
}

void Menue::text(std::string s,Gosu::Color c)
{
	this->schrift->draw_text(s,pos.x, pos.y,5, this->scale, this->scale,c);
	this->pos.y = int(this->pos.y + 40 *this->scale);
}

void Menue::update()
{
	switch (this->status) {
	case(spielende):
		if (this->winkel == 359) {
			this->winkel = 0;
		}
		else {
			this->winkel = this->winkel + 1;
		}
		break;
	default:
		break;
	}
}

Status Menue::get_status()
{
	return this->status;
}

void Menue::set_status(Status s)
{
	this->vStatus = this->status;
	this->status = s;
}

Status Menue::get_vStatus()
{
	return this->vStatus;
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
		this->text("Einstellungen:",this->textHervorheben);
		this->text("E: oeffnen/schliessen");
		this->text("R: neues Spiel");
		this->text("W: Hintergrund wechseln");
		this->text("Hintergrund: "+std::to_string(this->hintergrund+1));


		//this->text("Zeit beginntt nach 1.Form");
		break;
	case(aktiv):
		this->text("Funktionen:",this->textHervorheben);
		this->text("E: Einstellungen");
		this->text("M: Dieses Menue ausblenden");
		this->text("Esc: Spiel beenden");
		this->text("Steuerung:",this->textHervorheben);
		this->text("Bewegung: Pfeiltasten");
		this->text("Drehen: Bild hoch/runter");
		this->text("Platzieren: Leertaste");
		break;
	case(spielende):
		this->text("Spielzuende:", this->textHervorheben);
		this->text("E: Einstellungen");
		this->text("R: neues Spiel");
		this->text("Enter: neues Spiel");
		text_scale = int(this->spielfeldLaenge / this->schrift->text_width(SpielendeNachricht));
		//this->schrift->draw_text_rel(SpielendeNachricht,this->spielfeldLaenge/2,this->spielfeldLaenge/2,5,0.5,0.5,text_scale,text_scale,Gosu::interpolate(this->textHervorheben,Gosu::Color(0x70d00000)),Gosu::AM_INTERPOLATE);
		Gosu::Graphics::transform(Gosu::rotate(this->winkel, this->spielfeldLaenge / 2, this->spielfeldLaenge / 2), [&] {this->schrift->draw_text_rel(SpielendeNachricht, this->spielfeldLaenge / 2, this->spielfeldLaenge / 2, 5, 0.5, 0.5, text_scale, text_scale, Gosu::interpolate(this->textHervorheben, Gosu::Color(0x70d00000)), Gosu::AM_INTERPOLATE); });
		break;
	default:
		this->text("M: Menue anzeigen");
		break;
	}
}

void Menue::set_pos(Koord p)
{
	this->pos = p;
}

void Menue::resize(int hoehe, int breite)
{
	
}
