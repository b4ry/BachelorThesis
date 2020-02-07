#include "kontener.h"

/**************************************************/
Kontener::Kontener() {
	dlugosc = 100;
	szerokosc = 100;
	wysokosc = 100;
}
/**************************************************/
int Kontener::zwrocDl() {
	return dlugosc;
}
/**************************************************/
int Kontener::zwrocSzer() {
	return szerokosc;
}
/**************************************************/
int Kontener::zwrocWys() {
	return wysokosc;
}
/**************************************************/
Kontener::Kontener(int dlugosc, int szerokosc, int wysokosc) {
	this->dlugosc = dlugosc;
	this->szerokosc = szerokosc;
	this->wysokosc = wysokosc;
}
/**************************************************/
