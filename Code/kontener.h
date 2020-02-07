#ifndef KONTENER_H
#define KONTENER_H

class Kontener {
	private:
		int dlugosc; // dlugosc kontenera
		int szerokosc; // szerokosc kontenera
		int wysokosc; // wysokosc kontenera
	public:
		Kontener(); // konstruktor bezparametryczny
		Kontener(int dlugosc, int szerokosc, int wysokosc); // kontruktor parametryczny
		int zwrocDl(); // zwraca dlugosc kontenera
		int zwrocSzer(); // zwraca szerokosc kontenera
		int zwrocWys(); // zwraca wysokosc kontenera
		~Kontener(); // destruktor
};

#endif