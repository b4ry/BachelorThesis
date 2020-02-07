#include "funkcje_m.h"
#include "algo.h"

/***************************************************************************************************************************************/
bool bestfit = false; // flaga do bestfit - uzywana przy porownywaniu wynikow
bool worstfit = false; // flaga do worstfit - uzywana przy porownywaniu wynikow
bool nextfit = false; // flaga do nextfit - uzywana przy porownywaniu wynikow
/***************************************************************************************************************************************/
/* funkcja wyswietlajaca menu */
int menu(Paleta *paleta, std::fstream &plik, std::fstream &plik1, std::fstream &plik2, std::fstream &plik3, std::fstream &plik4, 
		 std::fstream &plik5, std::fstream &plik6, std::list<Paczka> &paczki, std::list<Paleta> &palety) {
	int _dlugosc = 0; // zmienna dlugosc dla palety
	int _szerokosc = 0; // zmienna szerokosc dla palety
	int _liczba_palet = 0; // zmienna liczba palet
	char wybor = 0; // zmienna wybor do menu

	do {
		std::cout << "			MENU " << std::endl;
		std::cout << "Prosze podac jedna z opcji." << std::endl;
		std::cout << "1. Pobierz palety z pliku." << std::endl; 
		std::cout << "2. Pobierz paczki z pliku." << std::endl; 
		std::cout << "3. Algorytm Best Fit." << std::endl; 
		std::cout << "4. Algorytm Worst Fit." << std::endl; 
		std::cout << "5. Algorytm First Fit." << std::endl;
		std::cout << "6. Porownanie wynikow." << std::endl;
		std::cout << "7. Wyjscie.\n" << std::endl;
		std::cout << "Wybor: ";
		std::cin >> wybor;
		switch(wybor) {
			case '1': // pobieranie palet z pliku
					system("cls");
					pobieranie_palet(plik6, _dlugosc, _szerokosc, _liczba_palet); 
					break;
			case '2': system("cls"); // pobieranie paczek z pliku
					pobieranie_paczek(plik, paczki, _szerokosc, _dlugosc);
					break;
			case '3': system("cls"); // wywolanie algorytmu Best Fit
					std::cout << "Wykonuje algorytm Best Fit." << std::endl;
					funkcja_alg(_dlugosc, _szerokosc, _liczba_palet, 0, plik1, plik3, paczki, paleta, palety);
					break;
			case '4': system("cls"); // wywolanie algorytmu Worst Fit
					std::cout << "Wykonuje algorytm Worst Fit." << std::endl;
					funkcja_alg(_dlugosc, _szerokosc, _liczba_palet, 1, plik2, plik3, paczki, paleta, palety);
					break;
			case '5': system("cls"); // wywolanie algorytmu First Fit
					std::cout << "Wykonuje algorytm First Fit." << std::endl;
					funkcja_alg(_dlugosc, _szerokosc, _liczba_palet, 2, plik5, plik3, paczki, paleta, palety);
					break;
			case '6': system("cls"); // porownanie otrzymanych wynikow
					std::cout << "Porownuje wyniki." << std::endl;
					porownanie_wynikow(plik4, _liczba_palet);
					break;
			case '7': std::cout << "Zakonczenie programu." << std::endl; // zakonczenie programu i zamkniecie plikow
					plik.close();
					plik3.close();
					return 0;
			// podanie opcji nie z menu czysci ekran
			default: system("cls");
					 break;
		}
	}while(wybor != '7'); // dopoki nie wybrano wyjscia - dzialaj
}
/***************************************************************************************************************************************/
int pobieranie_palet(std::fstream &plik, int &_dlugosc, int &_szerokosc, int &_liczba_palet) {
	int tmp_x, tmp_y, tmp_l, licznik; // tmp_l - liczba palet
	std::string tmp_xx, tmp_yy, tmp_ll; // wylapuja znaki 

	if(plik.is_open()) {
		licznik = 0;
		while(!plik.eof()) {
			std::cout << "Wczytywanie parametrow palety." << std::endl;

			// wczytuje wsp x palety
			doPalet(tmp_x, tmp_xx, plik);
			if(tmp_x <= 0) {
				std::cout << "Blad. Paleta nie moze miec rozmiaru mniejszego badz rownego zero." << std::endl;
				system("pause");
				return 1;
			}
			else {
				_szerokosc = tmp_x;
				licznik++;
			}
			// wczytuje wsp y palety
			doPalet(tmp_y, tmp_yy, plik);
			if(tmp_y <= 0) {
				std::cout << "Blad. Paleta nie moze miec rozmiaru mniejszego badz rownego zero." << std::endl;
				system("pause");
				return 1;
			}
			else {
				_dlugosc = tmp_y;
				licznik++;
			}
			// wczytuje liczbe palet
			doPalet(tmp_l, tmp_ll, plik);
			if(tmp_l <= 0) {
				std::cout << "Blad. Liczba palet nie moze byc mniejsza badz rowna zero." << std::endl;
				system("pause");
				return 1;
			}
			else {
				_liczba_palet = tmp_l;
				licznik++;
			}
			if(licznik == 3) { // jesli poprawnie wczytano wszystkie parametry
				std::cout << "Wczytano parametry palet:" << std::endl;
				std::cout << "Szerokosc: " << _szerokosc << std::endl;
				std::cout << "Dlugosc: " << _dlugosc << std::endl;
				std::cout << "Liczba palet: " << _liczba_palet << std::endl;
				break;
			}
		}
	}
	else {
		perror("Nie mozna otworzyc pliku.");
		system("pause");
		return 1;
	}
}
/***************************************************************************************************************************************/
/* funkcja pobierajaca paczki */
int pobieranie_paczek(std::fstream &plik, std::list<Paczka> &paczki, int szerokosc, int dlugosc) {
	if(szerokosc == 0 || dlugosc == 0) { // jesli nie pobrano palet
		std::cout << "Prosze najpierw pobrac palety." << std::endl;
	}
	else {
		int tmp_x, tmp_y, tmp_l; // zmienne do wczytywania z pliku
		int licznik = 0; // licznik do wyswietlania grafiki
		int _licznik = 0; // licznik do wczytywania
		int licznik_wp = 0; // liczba poprawnie wczytanych paczek
		std::string tmp_xx, tmp_yy, tmp_ll; // przechowuje liczbe i sprawdza ,czy jest liczba
	
		if(plik.is_open()) {
			plik.seekg(0, std::ios::beg); // wraca na poczatek pliku, dzieki czemu kolejny algo moze pobrac paczki

			int numer = 0; // zmienna pomocnicza do numerow paczek

			if(!plik.eof()) { // pobiera liczbe paczek
				doPaczek(tmp_l, tmp_ll, plik);
			}
			while(!plik.eof()) { // kazda iteracja petli czyta nowy wiersz, wrzucanie paczek do listy
				std::cout << "Wczytywanie paczek." << std::endl;

				Paczka *paczka = NULL; // tworzenei paczki

				/* pobiera wsp x i y paczek */
				doPaczek(tmp_x, tmp_xx, plik);
				doPaczek(tmp_y, tmp_yy, plik);

				if((tmp_x <= 0 || tmp_x > szerokosc || tmp_x > dlugosc) || (tmp_y <= 0 || tmp_y > szerokosc || tmp_y > dlugosc)) { // jesli pobrane rozmiary paczki przekraczaja rozmiary palety
					std::cout << "Paczka o wymiarach " << tmp_x << "x" << tmp_y << " przekracza rozmiary palety. Paczka odrzucona" <<
						std::endl;
					system("pause");
					tmp_l--; // zmniejsz liczbe paczek do pobrania
				}
				else { // jesli rozmiary sie zgadzaja, to
					++numer; // zwieksza numer paczki
					if(numer == 2)
						++numer; // zwieksza numer paczki, jesli wynosi 2, bo dwa jest zarezerwowane dla miejsca pustego nieuzywanego (bloczkow blokady)
					
					paczka = new Paczka(tmp_x, tmp_y, numer); // tworzy paczke
					paczki.push_back(*paczka); // wrzuca paczke do listy
					licznik_wp++; // zwieksza licznik pobranych paczek

					/* animacja wiatraczka */
					switch(licznik) { 
						case 0: std::cout << "|" << std::endl;
								break;
						case 1:	std::cout << "/" << std::endl;
								break;
						case 2: std::cout << "--" << std::endl;
								break;
						case 3:	std::cout << "\\" << std::endl;
								break;
					}
					licznik++;
					if(licznik > 3)
						licznik = 0; // zerownanie, jesli wieksze od 3
					system("cls");
				}
				if(licznik_wp == tmp_l) // jesli liczba pobranych paczek jest rowna liczbie wymaganych paczek, to break (zapobiega pobieraniu pustych wierszy z konca pliku)
					break;
			}
			std::cout << "Wczytano " << paczki.size() << " paczek." << std::endl;
		}
		else {
			perror("Nie mozna otworzyc pliku badz paczki zostaly wczytane.");
			system("pause");
			return 1;
		}
		plik.close(); // zamyka plik paczki.txt
	}
}
/***************************************************************************************************************************************/
int funkcja_alg(int &_dlugosc, int &_szerokosc, int &_liczba_palet, int nr_algorytmu, std::fstream &plik, std::fstream &plik1, 
				std::list<Paczka> &paczki, Paleta *paleta, std::list<Paleta> &palety) {

	std::list<Paczka> paczki1 = paczki; // kopiuje liste paczek, zeby operowac na kopii (dzieki temu nie trzeba pobierac drugi raz paczek dla innego algorytmu)
	palety.clear(); // czysci palety (zapobiega wywalaniu sie programu)

	int suma_paczek = 0; // licznik do ilosci pobranych paczek przez algorytm
	bool limit = false; // jesli przekroczono podana liczbe palet, to liczy ile palet potrzeba do upakowania pozostalych

	if(_dlugosc <= 0 || _szerokosc <= 0) // jesli parametry palety sa niepoprawne
		std::cout << "Zdefiniuj palety. Pamietaj, ze parametry musza byc wieksze od 0." << std::endl;
	else {
		/*tworzy palete */
		paleta = new Paleta(_dlugosc, _szerokosc, _liczba_palet);

		if(paleta == NULL) { // jesli z jakiegos powodu nie udalo sie stworzyc palety
			std::cout << "Blad w tworzeniu palety." << std::endl;
			return 1;
		}
	}
	if(plik.is_open()) { // jesli plik otwarty
		double suma = 0; // zmienna wykorzystywana do zapisywania sumy zajetosci

		if(paczki1.size() == 0) // jesli nie pobrano paczek, to nalezy je pobrac
			std::cout << "Pobierz paczki." << std::endl;
		else { // jesli sa paczki, to lec dalej
			plik << "Liczba pobranych paczek: " << paczki1.size() << std::endl;
		
			while(paczki1.size() > 0) { // jesli wiecej paczek niz 0
				paleta->szukajDziury1(); // szuka dziury na palecie

				/* w zaleznosci od nr algorytmu wykonuje dany algorytm */
				if(nr_algorytmu == 0) 
					paleta->BestFit(paczki1);
				else if(nr_algorytmu == 1)
					paleta->WorstFit(paczki1);
				else if(nr_algorytmu == 2)
					paleta->FirstFit(paczki1);

				if(paleta->czyPaletaPelna() == true) { // jesli paleta pelna
					paleta->wyswietlInfoPaleta(paczki1, plik, suma, suma_paczek); // zapisz info o palecie do pliku
					paleta->wyswietlPalete(plik, suma); // zapisz ulozenei paczek do pliku
					palety.push_back(*paleta); // wrzuca palete do uzywanych

					if(palety.size() == _liczba_palet) // jesli wykorzystano dostepna liczbe palet
						limit = true;
					if(limit == true) { // wyswietl komentarz w pliku, kiedy liczysz ponad limit
						plik << "\n---------------- PONAD LIMIT ----------------\n" << std::endl;
						limit = false;
					}
					if(paczki1.size() > 0) { // jesli dalej sa paczki, tworz nowa palete
						paleta = new Paleta(_dlugosc, _szerokosc, _liczba_palet); // tworzy nowa palete 
						if(paleta == NULL) { // jesli nie udalo sie stworzyc palety
							std::cout << "Blad w tworzeniu palety." << std::endl;
							return 1;
						}
					}
				}
			}
			if(paleta->zwrocZajPow() != 0) { // jesli ostatnia paleta nie jest pusta, to ja wrzuc
				palety.push_back(*paleta); // wrzuca palete do uzywanych
				paleta->wyswietlInfoPaleta(paczki1, plik, suma, suma_paczek); // pozostale wyniki do pliku
				paleta->wyswietlPalete(plik, suma); // pozostale wyniki do pliku
			}
			
			std::cout << "Ilosc uzytych palet: " << palety.size() << std::endl;

			plik << "Ilosc uzytych palet: " << palety.size() << std::endl;

			/* jesli wykonuje sie dany algorytm, to wyswietl jego informacje */
			if(nr_algorytmu == 0) {
				std::cout << "\nWyniki zapisano do pliku \"wynik_bestfit.txt\".\n" << std::endl;
				bestfit = true; // wykonal sie bestfit
			}
			else if(nr_algorytmu == 1) {
				std::cout << "\nWyniki zapisano do pliku \"wynik_worstfit.txt\".\n" << std::endl;
				worstfit = true; // wykonal sie worstfit
			}
			else if(nr_algorytmu == 2) {
				std::cout << "\nWyniki zapisano do pliku \"wynik_firstfit.txt\".\n" << std::endl;
				nextfit = true;
			}

			plik1 << palety.size() << std::endl; // liczba uzytych palet

			if(palety.size() > 1) // jesli liczba palet wieksza niz 1
				plik1 << (suma/(palety.size()*paleta->zwrocPow()))*100 << std::endl; // zapelnione miejsce
			else
				plik1 << suma << std::endl;  // jesli liczba palet rowna 1, to wrzuc sume zajetej powierzchni

			plik1 << suma_paczek << std::endl; // suma paczek

			plik.close(); // zamknij plik algorytm_wynik.txt
		}
	}
	else {
		perror("Nie mozna otworzyc pliku.");
		system("pause");
		return 1;
	}
	return 0;
}
/***************************************************************************************************************************************/
int porownanie_wynikow(std::fstream &plik, int &_liczba_palet) {
	double tmplp, tmpzaj, tmppa; // pomocnicze (liczba palet, zajetosc, zaladowane paczki)

	/* obiekty algorytmow */
	Algo *algo_best = new Algo("best_fit");
	Algo *algo_worst = new Algo("worst_fit");
	Algo *algo_next = new Algo("first_fit");

	std::list<Algo> lista_algo; // lista przechowujca algorytmy

	if(bestfit == false || worstfit == false || nextfit == false) { // jesli ktorys z algorytmow nie zostal wykonany
		std::cout << "Prosze wykonac wszystkie algorytmy. Pozostale algorytmy do wykonania: " << std::endl;
		if(bestfit == false) 
			std::cout << "bestfit" << std::endl;
		if(worstfit == false)
			std::cout << "worstfit" << std::endl;
		if(nextfit == false)
			std::cout << "firstfit" << std::endl;
	}
	else {
		if(plik.is_open()) {
			plik.seekg(0, std::ios::beg); // wroc na poczatek pliku

			/* czytanie informacji z pliku i wrzucanie ich do odpowiednich struktur, a nastepnie wrzucenie tych struktur do listy */
			plik >> tmplp >> tmpzaj >> tmppa;
			algo_best->pobierzZawTab(tmplp, tmpzaj, tmppa);
			lista_algo.push_back(*algo_best);
			plik >> tmplp >> tmpzaj >> tmppa;
			algo_worst->pobierzZawTab(tmplp, tmpzaj, tmppa);
			lista_algo.push_back(*algo_worst);
			plik >> tmplp >> tmpzaj >> tmppa;
			algo_next->pobierzZawTab(tmplp, tmpzaj, tmppa);
			lista_algo.push_back(*algo_next);

			// porzadkowanie listy wynikow
			lista_algo.sort(sortujPoLiczbiePalet);
			lista_algo.unique(wyrzucWiecejPalet);
			lista_algo.sort(sortujPoPow);
			lista_algo.unique(wyrzucWiecejZajetosci);
			lista_algo.sort(sortujPoLiczbiePaczek);
			lista_algo.unique(wyrzucMniejPaczek);

			if(lista_algo.size() > 1) { // jesli liczba najlepszych algorytmow wieksza niz 1
				std::cout << "\nNajlepsze wyniki dla algorytmow: " << std::endl;
			}
			else { // jesli liczba najlepszych algorytmow rowna 1
				std::cout << "Najlepszy wynik dla algorytmu: " << std::endl;
			}
			for(std::list<Algo>::iterator iter = lista_algo.begin(); iter != lista_algo.end(); ++iter) { // wyswietla algorytmy po kolei
				std::cout << "\nNazwa: " << iter->zwrocNazwe() << std::endl;
				std::cout << "Liczba dostepnych palet: " << _liczba_palet << std::endl;
				std::cout << "Liczba wykorzystanych palet: " << iter->zwrocLP() << std::endl;
				std::cout << "Zajetosc powierzchni: " << iter->zwrocZaj() << "%" << std::endl;
				std::cout << "Liczba zapakowanych paczek: " << iter->zwrocPa() << std::endl;
			}
		}
		else {
			perror("Nie mozna otworzyc pliku.");
			system("pause");
			return 1;
		}
		std::cout << "\nKoniec programu." << std::endl;
		system("pause");
		exit(0);
	}
}
/***************************************************************************************************************************************/
void doPalet(int &dana, std::string lancuch, std::fstream &plik) {
	getline(plik, lancuch); // pobiera parametry z pliku palety.txt do lancucha
	// sprawdza czy liczba
	for(unsigned i = 0; i < lancuch.length(); i++) { // szuka znaku w lancuchu
		int licznik = 0;

		if(!isdigit(lancuch[i])) { // jesli znak w lancuchu
			std::cout << "\nWprowadzone dane niepoprawne. Prosze zmienic dane wejsciowe w pliku" << std::endl;
			std::cout << "\"palety.txt\".\n" << std::endl;
			system("pause");
			exit(1);
		}
		else { // jesli cyfra w lancuchu
			licznik++;
		}
		if(lancuch.length() >= 2) { // dla wiekszych niz jednocyfrowe
			if(licznik == lancuch.length()-1) {
				std::istringstream iss(lancuch); // konwersja string na int
				iss >> dana;
			}
		}
		else if(lancuch.length() < 2) { // dla jednocyfrowych
			if(licznik == lancuch.length()) {
				std::istringstream iss(lancuch); // konwersja string na int
				iss >> dana;
			}
		}
	}
}
/***************************************************************************************************************************************/
void doPaczek(int &dana, std::string lancuch, std::fstream &plik) {
	plik >> lancuch;
	// sprawdza czy liczba
	for(unsigned i = 0; i < lancuch.length(); i++) { // szuka znaku w lancuchu
		int licznik = 0;

		if(!isdigit(lancuch[i])) { // jesli znak w lancuchu
			std::cout << "\nWprowadzone dane niepoprawne. Prosze zmienic dane wejsciowe w pliku" << std::endl;
			std::cout << "\"palety.txt\".\n" << std::endl;
			system("pause");
			exit(1);
		}
		else { // jesli cyfra w lancuchu
			licznik++;
		}
		if(lancuch.length() >= 2) { // dla wiekszych niz jednocyfrowe
			if(licznik == lancuch.length()-1) {
				std::istringstream iss(lancuch); // konwersja string na int
				iss >> dana;
			}
		}
		else if(lancuch.length() < 2) { // dla jednocyfrowych
			if(licznik == lancuch.length()) {
				std::istringstream iss(lancuch); // konwersja string na int
				iss >> dana;
			}
		}
	}
}
/***************************************************************************************************************************************/
