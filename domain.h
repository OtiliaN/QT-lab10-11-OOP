#pragma once
#include<string>
#include<iostream>
using std::string;
using std::cout;

class Oferta {
private:
	string denumire;
	string destinatie;
	string tip;
	float pret;

public:
	//Constructor implicit
	Oferta() : denumire { "" }, destinatie{ "" }, tip{ "" }, pret{ 0 } {};

	//constructorul ofertei
	Oferta( string denumire, string destinatie, string tip, float pret) : denumire { denumire }, destinatie{ destinatie }, tip{ tip }, pret{ pret } {}

	//Destructor
	~Oferta() = default;

	//Functie de copiere
	Oferta(const Oferta& copie) : denumire { copie.denumire }, destinatie{ copie.destinatie }, tip{ copie.tip }, pret{ copie.pret } {
		//cout << "Hi!\n";
	}
	////getters


	//Returneaza denumirea unei oferte
	string getDenumire() const;

	//Returneaza destinatia unei oferte
	string getDestinatie() const;

	//Returneaza tipul unei oferte
	string getTip() const;

	//Returneaza pretul unei oferte
	float getPret() const;


	////setters
	/*
	* Seteaza denumirea unei oferte.
	* @param: denumireNou - string, noua denumire
	*/
	void setDenumire(string denumireNou);

	/*
	* Seteaza destinatia unei oferte.
	* @param: destinatieNou - string
	*/
	void setDestinatie(string destinatieNou);

	/*
	* Seteaza tipul unei oferte.
	* @param: tipNou - string
	*/
	void setTip(string tipNou);

	/*
	* Seteaza pretul unei oferte.
	* @param: pretNou - float
	*/
	void setPret(float pretNou);

	//operator de egalitate dintre 2 obiecte
	bool operator == (const Oferta& copie);


};

class Validator {
public:
	/*
	* Valideaza datele unei oferte.
	* @param: denumire - string
	*		: destinatie -  string
	*		: tip - string
	*		: pret - float
	* @return : arunca exceptii daca oferta nu este valida
	*/
	void valideazaOferta(string denumire, string destinatie, string tip, float pret) const;
};

/////comparatori


/*
* compara denumirea a doua oferte
* @param: oferta1, oferta2 - Oferta, ce trebuie comparate
* @return: true - oferta1.denumire > oferta2.denumire
*			false - altfel
*/
bool cmpDenumire(const Oferta& oferta1, const Oferta& oferta2);

/*
* compara lexicografic destinatia a doua oferte
*/
bool cmpDestinatie(const Oferta& oferta1, const Oferta& oferta2);

class OfertaDTO {
public:
	string tip;
	int nr;
	OfertaDTO() = default;
	OfertaDTO(const std::string& tip, int nr) : tip{ tip }, nr{ nr } {};
};