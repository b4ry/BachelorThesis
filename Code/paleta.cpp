#include "paleta.h"

/***************************************************************************************************************************************/
/* konstruktor bezparametryczny do tworzenia palety domyslnej */
Paleta::Paleta() {
	this->dlugosc = 10;
	this->szerokosc = 10;
	this->dziura = new Dziura(); // tworzenie dziury
	this->powierzchnia = dlugosc*szerokosc; 
	this->pow_zaj = 0;

	// dynamiczna alokacja tablicy dwuwymiarowej
	this->paleta_tab = new int *[dlugosc];
	for(int i = 0; i < dlugosc; i++)
		paleta_tab[i] = new int[szerokosc];
	// zerowanie tablicy
	for(int i = 0; i < dlugosc; i++) {
		for(int j = 0; j < szerokosc; j++)
			paleta_tab[i][j] = 0;
	}
}
/***************************************************************************************************************************************/
/* konstruktor parametryczny dla palety zdefiniowanej przez uzytkownika */
Paleta::Paleta(int dlugosc, int szerokosc, int liczba_palet) {
	this->dlugosc = dlugosc;
	this->szerokosc = szerokosc;
	this->liczba_palet = liczba_palet;
	this->dziura = new Dziura(); // tworzenie dziury
	this->powierzchnia = dlugosc*szerokosc; 
	this->pow_zaj = 0;

	// dynamiczna alokacja tablicy dwuwymiarowej
	this->paleta_tab = new int *[dlugosc];

	for(int i = 0; i < dlugosc; i++)
		paleta_tab[i] = new int[szerokosc];

	// zerowanie tablicy
	for(int i = 0; i < dlugosc; i++) {
		for(int j = 0; j < szerokosc; j++)
			paleta_tab[i][j] = 0;
	}
}
/***************************************************************************************************************************************/
/* zwraca dlugosc palety */
int Paleta::zwrocDl() {
	return this->dlugosc;
}
/***************************************************************************************************************************************/
/*zwraca szerokosc palety */
int Paleta::zwrocSzer() {
	return this->szerokosc;
}
/***************************************************************************************************************************************/
int Paleta::zwrocIloscPaczek() {
	return paczki_na_palecie.size();
}
/***************************************************************************************************************************************/
double Paleta::zwrocPow() {
	return this->powierzchnia;
}
/***************************************************************************************************************************************/
double Paleta::zwrocZajPow() {
	return this->pow_zaj;
}
/***************************************************************************************************************************************/
bool Paleta::czyPaletaPelna() {
	int licznik = 0;

	for(int i = 0; i < dlugosc; i++) {
		for(int j = 0; j < szerokosc; j++) {
			if(paleta_tab[i][j] == 0) // jesli pojawia sie jakies puste miejsce na palecie
				++licznik;
		}
	}
	if(licznik > 0) // jesli liczba pustych miejsc wieksza od 0, tzn, ze paleta nie jest pelna
		return false;
	else
		return true;
}
/***************************************************************************************************************************************/
bool Paleta::czyPaletaNiePelna() { // czy paleta nie pusta
	if(paczki_na_palecie.size() > 0) // jesli liczba paczek na palecie wieksza od 0, to paleta nie jest pusta
		return true;
}
/***************************************************************************************************************************************/
void Paleta::aktualizujZajPow(double pow) {
	this->pow_zaj += pow;
}
/***************************************************************************************************************************************/
void Paleta::operujDziury(std::list<Dziura> &l_dziur) {
	l_dziur.sort(sortujListeDziurD); // sortuje listy od najglebszej do najplytszej
	l_dziur.unique(wyrzucPlytsze); // wyrzuca plytsze dziury
	l_dziur.sort(sortujListeDziurL); // sortuje pozostale dziury po szerokosci
	l_dziur.unique(wyrzucWezsze); // wyrzuca wezsze dziury
}
/***************************************************************************************************************************************/
void Paleta::BestFit(std::list<Paczka> &l_paczek) {
	int licznik_pasujacych = 0; // liczba pasujacych paczek
	
	/* sprawdza, ktore paczki pasuja i ustala ich status */
	if(!l_paczek.empty()) {
		for(std::list<Paczka>::iterator iter = l_paczek.begin(); iter != l_paczek.end(); ++iter) {
			if(((iter->zwrocX() <= dziury.begin()->zwrocL()+1) && (iter->zwrocY() <= dziury.begin()->zwrocD()+1)) ||
				((iter->zwrocX() <= dziury.begin()->zwrocD()+1) && (iter->zwrocY() <= dziury.begin()->zwrocL()+1))) {
					iter->pasuje(); // paczka pasuje
					licznik_pasujacych++; // zwiekszamy licznik pasujacych
			}
		}
		obrocPaczkeNaPalecie(l_paczek); // obraca paczki dla dziury
		l_paczek.sort(sortujListePaczek); // sortuje po x
		l_paczek.sort(sortujListePaczekPasuja); // sortuje po pasowaniu
	}
	if(licznik_pasujacych == 0 && dziury.begin()->zwrocX() >= 0 && dziury.begin()->zwrocX() < szerokosc) { // wiadomo, co robi ten if (szukanie dziur niemozliwych do wypelnienia) - bloczki blokady
		// MOJ ALGORYTM, LEWA STRONA
		int y = dziury.begin()->zwrocY(); 
		int x = dziury.begin()->zwrocX()-1;
		int tmp1 = 0;
		int tmp2 = 0;

		while(paleta_tab[y][x] != 0) {
			--y;
			if(y < 0)
				break;
		}
		tmp1 = y;

		// PRAWA STRONA
		int koniec = dziury.begin()->zwrocX()+dziury.begin()->zwrocL()+1;
		for(int j = dziury.begin()->zwrocX(); j <= koniec ; j++) {
			if(j == koniec) {
				int y = dziury.begin()->zwrocY();
				int x = j;
				while(paleta_tab[y][x] != 0) {
					--y;
					if(y < 0)
						break;
				}
				tmp2 = y; 
			}
		}
		// JESLI NA POZIOMIE NIC NIE MA
		if((tmp2 == szerokosc-1 && dziury.begin()->zwrocX() == 0) ||
			(tmp2 <= szerokosc-1 && tmp1 < szerokosc-1 && dziury.begin()->zwrocX() == 0 && koniec == szerokosc)) {
			tmp1 = -1;
		}
		else if((tmp2 <= szerokosc-1 && dziury.begin()->zwrocX() == 0) || (koniec <= szerokosc-1 && dziury.begin()->zwrocX() == 0)) {
			tmp1 = tmp2;
		}
		else {
			tmp1 = tmp1 >= tmp2 ? tmp1 : tmp2; // wybiera glebsza czesc, aby ja wypelnic
		}

		for(int i = dziury.begin()->zwrocY(); i > tmp1; i--) { // wypelnia dziure bloczkami blokady
			for(int j = dziury.begin()->zwrocX(); j <= koniec-1; j++)
				paleta_tab[i][j] = 2;
		}
	}
	else if(licznik_pasujacych > 0) {
		/* jesli lista nie jest pusta i sa paczki pasujace, to wrzuca je na palete */
		if(!l_paczek.empty() && (l_paczek.begin()->zwrocStatus() == false)) { 
			for(int i = dziury.begin()->zwrocY(); i > dziury.begin()->zwrocY()-l_paczek.begin()->zwrocY(); --i) {
				for(int j = dziury.begin()->zwrocX(); j <= (dziury.begin()->zwrocX()+l_paczek.begin()->zwrocX())-1; ++j) {
					paleta_tab[i][j] = l_paczek.begin()->zwrocNumer(); // wklada paczke
				}
			}

			aktualizujZajPow(l_paczek.begin()->zwrocPow()); // aktualizuje zajeta pow palety o pow paczki
			l_paczek.begin()->zmienStatus(); // zmienia status paczki na umieszczona na palecie
			paczki_na_palecie.push_front(*l_paczek.begin()); // przerzuca paczke do paczek ulozonych na palecie
			l_paczek.pop_front(); // usuwa uzyta paczke

			for(std::list<Paczka>::iterator iter = l_paczek.begin(); iter != l_paczek.end(); ++iter) { // zeruje "pasowanie"
				iter->niePasuje();
			}
		}
	}
	dziury.clear(); // czysci dziury 
}
/***************************************************************************************************************************************/
void Paleta::WorstFit(std::list<Paczka> &l_paczek) {
	int licznik_pasujacych = 0; // liczba pasujacych paczek
	
	/* sprawdza, ktore paczki pasuja i ustala ich status */
	if(!l_paczek.empty()) {
		for(std::list<Paczka>::iterator iter = l_paczek.begin(); iter != l_paczek.end(); ++iter) {
			if(((iter->zwrocX() <= dziury.begin()->zwrocL()+1) && (iter->zwrocY() <= dziury.begin()->zwrocD()+1)) ||
				((iter->zwrocX() <= dziury.begin()->zwrocD()+1) && (iter->zwrocY() <= dziury.begin()->zwrocL()+1))) {
					iter->pasuje(); // paczka pasuje
					licznik_pasujacych++; // zwiekszamy licznik pasujacych
			}
		}
		obrocPaczkeNaPalecieWorst(l_paczek); // obraca paczki dla dziury
		l_paczek.sort(sortujListePaczek1); // sortuje po x
		obrocPaczkiDoPoczatkowej(l_paczek); // odwraca 
		obrocPaczkeNaPalecieWorst(l_paczek); // obraca paczki dla dziury
		l_paczek.sort(sortujListePaczekPasuja); // sortuje po pasowaniu
	}
	if(licznik_pasujacych == 0 && dziury.begin()->zwrocX() >= 0 && dziury.begin()->zwrocX() < szerokosc) { // wiadomo, co robi ten if (szukanie dziur niemozliwych do wypelnienia)
		// MOJ ALGORYTM, LEWA STRONA
		int y = dziury.begin()->zwrocY(); 
		int x = dziury.begin()->zwrocX()-1;
		int tmp1 = 0;
		int tmp2 = 0;

		while(paleta_tab[y][x] != 0) {
			--y;
			if(y < 0)
				break;
		}
		tmp1 = y;

		// PRAWA STRONA
		int koniec = dziury.begin()->zwrocX()+dziury.begin()->zwrocL()+1;
		for(int j = dziury.begin()->zwrocX(); j <= koniec ; j++) {
			if(j == koniec) {
				int y = dziury.begin()->zwrocY();
				int x = j;
				while(paleta_tab[y][x] != 0) {
					--y;
					if(y < 0)
						break;
				}
				tmp2 = y; 
			}
		}

		// JESLI NA POZIOMIE NIC NIE MA
		if((tmp2 == szerokosc-1 && dziury.begin()->zwrocX() == 0) ||
			(tmp2 <= szerokosc-1 && tmp1 < szerokosc-1 && dziury.begin()->zwrocX() == 0 && koniec == szerokosc)) {
			tmp1 = -1;
		}
		else if((tmp2 <= szerokosc-1 && dziury.begin()->zwrocX() == 0) || (koniec <= szerokosc-1 && dziury.begin()->zwrocX() == 0)) {
			tmp1 = tmp2;
		}
		else {
			tmp1 = tmp1 >= tmp2 ? tmp1 : tmp2; // wybiera glebsza czesc, aby ja wypelnic
		}
		for(int i = dziury.begin()->zwrocY(); i > tmp1; i--) { // wypelnia dziure
			for(int j = dziury.begin()->zwrocX(); j <= koniec-1; j++)
				paleta_tab[i][j] = 2;
		}
	}
	else if(licznik_pasujacych > 0) {
		/* jesli lista nie jest pusta i sa paczki pasujace, to wrzuca je na palete */
		if(!l_paczek.empty() && (l_paczek.begin()->zwrocStatus() == false)) { 
			for(int i = dziury.begin()->zwrocY(); i > dziury.begin()->zwrocY()-l_paczek.begin()->zwrocY(); --i) {
				for(int j = dziury.begin()->zwrocX(); j <= (dziury.begin()->zwrocX()+l_paczek.begin()->zwrocX())-1; ++j) {
					paleta_tab[i][j] = l_paczek.begin()->zwrocNumer(); // wklada paczke
				}
			}
			aktualizujZajPow(l_paczek.begin()->zwrocPow()); // aktualizuje zajeta pow palety o pow paczki
			l_paczek.begin()->zmienStatus(); // zmienia status paczki na umieszczona na palecie
			paczki_na_palecie.push_front(*l_paczek.begin()); // przerzuca paczke do paczek ulozonych na palecie
			l_paczek.pop_front(); // usuwa uzyta paczke
			for(std::list<Paczka>::iterator iter = l_paczek.begin(); iter != l_paczek.end(); ++iter) { // zeruje "pasowanie"
				iter->niePasuje();
			}
		}
	}
	obrocPaczkiDoPoczatkowej(l_paczek);
	dziury.clear(); // czysci dziury 
}
/***************************************************************************************************************************************/
void Paleta::FirstFit(std::list<Paczka> &l_paczek) {
	int licznik_pasujacych = 0; // liczba pasujacych paczek

	/* sprawdza, ktore paczki pasuja i ustala ich status */
	if(!l_paczek.empty()) {
		for(std::list<Paczka>::iterator iter = l_paczek.begin(); iter != l_paczek.end(); ++iter) {
			if(((iter->zwrocX() <= dziury.begin()->zwrocL()+1) && (iter->zwrocY() <= dziury.begin()->zwrocD()+1)) ||
				((iter->zwrocX() <= dziury.begin()->zwrocD()+1) && (iter->zwrocY() <= dziury.begin()->zwrocL()+1))) {
					iter->pasuje(); // paczka pasuje
					licznik_pasujacych++; // zwiekszamy licznik pasujacych
					if(((iter->zwrocX() <= dziury.begin()->zwrocL()+1) && (iter->zwrocY() <= dziury.begin()->zwrocD()+1)))
						break;
					else if(((iter->zwrocX() <= dziury.begin()->zwrocD()+1) && (iter->zwrocY() <= dziury.begin()->zwrocL()+1))) {
						obrocPaczkeNaPalecie(l_paczek); // obraca paczki dla dziury
					}
					break;
			}
		}
		l_paczek.sort(sortujListePaczekPasuja); // sortuje po pasowaniu
	}

	if(licznik_pasujacych == 0 && dziury.begin()->zwrocX() >= 0 && dziury.begin()->zwrocX() < szerokosc) { // wiadomo, co robi ten if (szukanie dziur niemozliwych do wypelnienia)
		// MOJ ALGORYTM, LEWA STRONA
		int y = dziury.begin()->zwrocY(); 
		int x = dziury.begin()->zwrocX()-1;
		int tmp1 = 0;
		int tmp2 = 0;
		while(paleta_tab[y][x] != 0) {
			--y;
			if(y < 0)
				break;
		}
		tmp1 = y;

		// PRAWA STRONA
		int koniec = dziury.begin()->zwrocX()+dziury.begin()->zwrocL()+1;
		for(int j = dziury.begin()->zwrocX(); j <= koniec ; j++) {
			if(j == koniec) {
				int y = dziury.begin()->zwrocY();
				int x = j;
				while(paleta_tab[y][x] != 0) {
					--y;
					if(y < 0)
						break;
				}
				tmp2 = y; 
			}
		}

		// JESLI NA POZIOMIE NIC NIE MA
		if((tmp2 == szerokosc-1 && dziury.begin()->zwrocX() == 0) ||
			(tmp2 <= szerokosc-1 && tmp1 < szerokosc-1 && dziury.begin()->zwrocX() == 0 && koniec == szerokosc)) {
			tmp1 = -1;
		}
		else if((tmp2 <= szerokosc-1 && dziury.begin()->zwrocX() == 0) || (koniec <= szerokosc-1 && dziury.begin()->zwrocX() == 0)) {
			tmp1 = tmp2;
		}
		else {
			tmp1 = tmp1 >= tmp2 ? tmp1 : tmp2; // wybiera glebsza czesc, aby ja wypelnic
		}
		for(int i = dziury.begin()->zwrocY(); i > tmp1; i--) { // wypelnia dziure bloczkami blokady
			for(int j = dziury.begin()->zwrocX(); j <= koniec-1; j++)
				paleta_tab[i][j] = 2;
		}
	}
	else if(licznik_pasujacych > 0) {
		/* jesli lista nie jest pusta i sa paczki pasujace, to wrzuca je na palete */
		if(!l_paczek.empty() && (l_paczek.begin()->zwrocStatus() == false)) { 
			for(int i = dziury.begin()->zwrocY(); i > dziury.begin()->zwrocY()-l_paczek.begin()->zwrocY(); --i) {
				for(int j = dziury.begin()->zwrocX(); j <= (dziury.begin()->zwrocX()+l_paczek.begin()->zwrocX())-1; ++j) {
					paleta_tab[i][j] = l_paczek.begin()->zwrocNumer(); // wklada paczke
				}
			}
			aktualizujZajPow(l_paczek.begin()->zwrocPow()); // aktualizuje zajeta pow palety o pow paczki
			l_paczek.begin()->zmienStatus(); // zmienia status paczki na umieszczona na palecie
			paczki_na_palecie.push_front(*l_paczek.begin()); // przerzuca paczke do paczek ulozonych na palecie
			l_paczek.pop_front(); // usuwa uzyta paczke

			for(std::list<Paczka>::iterator iter = l_paczek.begin(); iter != l_paczek.end(); ++iter) { // zeruje "pasowanie"
				iter->niePasuje();
			}
		}
	}
	dziury.clear(); // czysci dziury 
}
/***************************************************************************************************************************************/
void Paleta::wyswietlPalete(std::fstream &plik1, double &suma) {
	plik1 << std::endl;
	int pow_bloczki = 0;

	for(int i = 0; i < this->dlugosc; i++) { // zapisuje do pliku polozenie paczek na palecie
		for(int j = 0; j < this->szerokosc ; j++) {
			plik1 << static_cast<char>(paleta_tab[i][j]+64) << " ";

			if(paleta_tab[i][j] == 2) // jesli znalazl bloczek blokady
				++pow_bloczki;
		}
		plik1 << std::endl;
	}
	plik1 << std::endl;
	plik1 << "Zajeta powierzchnia przez bloczki blokady: " << pow_bloczki/zwrocPow()*100 << "%\n" << std::endl;
	suma += pow_bloczki/zwrocPow()*100; // zwieksz zajetosc pow przez bloczki blokady
}
/***************************************************************************************************************************************/
void Paleta::obrocPaczkeNaPalecie(std::list<Paczka> &l_paczek) {
	/* obracanie paczek */
	for(std::list<Paczka>::iterator iter = l_paczek.begin(); iter != l_paczek.end(); ++iter) {
		if(iter->zwrocPasuje() == true) { // obraca tylko te, co pasuja do dziury
			int tmp1 = dziury.begin()->zwrocL()+1 - iter->zwrocX();
			int tmp2 = dziury.begin()->zwrocL()+1 - iter->zwrocY();
			int roznica;
		
			if(tmp1 <= tmp2 && tmp1 <= dziury.begin()->zwrocL()+1) {
				if(tmp1 < 0 && tmp2 >= 0) { // jesli y lepszy od x, to obracamy
					roznica = tmp2; 
					iter->ustawObrot();
				}
				else
					roznica = tmp1;
			}
			else if(tmp1 > tmp2 && tmp2 <= dziury.begin()->zwrocL()+1) {
				if(tmp2 < 0) 
					roznica = tmp1;
				else { // jesli y lepszy od x, to obracamy
					roznica = tmp2;
					iter->ustawObrot();
				}
			}
		}
	}
}
/***************************************************************************************************************************************/
void Paleta::obrocPaczkeNaPalecieWorst(std::list<Paczka> &l_paczek) {
	/* obracanie paczek */
	for(std::list<Paczka>::iterator iter = l_paczek.begin(); iter != l_paczek.end(); ++iter) {
		if(iter->zwrocPasuje() == true) { // obraca tylko te, co pasuja do dziury
			int tmp1 = dziury.begin()->zwrocL()+1 - iter->zwrocX();
			int tmp2 = dziury.begin()->zwrocL()+1 - iter->zwrocY();
			
			if(tmp2 >= tmp1 && tmp2 >= 0 && iter->zwrocX() <= dziury.begin()->zwrocD()+1) // jesli y mniejszy od x i x mniejszy od glebokosci dziury to obroc paczke
				iter->ustawObrot();
			else if(iter->zwrocY() > dziury.begin()->zwrocD()+1) // jesli y wiekszy od glebokosci, to obroc paczke
				iter->ustawObrot();
		}
	}
}
/***************************************************************************************************************************************/
void Paleta::obrocPaczkiDoPoczatkowej(std::list<Paczka> &l_paczek) {
	for(std::list<Paczka>::iterator iter = l_paczek.begin(); iter != l_paczek.end(); ++iter) {
		if(iter->zwrocObrot() == true) { // obraca tylko te, co byly juz obrocone
			iter->ustawObrot();
		}
	}
}
/***************************************************************************************************************************************/
void Paleta::wyswietlInfoPaleta(std::list<Paczka> &l_paczek, std::fstream &plik1, double &suma, int &suma1) {
	plik1 << "Zajeta pow: " << (zwrocZajPow()/zwrocPow())*100 << "%." << std::endl;
	plik1 << "Ilosc pozostalych paczek: " << l_paczek.size() << std::endl;
	plik1 << "Ilosc paczek umieszczonych na palecie: " << zwrocIloscPaczek() << std::endl;
	suma = suma + (zwrocZajPow()/zwrocPow())*100;
	suma1 = suma1 + zwrocIloscPaczek();
}
/***************************************************************************************************************************************/
void Paleta::szukajDziury1() {
	int tmp_l = 0;
	int x = 0;
	bool flaga1 = false;
	bool flaga = false;

	for(int i = dlugosc-1; i >= 0; i--) { // od dolu do gory
		for(int j = 0; j < szerokosc; j++) {
			if(paleta_tab[i][j] == 0) {
				flaga = true;
				++tmp_l;
				if(flaga1 == false) { // jesli wchodzi na pole, gdzie jest 0, pierwszy raz badz wraca z pola z paczka
					x = j;
					flaga1 = true;
				}
				if(j == szerokosc - 1) { // koniec palety
					flaga1 = false;
					Dziura *dziura_tmp = new Dziura(i, tmp_l-1, x, i); // inicjacja dziury wrzucanej do listy
					dziury.push_back(*dziura_tmp); // wrzucenie dziury do listy
				}
			}
			else if(paleta_tab[i][j] != 0 && flaga == true) { // wchodzi na pole z paczka i wrzuca paczke do listy
				flaga1 = false;
				Dziura *dziura_tmp = new Dziura(i, tmp_l-1, x, i); // inicjacja dziury wrzucanej do listy
				dziury.push_back(*dziura_tmp); // wrzucenie dziury do listy
				flaga = false;
				tmp_l = 0;
			}
		}
	}
	operujDziury(dziury);
}
/***************************************************************************************************************************************/