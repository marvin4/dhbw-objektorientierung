#pragma once
#include "Klassen.h"

enum Status
{
	inaktiv,einstellungen,spielende
};

	

class Menue
{
	int windowHoehe;
	int windowBreite;
	Status status;

public:
	Status get_status();
	bool set_windowSize(unsigned int maxHoehe, unsigned int maxBreite, unsigned int hoehe = 600, unsigned int breite = 800);
	Menue();
};

