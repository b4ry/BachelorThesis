#ifndef PUNKT_H
#define PUNKT_H
#include <iostream>

class Punkt {
	private:
		int x; // wspolrzedna x punkty
		int y; // wspolrzedna y punktu
		int z; // wspolrzedna z punktu
	public:
		Punkt(int x = 0, int y = 0); // konstruktor parametryczny 2D
		int pobierzX(); // pobiera wspolrzedna x
		int pobierzY(); // pobiera wspolrzedna y
		int pobierzZ();	// pobiera wspolrzedna z
		void ustawX(int x); // ustawia wspolrzedna x na konkretna wartosc, metoda wykorzystywana w aktualizacji wspolrzednych
		void ustawY(int y); // ustawia wspolrzedna y na konkretna wartosc, metoda wykorzystywana w aktualizacji wspolrzednych
		void ustawZ(int z); // ustawia wspolrzedna z na konkretna wartosc, metoda wykorzystywana w aktualizacji wspolrzednych
		int odlegoscPunktow2D(Punkt p); // oblicza odleglosc miedzy dwoma punktami
		friend std::ostream & operator<< (std::ostream &wyjscie, Punkt &p); // przeciazenie operatora << dla klasy Punkt
};

#endif