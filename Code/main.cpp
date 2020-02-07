#include "naglowki.h"

int main() {

	Paleta *paleta = NULL; // zmienna paleta
	std::list<Paczka> lista_paczek; // lista paczek
	std::list<Paleta> lista_palet; // lista palet
	std::fstream plik("paczki.txt", std::ios::in); // zmienna plik do czytania
	std::fstream plik1("wynik_bestfit.txt", std::ios::out); // zmienna plik do zapisywania wynikow algorytmu Best Fit
	std::fstream plik2("wynik_worstfit.txt", std::ios::out); // zmienna plik do zapisywania wynikow algorytmu Worst Fit
	std::fstream plik5("wynik_firstfit.txt", std::ios::out); // zmienna plik do zapisywania wynikow algorytmu Next Fit
	std::fstream plik3("wyniki.txt", std::ios::out); // plik, w ktorym przechowywane sa wyniki algorytmow
	std::fstream plik4("wyniki.txt", std::ios::in); // wyniki do czytania
	std::fstream plik6("palety.txt", std::ios::in); // plik do wczytywania parametrow palety

	// menu
	menu(paleta, plik, plik1, plik2, plik3, plik4, plik5, plik6, lista_paczek, lista_palet);

	system("pause");
	return 0;
}