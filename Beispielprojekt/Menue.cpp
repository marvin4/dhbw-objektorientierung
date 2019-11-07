#include "stdafx.h"
#include "Menue.h"


Status Menue::get_status()
{
	return Status();
}

bool Menue::set_windowSize(unsigned int maxHoehe,unsigned int maxBreite,unsigned int hoehe,unsigned int breite)
{
	int r = false;
	hoehe = Gosu::clamp(hoehe, unsigned int(0), maxHoehe);
	breite = Gosu::clamp(breite, unsigned int(0), maxBreite);
	if ((hoehe < breite)&&(breite-hoehe>160)&&(hoehe>100)) {
		r = true;
		
	}
	return r;
}

Menue::Menue()
{
	this->status = einstellungen;
	this->windowHoehe = 600;
	this->windowBreite = 800;
}
