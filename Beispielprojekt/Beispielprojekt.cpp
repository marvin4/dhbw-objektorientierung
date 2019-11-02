#include "stdafx.h"

#include <Gosu/Gosu.hpp>
#include <Gosu/AutoLink.hpp>

#include <vector>
#include <string>
#include <iostream>

//#include "Vektor2d.h"
#include "Klassen.h"

// Simulationsgeschwindigkeit
const double DT = 100.0;

class GameWindow : public Gosu::Window
{
	uint16_t hoehePxlSpielfeld;
	uint16_t hoehePxlAbschnitt;
	Spielfeld spielfeld;
	AktiverSpielstein aktiverSpielstein;
public:
	Gosu::Image bild;
	

	GameWindow()
		: Window(800, 600)
	{
		set_caption("Gosu Tutorial Game mit Git");
		hoehePxlSpielfeld = (std::min(width(), height())- (std::min(width(), height())%SPIELFELD_BREITE));
		hoehePxlAbschnitt = (hoehePxlSpielfeld / SPIELFELD_BREITE);
		spielfeld.reset();
	}
	
	// wird bis zu 60x pro Sekunde aufgerufen.
	// Wenn die Grafikkarte oder der Prozessor nicht mehr hinterherkommen,
	// dann werden `draw` Aufrufe ausgelassen und die Framerate sinkt
	void draw() override
	{
		Gosu::Graphics::draw_rect(0,0,hoehePxlSpielfeld,hoehePxlSpielfeld,Gosu::Color::GRAY,1);
		spielfeld.draw(this->hoehePxlAbschnitt);
		aktiverSpielstein.draw(this->hoehePxlAbschnitt);
	}

	// Wird 60x pro Sekunde aufgerufen
	void update() override
	{
		//std::cout << Gosu::fps() << std::endl;
	}

	void button_down(Gosu::Button button) override
	{
		if (button == Gosu::KB_ESCAPE) {
			close();
		}
		else {
			Window::button_down(button);
		}
	}

	void button_up(Gosu::Button button) override
	{
		if (button == Gosu::KB_LEFT) {
			aktiverSpielstein.linksBewegen();
		}
		if (button == Gosu::KB_RIGHT) {
			aktiverSpielstein.rechtsBewegen();
		}
		if (button == Gosu::KB_UP) {
			aktiverSpielstein.obenBewegen();
		}
		if (button == Gosu::KB_DOWN) {
			aktiverSpielstein.untenBewegen();
		}
		if (button == Gosu::KB_PAGE_UP) {
			aktiverSpielstein.linksRotieren();
		}
		if (button == Gosu::KB_PAGE_DOWN) {
			aktiverSpielstein.rechtsRotieren();
		}
		if (button == Gosu::KB_SPACE) {
			if (aktiverSpielstein.platzieren(spielfeld)) {
				unsigned int y = aktiverSpielstein.get_y();
				unsigned int x = aktiverSpielstein.get_x();
				//unsigned int s = 0;
				//unsigned int z = 0;
				unsigned int reihen = 0;
				auto zustand = spielfeld.get_zustand();
				for (int i = y; i < (y + 4); i++) {//Darf nich fuer Bereiche ausserhalb des Spielfelds ausgefuehrt werden
					if (aktiverSpielstein.zeileBelegt(i-y)) {
						bool kompletteReihe = true;
						for (unsigned int j = 0; j < SPIELFELD_BREITE; j++) {
							if (!zustand.at(i).at(j).status) {
								kompletteReihe = false;
								break;
							}
						}
						if (kompletteReihe) {
							reihen = reihen + 1;
							for (unsigned int k = 0; k < SPIELFELD_BREITE; k++) {
								spielfeld.loescheAbschnitt(i, k);
							}
						}
					}
				}
				for (int i = x; i < (x + 4); i++) {//Darf nich fuer Bereiche ausserhalb des Spielfelds ausgefuehrt werden
					if (aktiverSpielstein.spalteBelegt(i-x)) {
						bool kompletteReihe = true;
						for (unsigned int j = 0; j < SPIELFELD_BREITE; j++) {
							if (!zustand.at(j).at(i).status) {
								kompletteReihe = false;
								break;
							}
						}
						if (kompletteReihe) {
							reihen = reihen + 1;
							for (unsigned int k = 0; k < SPIELFELD_BREITE; k++) {
								spielfeld.loescheAbschnitt(k, i);
							}
						}
					}
					

				}
				if (reihen > 0) {//score berrechnen
					spielfeld.addZuScore(std::powl(2, reihen) * 50);
				}
				aktiverSpielstein.neu();
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
