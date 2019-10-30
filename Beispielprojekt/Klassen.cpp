#include "stdafx.h"
#include "Klassen.h"

class Spielfeld
{

	Gosu::Image bild;
	std::array<std::array<Feld, SPIELFELD_BREITE>, SPIELFELD_BREITE> zustand;
	int64_t score=0;

public:
	uint16_t hoehe() {
		return this->zustand.size();
	}
	void Spielreset() {
		for (std::array<Feld,SPIELFELD_BREITE>& zeile_ref : this->zustand) {
			for (Feld& elem_ref : zeile_ref) {
				elem_ref.status = 0;
			}
		}
		this->score = 0;
	}

};