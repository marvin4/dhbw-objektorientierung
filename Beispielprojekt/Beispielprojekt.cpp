#include "stdafx.h"

#include <Gosu/Gosu.hpp>
#include <Gosu/AutoLink.hpp>

#include <vector>
#include <string>
#include <iostream>

//#include Eigene Klassen
#include "Klassen.h"
#include "Menue.h"

// Simulationsgeschwindigkeit
const double DT = 100.0;

class GameWindow : public Gosu::Window
{
	int hoehePxlSpielfeld;
	int hoehePxlAbschnitt;
	//int hintergrund = 0;
	Menue menue;
	Spielfeld spielfeld;
	AktiverSpielstein aktiverSpielstein;
	//Gosu::Font font;
	//Gosu::Image hintergrund;
	std::shared_ptr<Gosu::Font> ptr_font;
	std::vector<std::shared_ptr<Gosu::Image>>hintergruende;
	std::shared_ptr<Gosu::Image>ptr_hintergrund;
	std::vector<std::string> pfade = {"media/Unterwasser1920x1080.png","media/Holz1920x1080.png"};
public:
	
	
	GameWindow()
		: Window(800, 600,false,1/60,true)//,font(20)//,hintergrund("media/HintergrundHolz800x600.png")
	{
		set_caption("Testspiel");
		hoehePxlSpielfeld = (std::min(width(), height())- (std::min(width(), height())%SPIELFELD_BREITE));
		hoehePxlAbschnitt = (hoehePxlSpielfeld / SPIELFELD_BREITE);
		spielfeld.reset();
		spielfeld.formen = formen4;
		ptr_font = std::make_shared<Gosu::Font>(Gosu::Font(20));
		for (std::string elem : pfade) {
			hintergruende.push_back(std::make_shared<Gosu::Image>(Gosu::Image(elem)));
		}
		ptr_hintergrund = hintergruende.at(menue.hintergrund);
		menue.set_schrift(ptr_font);
	}
	
	// wird bis zu 60x pro Sekunde aufgerufen.
	// Wenn die Grafikkarte oder der Prozessor nicht mehr hinterherkommen,
	// dann werden `draw` Aufrufe ausgelassen und die Framerate sinkt
	void draw() override
	{	
		hoehePxlSpielfeld = (std::min(width(), height()) - (std::min(width(), height()) % SPIELFELD_BREITE));
		hoehePxlAbschnitt = (hoehePxlSpielfeld / SPIELFELD_BREITE);
		//hintergrund.draw(0, 0, 0,double(width())/double(hintergrund.width()),double(height())/double(hintergrund.height()));//ohne pointer
		//ptr_hintergrund->draw(0, 0, 0, double(width()) / double(ptr_hintergrund->width()), double(height()) / double(ptr_hintergrund->height()));mit skalierung
		ptr_hintergrund->draw(0,0, 0, 1.0,1.0);
		menue.scale = double(width() - hoehePxlSpielfeld) / 200.0;
		menue.set_pos({int(hoehePxlSpielfeld+20*menue.scale),int(20+menue.scale*200)});
		menue.windowBreite = width();
		menue.windowHoehe=height();
		menue.spielfeldLaenge = hoehePxlSpielfeld;
			Gosu::Graphics::draw_rect(0, 0, hoehePxlSpielfeld, hoehePxlSpielfeld, Gosu::Color(0x20000000), 1, Gosu::AM_INTERPOLATE);
			spielfeld.draw(this->hoehePxlAbschnitt);
			aktiverSpielstein.draw(this->hoehePxlAbschnitt);
			menue.draw();
			ptr_font->draw_text("Spielzeit: " + std::to_string(int(spielfeld.dauer() / 60)) + "min " + std::to_string(int(spielfeld.dauer()) % 60) + "s", hoehePxlSpielfeld + 20*menue.scale, 20+menue.scale*50, 5, menue.scale, menue.scale, Gosu::Color::BLACK);
			ptr_font->draw_text("Punktestand: " + std::to_string(spielfeld.get_score()), hoehePxlSpielfeld + 20*menue.scale, 20+menue.scale*100, 5, menue.scale, menue.scale, Gosu::Color::BLACK);
			ptr_font->draw_text("Platzierte Teile: " + std::to_string(spielfeld.get_anzPlatzSpielsteine()), hoehePxlSpielfeld + 20*menue.scale, 20+150*menue.scale, 5, menue.scale, menue.scale, Gosu::Color::BLACK);
		
	}

	// Wird 60x pro Sekunde aufgerufen
	void update() override
	{
		
		//std::cout << Gosu::fps() << std::endl;
		//std::cout << spielfeld.hatPlatzFuerSpielstein(aktiverSpielstein);
		menue.update();
	}

