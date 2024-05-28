#pragma once
#include"domain.h"
#include"repo.h"

class ActiuneUndo {
public:
	virtual void doUndo() = 0;
	// destructorul e pentru  a ne asigura ca daca dau delete se apeleaza destuctorul din clasa care trebuie
	virtual ~ActiuneUndo() = default;
};

//clasa care mosteneste metodele clasei ActiuneUndo
class UndoAdauga : public ActiuneUndo {
	Oferta oferta_adaugata;
	RepoAbstract& repo;
	int poz;
public:
	UndoAdauga(RepoAbstract& repo, const Oferta& o, int poz) : repo{ repo }, oferta_adaugata{ o }, poz{ poz } {}

	void doUndo() override {
		repo.stergeOferta(poz);
	}
};

class UndoSterge : public ActiuneUndo {
	Oferta oferta_stearsa;
	RepoAbstract& repo;
public:
	UndoSterge(RepoAbstract& repo, const Oferta& o):repo{repo}, oferta_stearsa{o}{}

	void doUndo() override {
		repo.adaugaOferta(oferta_stearsa);
	}
};

class UndoModifica : public ActiuneUndo {
	Oferta oferta_modificata;
	RepoAbstract& repo;
	int poz;
public:
	UndoModifica(RepoAbstract& repo, const Oferta& o, int poz): repo{repo}, oferta_modificata{o}, poz{poz} {}
	void doUndo() override {
		repo.modificaOferta(poz, oferta_modificata);
	}
};