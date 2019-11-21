#include "stdafx.h"
#include "Menue.h"
const std::string SpielendeNachricht="Spiel zu Ende";

void Menue::text(std::string s)
{
	Gosu::Color c = this->textfarbe;
	this->schrift->draw_text(s, text_pos.x, text_pos.y, 5, 1,1, c);
	this->text_pos.y = int(this->text_pos.y + 30 * this->scale);
}

void Menue::text(std::string s,Gosu::Color c)
{
	this->schrift->draw_text(s,text_pos.x, text_pos.y,5,1,1,c);
	this->text_pos.y = int(this->text_pos.y + 30 *this->scale);
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



//void Menue::set_schrift(std::shared_ptr<Gosu::Font> s)
//{
//	this->schrift = s;
//}

void Menue::draw(int spielzeit,int punktzahl,int anzahlTeile)
{
	
	int text_scale;
	//schrift->draw_text("Spielzeit: " + std::to_string(spielzeit / 60) + "min " + std::to_string(spielzeit % 60) + "s", l + 10 * menue.scale, menue.scale*(10), 5, 1, 1, Gosu::Color::BLACK);
	//schrift->draw_text("Punkte: " + std::to_string(spielfeld.get_score()), hoehePxlSpielfeld + 10 * menue.scale, menue.scale*(30 * 1 + 10), 5, 1, 1, Gosu::Color::BLACK);
	//schrift->draw_text("Platzierte Teile: " + std::to_string(spielfeld.get_anzPlatzSpielsteine()), hoehePxlSpielfeld + 10 * menue.scale, (30 * 2 + 10)*menue.scale, 5, 1, 1, Gosu::Color::BLACK);
	if(!overlay) {
		this->set_text_pos(pos.y+10*scale,pos.x+10*scale);
		this->text("Spielzeit: " + std::to_string(spielzeit / 60) + "min " + std::to_string(spielzeit % 60) + "s");
		this->text("Punkte: " + std::to_string(punktzahl));
		this->text("Steine: "+std::to_string(anzahlTeile));
		if (menueHoehe>scale*500) { 
			text_pos.y += 20 * scale;
		}
	}
	else {

	}
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
		this->text("M: Menue ausblenden");
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
		text_scale =int(this->spielfeldLaenge / this->schrift->text_width(SpielendeNachricht));
		//this->schrift->draw_text_rel(SpielendeNachricht,this->spielfeldLaenge/2,this->spielfeldLaenge/2,5,0.5,0.5,text_scale,text_scale,Gosu::interpolate(this->textHervorheben,Gosu::Color(0x70d00000)),Gosu::AM_INTERPOLATE);
		Gosu::Graphics::transform(Gosu::rotate(this->winkel, this->spielfeldLaenge / 2, this->spielfeldLaenge / 2), [&] {this->schrift->draw_text_rel(SpielendeNachricht, this->spielfeldLaenge / 2, this->spielfeldLaenge / 2, 5, 0.5, 0.5, text_scale, text_scale, Gosu::interpolate(this->textHervorheben, Gosu::Color(0x70d00000)), Gosu::AM_INTERPOLATE); });
		break;
	default:
		this->text("M: Menue anzeigen");
		break;
	}
}

void Menue::set_text_pos(int y,int x)
{
	this->text_pos.y = y;
	this->text_pos.x = x;
}

void Menue::resize(int hoehe, int breite,int laenge)
{
	this->windowHoehe = hoehe;
	this->windowBreite = breite;
	this->spielfeldLaenge = laenge;
	this->scale = double(breite - laenge) / 200.0;
	if (abs(breite-hoehe)>Gosu::available_width()/10) {
		this->overlay = false;
		if (breite > hoehe) {//Menue links von Spielfeld
			this->menueBreite = breite - laenge;
			this->menueHoehe = hoehe;
			this->zeilenBreite = menueBreite;
			this->pos.x = laenge;// +10 * this->scale;
			this->pos.y =0;// +10 * this->scale;
			this->text_pos.x = pos.x+10*this->scale;
			this->text_pos.y = pos.y+10*this->scale;
			this->schrift = std::make_unique<Gosu::Font>(Gosu::Font(zeilenBreite/11));
		}
		else {//Menue ueber Spielfeld
			this->menueHoehe = hoehe - laenge;
			this->menueBreite = breite;
			this->pos.x = 0;
			this->pos.y = 0;
		}
	}
	else {
		this->overlay = true;
	}

}