	void button_down(Gosu::Button button) override
	{
		
		if (button == Gosu::KB_ESCAPE) {
			close();
		}
		else {//std::cout << "??????" <<menue.get_status()<< std::endl;
			switch (menue.get_status()) {
			case(inaktiv):
				if (button == Gosu::KB_M) {
					menue.set_status(aktiv);
				}
				else if (button == Gosu::KB_E) {
					menue.set_status(einstellungen);
				}
				break;
			case(aktiv):
				if (button == Gosu::KB_M) {
					menue.set_status(inaktiv);
				}
				else if (button == Gosu::KB_E) {
					menue.set_status(einstellungen);
				}
				break;
			case(einstellungen):
				//std::cout << "einstellungen"<<std::endl;;
				if ((button == Gosu::KB_E) || (button == Gosu::KB_ENTER)) {
					menue.set_status(menue.get_vStatus());
				}
				else if (button == Gosu::KB_M) {
					menue.set_status(inaktiv);
				}
				else if (button == Gosu::KB_W) {
					std::cout << menue.hintergrund << std::endl;;
					menue.hintergrund = Gosu::wrap(menue.hintergrund + 1, 0, int(hintergruende.size()));
					ptr_hintergrund = hintergruende.at(menue.hintergrund);
				}
				/*else if (button == Gosu::KB_LEFT) {
					menue.hintergrund = Gosu::wrap(menue.hintergrund - 1, 0, hintergruende.size());
					ptr_hintergrund = hintergruende.at(menue.hintergrund);
				}*/
				break;
			case(spielende):
				if ((button==Gosu::KB_R) || (button==Gosu::KB_ENTER)) {
					spielfeld.reset();
					menue.set_status(aktiv);
				}
				else if (button==Gosu::KB_E) {
					menue.set_status(einstellungen);
				}
				break;
			default:
				//std::cout <<" ? ? ? ? ? "<< std::endl;
				
				break;
			}
		}	Window::button_down(button);
	}

	void button_up(Gosu::Button button) override
	{
		
		if (button == Gosu::KB_LEFT) {//Spiel Steuerung
			aktiverSpielstein.linksBewegen();
		}
		else if (button == Gosu::KB_RIGHT) {
			aktiverSpielstein.rechtsBewegen();
		}
		else if (button == Gosu::KB_UP) {
			aktiverSpielstein.obenBewegen();
		}
		else if (button == Gosu::KB_DOWN) {
			aktiverSpielstein.untenBewegen();
		}
		else if (button == Gosu::KB_PAGE_UP) {
			aktiverSpielstein.linksRotieren();
		}
		else if (button == Gosu::KB_PAGE_DOWN) {
			aktiverSpielstein.rechtsRotieren();
		}
		else if (button == Gosu::KB_SPACE) {
			if (aktiverSpielstein.platzieren(spielfeld)) {
				 int y = aktiverSpielstein.get_y();
				 int x = aktiverSpielstein.get_x();
				// int s = 0;
				// int z = 0;
				 int reihen = 0;
				auto zustand = spielfeld.get_zustand();
				for ( int i = y; i < (y + 4); i++) {//Darf nich fuer Bereiche ausserhalb des Spielfelds ausgefuehrt werden
					if (aktiverSpielstein.zeileBelegt(i-y)) {
						bool kompletteReihe = true;
						for ( int j = 0; j < SPIELFELD_BREITE; j++) {
							if (!zustand.at(i).at(j).status) {
								kompletteReihe = false;
								break;
							}
						}
						if (kompletteReihe) {
							reihen = reihen + 1;
							for ( int k = 0; k < SPIELFELD_BREITE; k++) {
								spielfeld.loescheAbschnitt(i, k);
							}
						}
					}
				}
				for ( int i = x; i < (x + 4); i++) {//Darf nich fuer Bereiche ausserhalb des Spielfelds ausgefuehrt werden
					if (aktiverSpielstein.spalteBelegt(i-x)) {
						bool kompletteReihe = true;
						for ( int j = 0; j < SPIELFELD_BREITE; j++) {
							if (!zustand.at(j).at(i).status) {
								kompletteReihe = false;
								break;
							}
						}
						if (kompletteReihe) {
							reihen = reihen + 1;
							for ( int k = 0; k < SPIELFELD_BREITE; k++) {
								spielfeld.loescheAbschnitt(k, i);
							}
						}
					}
				}
				if (reihen > 0) {//score berrechnen
					spielfeld.addZuScore(int(std::pow(2, reihen) * 50));
				}
				spielfeld.upanzPlatzSpielsteine();
				aktiverSpielstein.neu(spielfeld.formen);
			}
		}
		
	}
};

// C++ Hauptprogramm
int main()
{
	GameWindow window;
	window.show();
}
