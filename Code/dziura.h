#ifndef DZIURA_H
#define DZIURA_H
#include "punkt.h"

class Dziura {
	private:
		int d; // glebokosc dziury
		int l; // szerokosc dziury
		Punkt *punkt; // wspolrzedne dziury

	public:
		Dziura(); // konstruktor domyslny 
		Dziura(int d, int l, int x, int y); // konstruktor parametryczny dziur
		void ustawD(int d); // ustawia glebokosc dziury
		void ustawL(int l); // ustawia szerokosc dziury
		void modyfikujPkt(int x, int y); // modyfikuje wsp dziury
		int zwrocD(); // pobiera glebokosc dziury
		int zwrocL(); // pobiera szerokosc dziury
		int zwrocX(); // zwraca wsp x dziury
		int zwrocY(); // zwraca wsp y dziury
};
bool sortujListeDziurD(Dziura &dziura1, Dziura &dziura2); // sortuje dziury od najwiekszej do najmniejszej
bool sortujListeDziurL(Dziura &dziura1, Dziura &dziura2); // sortuje dziury po szerokosci
bool wyrzucPlytsze(Dziura &dziura1, Dziura &dziura2); // wyrzuca dziury plytsze
bool wyrzucWezsze(Dziura &dziura1, Dziura &dziura2); // wyrzuca dziury wezsze

#endif
