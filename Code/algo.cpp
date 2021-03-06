#include "algo.h"

/***************************************************************************************************************************************/
Algo::Algo(std::string nazwa) {
	this->nazwa = nazwa;
	tab[0] = 0; // liczba palet
	tab[1] = 0; // zajetosc
	tab[2] = 0; // paczki
}
/***************************************************************************************************************************************/
std::string Algo::zwrocNazwe() {
	return this->nazwa;
}
/***************************************************************************************************************************************/
double Algo::zwrocLP() {
	return tab[0];
}
/***************************************************************************************************************************************/
double Algo::zwrocZaj() {
	return tab[1];
}
/***************************************************************************************************************************************/
double Algo::zwrocPa() {
	return tab[2];
}
/***************************************************************************************************************************************/
void Algo::zwrocZawTab() {
	std::cout << "Liczba palet: " << tab[0] << std::endl;
	std::cout << "Zajeta powierzchnia: " << tab[1] << "%" << std::endl;
}
/***************************************************************************************************************************************/
void Algo::pobierzZawTab(double lp, double zaj, double paczki) {
	this->tab[0] = lp;
	this->tab[1] = zaj;
	this->tab[2] = paczki;
}
/***************************************************************************************************************************************/
bool sortujPoLiczbiePalet(Algo &algo1, Algo &algo2){
	return algo1.zwrocLP() < algo2.zwrocLP();
}
/***************************************************************************************************************************************/
bool sortujPoLiczbiePaczek(Algo &algo1, Algo &algo2){
	return algo1.zwrocPa() > algo2.zwrocPa();
}
/***************************************************************************************************************************************/
bool sortujPoPow(Algo &algo1, Algo &algo2) {
	return algo1.zwrocZaj() < algo2.zwrocZaj();
}
/***************************************************************************************************************************************/
bool wyrzucWiecejPalet(Algo &algo1, Algo &algo2) {
	return algo1.zwrocLP() < algo2.zwrocLP();
}
/***************************************************************************************************************************************/
bool wyrzucWiecejZajetosci(Algo &algo1, Algo &algo2) {
	return algo1.zwrocZaj() < algo2.zwrocZaj();
}
/***************************************************************************************************************************************/
bool wyrzucMniejPaczek(Algo &algo1, Algo &algo2) {
	return algo1.zwrocPa() > algo2.zwrocPa();
}
/***************************************************************************************************************************************/