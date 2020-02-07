#ifndef PALETA_H
#define PALETA_H
#include <iostream>
#include <list>
#include <fstream>
#include "dziura.h"
#include "paczka.h"

extern int _dlugosc;
extern int _szerokosc;

class Paleta {
	private:
		int dlugosc; // dlugosc palety
		int szerokosc; // szerokosc palety
		int liczba_palet; // liczba palet zdefiniowanych przez uzytkownika
		int **paleta_tab; // tablica rozlozenia paczek na palecie (0 - brak paczki w danym miejscu, 1 - paczka)
		double powierzchnia; // powierzchnia palety
		double pow_zaj; // zajeta powierzchnia palety przez paczki
		Dziura *dziura; // biezaca dziura
		std::list<Dziura> dziury; // lista dziur
		std::list<Paczka> paczki_na_palecie; // liczba paczek umieszczonych na palecie

	public:
		Paleta(); // konstruktor bezparametryczny
		Paleta(int dlugosc, int szerokosc, int liczba_palet); // kontruktor parametryczny
		int zwrocDl(); // zwraca dlugosc palety
		int zwrocSzer(); // zwraca szerokosc palety
		int zwrocIloscPaczek(); // zwraca ilosc paczek na palecie
		double zwrocPow(); // zwraca pow palety
		double zwrocZajPow(); // zwraca zajeta pow palety
		bool czyPaletaPelna(); // jesli paleta nie ma miejsca
		bool czyPaletaNiePelna(); // czy paleta pusta
		void aktualizujZajPow(double pow); // aktualizuje zajeta pow palety
		void szukajDziury1(); // szuka dziur w palecie
		void operujDziury(std::list<Dziura> &l_dziur); // przeprowadza operacje na dziurach, tj. wybiera te najlepsza
		void BestFit(std::list<Paczka> &l_paczek); // wykonuje algorytm Best Fit
		void WorstFit(std::list<Paczka> &l_paczek); // wykonuje algorytm Worst Fit
		void FirstFit(std::list<Paczka> &l_paczek); // wykonuje algorytm First Fit
		void wyswietlPalete(std::fstream &plik1, double &suma); // wyswietla palete
		void obrocPaczkeNaPalecie(std::list<Paczka> &l_paczek); // obraca paczke na palecie
		void obrocPaczkeNaPalecieWorst(std::list<Paczka> &l_paczek); // obraca paczke na palecie 
		void obrocPaczkiDoPoczatkowej(std::list<Paczka> &l_paczek); // obraca paczki do pozycji poczatkowej
		void wyswietlInfoPaleta(std::list<Paczka> &l_paczek, std::fstream &plik1, double &suma, int &suma1); // wyswietla informacje o zapelnieniu palety
		//~Paleta(); // destruktor
};


#endif