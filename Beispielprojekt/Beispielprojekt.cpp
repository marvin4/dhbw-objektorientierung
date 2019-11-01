#include "stdafx.h"

#include <Gosu/Gosu.hpp>
#include <Gosu/AutoLink.hpp>

#include <vector>
#include <string>
#include <iostream>

#include "Vektor2d.h"
#include "Klassen.h"

// Simulationsgeschwindigkeit
const double DT = 100.0;

class GameWindow : public Gosu::Window
{
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
	uint16_t hoehePxlSpielfeld;
	uint16_t hoehePxlAbschnitt;
	Spielfeld spielfeld;
	AktiverSpielstein aktiverSpielstein;
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
			aktiverSpielstein.platzieren(spielfeld);
		}
		
	}
};

// C++ Hauptprogramm
int main()
{
	GameWindow window;
	window.show();
}
