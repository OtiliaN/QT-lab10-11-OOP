#pragma once
#include "repo.h"
#include "domain.h"
#include"undo.h"
#include<map>

using std::unique_ptr;

class Service {
	//referinta la repo
	RepoAbstract& repo;

	//Lista de undo
	vector<unique_ptr<ActiuneUndo>> undoAct;

	//referinta la validator
	Validator& validator;
public:
	//constructorul clasei
	Service(RepoAbstract& repo, Validator& validator) : repo{ repo }, validator{ validator } {}

	//nu se poate copia service-ul
	Service(const Service& copie) = delete;

	//constructor implicit
	Service() = default;

	//destructor implicit
	~Service() = default;

	/*
	* adauga o oferta in lista de oferte
	* arunca exceptie daca: deja exista sau nu este valida
	* @param: denumire, destinatie, tip - string
	*		  pret - float
	*/
	void adaugaSrv(const string& denumire, const string& destinatie, const string& tip, float pret);

	/*
	* sterge o oferta de pe pozitia data (indexarea incepe de la 1)
	* @param: poz - int
	*/
	void stergeSrv(const int& poz);

	/*
	* modifica o oferta de pe pozitia data
	* @param: poz - int
	*		: - datele cu care se va modifica oferta
	*/
	void modificaSrv(const int& poz, const string& denumire, const string& destinatie, const string& tip, float pret);


	/*
	* cauta o oferta dupa denumire
	* @param: denumire
	*/
	Oferta& cautaSrv(const string& denumire);


	Oferta& cautaSrvDestinatie(const string& destinatie);

	/*
	* Returneaza lista ofertelor
	*/
	vector<Oferta> getLista() const;

	/*
	* Filtreaza ofertele dupa un criteriu dat (destinatie sau pret)
	* 1. ofertele cu aceeasi destinatie introdusa
	* 2. ofertele cu pretul mai mic sau egal decat cel introdus
	*/
	vector<Oferta> filtreazaOferta(const string& destinatie, const float pret, const int tip);

	/*
	* Sorteaza ofertele lexicografic dupa denumire
	*/
	vector<Oferta> sortareDupaDenumire();

	/*
	* Sorteaza ofertele lexicografic dupa destinatie
	*/
	vector<Oferta> sortareDupaDestinatie();

	/*
	* Sorteaza ofertele dupa tip, iar daca 2 oferte au acelasi tip, le sorteaza dupa pret
	*/
	vector<Oferta> sortareTipPret();

	/*
	* Raport
	*/
	std::map<std::string, OfertaDTO> generareRaport(const std::vector<Oferta>& oferte);
	
	/*
	* functia de undo
	*/
	void undo();
};
