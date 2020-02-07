#ifndef PACZKA_H
#define PACZKA_H

class Paczka {
	private:
		int x; // szerokosc paczki
		int y; // dlugosc paczki
		int numer_paczki; // numer paczki
		double powierzchnia; // pow paczki
		bool obrot; // czy paczka obrocona
		bool status; // czy paczka umieszczona na palecie
		bool czyPasuje; // czy paczka pasuje do dziury

	public:
		Paczka(int x = 0, int y = 0, int numer = 0); // konstruktor parametryczny, domyslny
		int zwrocX(); // zwraca szerokosc paczki
		int zwrocY(); // zwraca dlugosc paczki
		int zwrocNumer(); // zwraca numer paczki
		double zwrocPow(); // zwraca pow
		void ustawX(int x); // ustawia szerokosc paczki na zadana wartosc
		void ustawY(int y); // ustawia dlugosc paczki na zadana wartosc
		void ustawObrot(); // obraca paczke o 90 stopni
		void zmienStatus(); // zmienia status paczki
		void pasuje(); // paczka pasuje do dziury
		void niePasuje(); // zmienia status "pasowania"
		bool zwrocObrot(); // zwraca obrot paczki
		bool zwrocStatus(); // zwraca status paczki
		bool zwrocPasuje(); // zwraca status "pasowania"
};
bool sortujListePaczek(Paczka &paczka1, Paczka &paczka2); // sortuje paczki w zaleznosci od dlugosci bokow (od najw do najm)
bool sortujListePaczek1(Paczka &paczka1, Paczka &paczka2); // sortuje paczki w zaleznosci od dlugosci bokow (od najm do najw)
bool sortujListePaczekPasuja(Paczka &paczka1, Paczka &paczka2); // sortuje paczki w zaleznosci od tego, czy pasuja do dziury
bool wyrzucPaczkiNiePasujace(Paczka &paczka1, Paczka &paczka2); // wywala paczki, ktore nie pasuja do dziury

#endif