#include "paczka.h"

//***************************************************************************************************************************************/
Paczka::Paczka(int x, int y, int numer) {
	this->x = x;
	this->y = y;
	this->obrot = false;
	this->status = false;
	this->czyPasuje = false;
	this->powierzchnia = x*y;
	this->numer_paczki = numer;
}
/***************************************************************************************************************************************/
void Paczka::ustawX(int x) {
	this->x = x;
}
/***************************************************************************************************************************************/
void Paczka::ustawY(int y) {
	this->y = y;
}
/***************************************************************************************************************************************/
void Paczka::ustawObrot() {
	int tmp;

	if(obrot == false) {
		tmp = this->x;
		this->x = this->y;
		this->y = tmp;
		this->obrot = true;
	}
	else {
		tmp = this->y;
		this->y = this->x;
		this->x = tmp;
		this->obrot = false;
	}
}
/***************************************************************************************************************************************/
void Paczka::zmienStatus() {
	this->status = true;
}
/***************************************************************************************************************************************/
void Paczka::pasuje() {
	this->czyPasuje = true;
}
/***************************************************************************************************************************************/
void Paczka::niePasuje() {
	this->czyPasuje = false;
}
/***************************************************************************************************************************************/
int Paczka::zwrocX() {
	return this->x;
}
/***************************************************************************************************************************************/
double Paczka::zwrocPow() {
	return this->powierzchnia;
}
/***************************************************************************************************************************************/
int Paczka::zwrocY() {
	return this->y;
}
/***************************************************************************************************************************************/
int Paczka::zwrocNumer() {
	return this->numer_paczki;
}
/***************************************************************************************************************************************/
bool Paczka::zwrocObrot() {
	return this->obrot;
}
/***************************************************************************************************************************************/
bool Paczka::zwrocStatus() {
	return this->status;
}
/***************************************************************************************************************************************/
bool Paczka::zwrocPasuje() {
	return this->czyPasuje;
}
/***************************************************************************************************************************************/
bool sortujListePaczek(Paczka &paczka1, Paczka &paczka2) {
	return ((paczka1.zwrocX() > paczka2.zwrocX()));
}
/***************************************************************************************************************************************/
bool sortujListePaczek1(Paczka &paczka1, Paczka &paczka2) {
	int tmp_x = paczka1.zwrocX();
	int tmp_y = paczka1.zwrocY();
	int tmp_xx = paczka2.zwrocX();
	int tmp_yy = paczka2.zwrocY();

	if(tmp_y < tmp_x)
		paczka1.ustawObrot();
	if(tmp_yy < tmp_xx)
		paczka2.ustawObrot();

	return ((paczka1.zwrocX() < paczka2.zwrocX())); 
}
/***************************************************************************************************************************************/
bool sortujListePaczekPasuja(Paczka &paczka1, Paczka &paczka2) {
	return paczka1.zwrocPasuje() > paczka2.zwrocPasuje();
}
/***************************************************************************************************************************************/
bool wyrzucPaczkiNiePasujace(Paczka &paczka1, Paczka &paczka2) {
	return (paczka1.zwrocPasuje() == 0 || paczka2.zwrocPasuje() == 0);
}
/***************************************************************************************************************************************/