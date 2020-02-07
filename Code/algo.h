#ifndef ALGO_H
#define ALGO_H
#include <string>
#include <iostream>

class Algo {
	private:
		std::string nazwa;
		double tab[3]; // zawiera liczbe paczek, palet oraz powierzchnie zajetosci
	public:
		Algo(std::string nazwa);
		std::string zwrocNazwe(); // zwraca nazwe algorytmu
		void zwrocZawTab(); //zwraca zawartosc tablicy
		double zwrocLP(); // zwraca liczbe palet
		double zwrocZaj(); // zwraca zajetosc
		double zwrocPa(); // zwraca paczki
		void pobierzZawTab(double lp, double zaj, double paczki); // pobiera wartosci i wpisuje je do tablicy
};
bool sortujPoLiczbiePalet(Algo &algo1, Algo &algo2); // sortuje po liczbie palet od najmniejszej do najw
bool sortujPoLiczbiePaczek(Algo &algo1, Algo &algo2); // sortuje po liczbie paczek od najw do najm
bool sortujPoPow(Algo &algo1, Algo &algo2); // sortuje po zaj pow od najmniejszej do najw
bool wyrzucWiecejPalet(Algo &algo1, Algo &algo2); // wyrzuca algo z wieksza liczba palet
bool wyrzucMniejPaczek(Algo &algo1, Algo &algo2); // wyrzuca algo z mniejsza liczba paczek
bool wyrzucWiecejZajetosci(Algo &algo1, Algo &algo2); // wyrzuca algo z wieksza zajetoscia palet

#endif