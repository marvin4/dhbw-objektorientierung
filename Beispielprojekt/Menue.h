#pragma once

enum Status
{
	inaktiv,einstellungen,spielende
};
class Menue
{
	int windowHoehe;
	int windowBreite;

public:
	Status get_status();
	bool set_windowHoehe();
	bool set_windowBreite();
	Menue();
	~Menue();
};

