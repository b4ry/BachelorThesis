#include "ogolne_funkcje.h"

void menu(int wybor, int dlugosc, int szerokosc, Paleta paleta) {
	do {
			std::cout << "			MENU " << std::endl;
			std::cout << "Prosze podac jedna z opcji." << std::endl;
			std::cout << "1. Paleta domyslna o wymiarach 100x100.\n2. Paleta z parametrami zdefiniowanymi.\n";
			std::cout << "3. Wyjscie.\n" << std::endl;
			std::cout << "Wybor: ";
			std::cin >> wybor;
			switch(wybor) {
				case 1:	paleta = new Paleta();
						if(paleta != NULL)
							std::cout << "Utworzono palete domyslna o wymiarach 100x100." << std::endl;
						else {
							std::cout << "Blad w tworzeniu palety." << std::endl;
							return 1;
						}
						break; 
				case 2: std::cout << "Podaj dlugosc palety: " << std::endl;
						std::cin >> _dlugosc;
						std::cout << "Podaj szerokosc palety: " << std::endl;
						std::cin >> _szerokosc;
						paleta = new Paleta(_dlugosc, _szerokosc);
						if(paleta != NULL)
							std::cout << "Utworzono palete o wymiarach " << _dlugosc << "x" << _szerokosc << "." << std::endl;
						else {
							std::cout << "Blad w tworzeniu palety." << std::endl;
							return 1;
						}
						break;
				case 3: std::cout << "Zakonczenie programu." << std::endl;
						return 0;
				default: system("cls");
						break;
			}
		}while(wybor != 1 && wybor != 2 && wybor != 3);
}