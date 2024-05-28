#pragma once
#include "domain.h"
#include <vector>
#include<fstream>
#include<map>
using std::vector;
using std::ifstream;
using std::ofstream;
using std::map;
using std::make_pair;

class RepoAbstract {
public:
	virtual void adaugaOferta(const Oferta& oferta) = 0;
	virtual void stergeOferta(const int& poz) = 0;
	virtual void modificaOferta(const int& poz, const Oferta& o)=0;
	virtual Oferta& cautaOfertaDenumire(const string& denumire)=0;
	virtual Oferta& cautaOfertaDestinatie(const string& destinatie) = 0;
	virtual vector<Oferta> getAll() =0;
	virtual bool existaOferta(const Oferta& o)=0;
	virtual ~RepoAbstract() = default;
};
class Repo: public RepoAbstract {
private:
	//vectorul in care retin ofertele
	vector<Oferta> oferte;


public:

	//constructor repo
	Repo() = default;

	//nu se copiaza aceasta clasa
	Repo(const Repo& copy) = delete;

	//destructor
	virtual ~Repo() = default;

	/*
	* verifica existenta unui oferta
	* @return: - true: daca oferta exista deja
	*		   - false: daca nu exista oferta
	*/
	virtual bool existaOferta(const Oferta& o) override;

	/*
	* Adauga o oferta in lista
	* @param: oferta - Oferta, ce trebuie adaugata in lista
	*/
	virtual void adaugaOferta(const Oferta& oferta) override;

	/*
	* Stergem oferta de pe pozitia introdusa
	* @param: poz - intreg
	*/
	virtual void stergeOferta(const int& poz) override;

	/*
	* Modifica oferta de pe pozitie introdusa
	* @param: poz - intreg
	*		: o - datele ofertei care trebuie modificate
	*/
	virtual void modificaOferta(const int& poz, const Oferta& o) override;

	
	/*
	* Cauta oferta dupa denumire
	* @param: denumire - ofertei cautate
	*/
	Oferta& cautaOfertaDenumire(const string& denumire) override;

	Oferta& cautaOfertaDestinatie(const string& destinatie) override;

	/*
	* Returneaza lista ofertelor
	* @return: oferte - lista de oferte
	*/
	vector<Oferta> getAll() override;
}; 

///FISIER
class RepoFile : public Repo {
private:
	string filename;
	void loadFromFile();
	void writeToFile();
public:
	//RepoFile() = default;

	RepoFile(const string& filename) : Repo(), filename{ filename } {
		loadFromFile(); //incarcam datele din fisier
	}

	void adaugaOferta(const Oferta& oferta) override {
		Repo::adaugaOferta(oferta);
		writeToFile();
	}

	void stergeOferta(const int& poz) override {
		Repo::stergeOferta(poz);
		writeToFile();
	}

	void modificaOferta(const int& poz, const Oferta& o) override {
		Repo::modificaOferta(poz, o);
		writeToFile();
	}
	
	//~RepoFile() override = default;
};

///PROBABILITATE

class RepoProbabilitate : public RepoAbstract {
private:
	int cheie;
	float probabiliate;
	map<int, Oferta> elem;
	void determinaSanse();
public:
	RepoProbabilitate() = default;
	explicit RepoProbabilitate(float prob);
	virtual void adaugaOferta(const Oferta& oferta) override;
	virtual void stergeOferta(const int& poz) override;
	virtual void modificaOferta(const int& poz, const Oferta& o) override;
	virtual Oferta& cautaOfertaDenumire(const string& denumire) override;
	virtual Oferta& cautaOfertaDestinatie(const string& destinatie) override;
	virtual vector<Oferta> getAll() override;
	virtual bool existaOferta(const Oferta& o) override;
};