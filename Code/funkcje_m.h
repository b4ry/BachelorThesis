#ifndef FUNKCJE_M_H
#define FUNKCJE_M_H
#include "paleta.h"
#include "paczka.h"
#include <fstream>
#include <list>
#include <string>
#include <sstream> // istringstream

extern bool bestfit; // flaga do bestfit - uzywana przy porownywaniu wynikow
extern bool worstfit; // flaga do worstfit - uzywana przy porownywaniu wynikow
extern bool nextfit; // flaga do nextfit - uzywana przy porownywaniu wynikow

int menu(Paleta *paleta, std::fstream &plik, std::fstream &plik1, std::fstream &plik2, std::fstream &plik3, std::fstream &plik4, 
		 std::fstream &plik5, std::fstream &plik6, std::list<Paczka> &paczki, std::list<Paleta> &palety); // funkcja wyswietlajaca menu
int pobieranie_paczek(std::fstream &plik, std::list<Paczka> &paczki, int szerokosc, int dlugosc); // funkcja pobierajaca paczki
int pobieranie_palet(std::fstream &plik, int &_dlugosc, int &_szerokosc, int &_liczba_palet); // funkcja pobierajaca parametry palet
int funkcja_alg(int &_dlugosc, int &_szerokosc, int &_liczba_palet, int nr_algorytmu, std::fstream &plik, std::fstream &plik1,
				std::list<Paczka> &paczki, Paleta *paleta, std::list<Paleta> &palety); // funkcja wykonujaca dany algorytm + rzeczy niezbedne do dzialania algorytmu
int porownanie_wynikow(std::fstream &plik, int &_liczba_palet); // funkcja porownujaca wyniki
void doPalet(int &dana, std::string lancuch, std::fstream &plik); // funkcja sprawdzajaca poprawnosc danych wejsciowych w pliku palety.txt
void doPaczek(int &dana, std::string lancuch, std::fstream &plik); // funkcja sprawdzajaca poprawnosc danych wejsciowych w pliku paczki.txt

#endif