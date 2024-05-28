#include "teste.h"
#include "domain.h"
#include "repo.h"
#include "service.h"
#include"exceptii.h"
#include <string>
#include <iostream>
#include <assert.h>
#include "wishlist.h"

using std::string;

void Teste::toateTestele() {
	//DOMAIN
	testCreareValidareOferta();
	testEgalitate();

	//REPO
	testAdaugaOferta();
	testStergeOferta();
	testModificareOferta();
	testCautaOferta();

	//SERVICE
	testServiceAdaugare();
	testServiceSterge();
	testServiceModificare();
	testServiceCauta();
	testfiltreazaOferte();
	testSortare();

	testGenerareRaport();
	testUndo();

	//WISHLIST
	testeWishlist();

	//FISIER
	testFileRepo();

	//Probabilitate
	testRepoProb();
}


//DOMAIN
void Teste::testCreareValidareOferta() {
	//test get si set
	Oferta o( "munte", "Predeal", "vacanta", 1500);
	
	assert(o.getDenumire() == "munte");
	assert(o.getDestinatie() == "Predeal");
	assert(o.getTip() == "vacanta");
	assert(o.getPret() == 1500);

	o.setDenumire("mare");
	o.setDestinatie("Mamaia");
	o.setTip("excursie scolara");
	o.setPret(400);

	assert(o.getDenumire() == "mare");
	assert(o.getDestinatie() == "Mamaia");
	assert(o.getTip() == "excursie scolara");
	assert(o.getPret() == 400);

	//test functie validare
	Validator validator;
	validator.valideazaOferta("munte", "Predeal", "vacanta", 1500);

	try {
		validator.valideazaOferta("", "", "", -5);
		assert(false);
	}
	catch (ValidatorExceptii e) {
		assert(true);
	}

}
void Teste::testEgalitate() {
	Oferta o1("munte", "Predeal", "vacanta", 1500);
	Oferta o2("munte", "Predeal", "vacanta", 1500);

	assert(o1 == o2);

}

//REPO

void Teste::testAdaugaOferta() {

	Repo repo;
	assert(repo.getAll().size() == 0);

	repo.adaugaOferta(Oferta{ "munte", "Predeal", "vacanta", 1500 });
	repo.adaugaOferta(Oferta{ "mare", "Mamaia", "vacanta", 1500 });
	assert(repo.getAll().size() == 2);
	try {
		repo.adaugaOferta(Oferta{"munte", "Predeal", "vacanta", 1500 });
		assert(false);
	}
	catch (const RepoExceptii& msj) {
		assert(msj.getMesaj() == "Oferta exista deja!\n");
	}

}

void Teste::testStergeOferta() {
	Repo repo;
	assert(repo.getAll().size() == 0);

	repo.adaugaOferta(Oferta{"munte", "Predeal", "vacanta", 1500 });
	repo.adaugaOferta(Oferta{"mare", "Mamaia", "vacanta", 1500 });
	assert(repo.getAll().size() == 2);

	repo.stergeOferta(2);
	assert(repo.getAll().size() == 1);
	try {
		repo.stergeOferta(0);
		assert(false);
	}
	catch (const RepoExceptii& msj) {
		assert(msj.getMesaj() == "Nu exista oferta!\n");
	}
}

void Teste::testModificareOferta() {
	Repo repo;
	assert(repo.getAll().size() == 0);

	repo.adaugaOferta(Oferta{ "munte", "Predeal", "vacanta", 1500 });
	repo.adaugaOferta(Oferta{"mare", "Mamaia", "vacanta", 1500 });
	assert(repo.getAll().size() == 2);

	repo.modificaOferta(1, Oferta{ "city-break", "Paris", "munca", 1000 });
	auto lst = repo.getAll();
	assert(lst[0].getDestinatie() == "Paris");

	try {
		repo.modificaOferta(7, Oferta{ "city-break", "Paris", "munca", 1000 });
		assert(false);
	}
	catch (const RepoExceptii& msj) {
		assert(msj.getMesaj() == "Nu exista oferta!\n");
	}
}
void Teste::testCautaOferta() {
	Repo repo;

	assert(repo.getAll().size() == 0);

	repo.adaugaOferta(Oferta{ "munte", "Predeal", "vacanta", 1500 });
	repo.adaugaOferta(Oferta{"mare", "Mamaia", "vacanta", 1500 });
	assert(repo.getAll().size() == 2);
	Oferta o_cautata = Oferta{ "munte", "Predeal", "vacanta", 1500 };
	Oferta o_gasita = repo.cautaOfertaDenumire("munte");
	assert(o_gasita == o_cautata);

	try {
		repo.cautaOfertaDenumire("city-break");
		assert(false);
	}
	catch (const RepoExceptii& msj) {
		assert(msj.getMesaj() == "Nu exista oferta cu aceasta denumire!\n");
	}

}

//SERVICE
void Teste::testServiceAdaugare() {
	Repo repo;
	Validator validator;
	Service srv(repo, validator);
	auto lst = srv.getLista();

	assert(srv.getLista().size() == 0);

	srv.adaugaSrv("munte", "Predeal", "vacanta", 1400);
	assert(srv.getLista().size() == 1);

	srv.adaugaSrv("mare", "Mamaia", "vacanta", 100);

	lst = srv.getLista();
	assert(lst.size() == 2);

	assert(lst[0].getDenumire() == "munte");
	assert(lst[0].getDestinatie() == "Predeal");
	assert(lst[0].getTip() == "vacanta");
	assert(lst[0].getPret() == 1400);

	try {
		srv.adaugaSrv("", "", "", -8);
		assert(false);
	}
	catch (const ValidatorExceptii& e) {
		assert(e.getMesaje().size() == 4);
	}

	try {
		srv.adaugaSrv("munte", "Predeal", "vacanta", 1400);
		assert(false);
	}
	catch (RepoExceptii e) {
		assert(true);
	}
}

void Teste::testServiceSterge() {
	Repo repo;
	Validator validator;
	Service srv(repo, validator);

	srv.adaugaSrv("city-break", "Paris", "vacanta", 5000);
	srv.adaugaSrv("munte", "Predeal", "vacanta", 1400);
	srv.adaugaSrv("mare", "Mamaia", "vacanta", 100);
	srv.adaugaSrv("munte", "Cavnic", "tabara", 200);
	assert(srv.getLista().size() == 4);

	auto lst = srv.getLista();
	assert(lst[1].getDestinatie() == "Predeal");
	srv.stergeSrv(1);
	assert(srv.getLista().size() == 3);

	lst = srv.getLista();
	assert(lst[1].getDestinatie() == "Mamaia");

}

void Teste::testServiceModificare() {
	Repo repo;
	Validator validator;
	Service srv(repo, validator);

	srv.adaugaSrv("city-break", "Paris", "vacanta", 5000);
	srv.adaugaSrv("munte", "Predeal", "vacanta", 1400);

	auto lst = srv.getLista();
	assert(lst[1].getDestinatie() == "Predeal");
	srv.modificaSrv(2, "munte", "Cavnic", "tabara", 450);
	assert(srv.getLista().size() == 2);

	lst = srv.getLista();
	assert(lst[1].getDestinatie() == "Cavnic");
}

void Teste::testServiceCauta() {
	Repo repo;
	Validator validator;
	Service srv(repo, validator);

	srv.adaugaSrv("city-break", "Paris", "vacanta", 5000);
	srv.adaugaSrv("munte", "Predeal", "vacanta", 1400);

	auto o_cautata = srv.cautaSrv("munte");
	assert(o_cautata.getDenumire() == "munte");
	assert(o_cautata.getDestinatie() == "Predeal");
	assert(o_cautata.getTip() == "vacanta");
	assert(o_cautata.getPret() == 1400);

	try {
		srv.cautaSrv("mare");
		assert(false);
	}
	catch (RepoExceptii e) {
		assert(true);
	}

}

void Teste::testfiltreazaOferte() {
	Repo repo;
	Validator validator;
	Service srv(repo, validator);

	srv.adaugaSrv("city-break", "Paris", "vacanta", 5000);
	srv.adaugaSrv("munte", "Predeal", "vacanta", 1000);
	srv.adaugaSrv("mare", "Mamaia", "vacanta", 100);
	srv.adaugaSrv("munte", "Predeal", "tabara", 200);
	auto lst = srv.getLista();

	assert(lst.size() == 4);
	vector<Oferta> test;
	test = srv.filtreazaOferta("Predeal", 0, 1);
	assert(test.size() == 2);

	test = srv.filtreazaOferta("", 1000, 2);
	assert(test.size() == 3);

}

void Teste::testSortare() {
	Repo repo;
	Validator validator;
	Service srv(repo, validator);

	srv.adaugaSrv("city-break", "Paris", "vacanta", 5000);
	srv.adaugaSrv("munte", "Predeal", "vacanta", 1000);
	srv.adaugaSrv("mare", "Mamaia", "vacanta", 100);
	srv.adaugaSrv("munte", "Predeal", "tabara", 200);

	vector<Oferta> test;
	test = srv.sortareDupaDenumire();
	assert(test[0].getDenumire() == "city-break");
	assert(test[1].getDenumire() == "mare");
	assert(test[2].getDenumire() == "munte");

	test = srv.sortareDupaDestinatie();
	assert(test[0].getDestinatie() == "Mamaia");
	assert(test[1].getDestinatie() == "Paris");
	assert(test[2].getDestinatie() == "Predeal");

	test = srv.sortareTipPret();
	assert(test[0].getTip() == "tabara");
	assert(test[1].getTip() == "vacanta");

	assert(test[1].getPret() == 100);
	assert(test[2].getPret() == 1000);
	assert(test[3].getPret() == 5000);
}

void Teste::testUndo() {
	Repo repo;
	Validator validator;
	Service srv(repo, validator);
	srv.adaugaSrv("city-break", "Paris", "vacanta", 5000);
	srv.adaugaSrv("mare", "Mamaia", "vacanta", 100);
	srv.adaugaSrv("munte", "Predeal", "tabara", 200);

	srv.undo();
	try {
		srv.cautaSrv("munte");
		assert(false);
	}
	catch (RepoExceptii e) {
		assert(true);
	}
	auto lst = srv.getLista();
	assert(lst[0].getDestinatie() == "Paris");
	assert(lst[1].getDestinatie() == "Mamaia");
	assert(srv.getLista().size() == 2);

	srv.stergeSrv(1);
	try {
		srv.cautaSrv("city-break");
		assert(false);
	}
	catch (RepoExceptii e) {
		assert(true);
	}
	srv.undo();
	
	lst = srv.getLista();
	assert(lst[0].getDestinatie() == "Mamaia");
	assert(lst[1].getDestinatie() == "Paris");

	srv.modificaSrv(1, "munte", "Cavnic", "tabara", 450);
	lst = srv.getLista();
	assert(lst[0].getDestinatie() == "Cavnic");
	assert(lst[1].getDestinatie() == "Paris");

	srv.undo();
	lst = srv.getLista();
	assert(lst[0].getDestinatie() == "Mamaia");
	try {
		srv.undo();
		srv.undo();
		srv.undo();
		srv.undo();
		assert(false);
	}
	catch (const RepoExceptii msg) {
		assert(msg.getMesaj() == "Nu se mai poate face undo!\n");
	}

}

///WISHLIST
void Teste::testeWishlist() {
	Wishlist wishlist;
	auto w = wishlist.getWishlist();
	assert(w.size() == 0);

	//adaugare
	Oferta o1("city-break", "Paris", "vacanta", 5000);
	Oferta o2("munte", "Predeal", "vacanta", 1000);
	wishlist.adaugaWishlist(o1);
	w = wishlist.getWishlist();
	assert(w.size() == 1);
	wishlist.adaugaWishlist(o2);
	w = wishlist.getWishlist();
	assert(w.size() == 2);

	//golire
	wishlist.golesteWishlist();
	w = wishlist.getWishlist();
	assert(w.size() == 0);

	//random
	Repo repo;
	Oferta o3("mare", "Mamaia", "vacanta", 100);
	Oferta o4("munte", "Predeal", "tabara", 200);
	repo.adaugaOferta(o1);
	repo.adaugaOferta(o2);
	repo.adaugaOferta(o3);
	repo.adaugaOferta(o4);
	wishlist.adaugaRandom(repo.getAll(), 3);
	assert(wishlist.getWishlist().size() == 3);

	wishlist.exportHTML("testf.html");

}

void Teste::testGenerareRaport() {
	Repo repo;
	Validator validator;
	Service srv(repo, validator);

	srv.adaugaSrv("city-break", "Paris", "vacanta", 5000);
	srv.adaugaSrv("munte", "Predeal", "vacanta", 1000);
	srv.adaugaSrv("mare", "Mamaia", "conferinta", 100);
	srv.adaugaSrv("munte", "Predeal", "tabara", 200);
	srv.adaugaSrv("city-break", "Cluj", "tabara", 500);

	assert(srv.getLista().size() == 5);
	std::map<std::string, OfertaDTO> raport = srv.generareRaport(repo.getAll());
	assert(raport.size() == 3);

	assert(raport["vacanta"].nr == 2);
	assert(raport["conferinta"].nr == 1);
	assert(raport["tabara"].nr == 2);
	assert(raport.find("concediu") == raport.end());
}

///FISIER
void Teste::testFileRepo() {
	RepoFile repo{ "test.txt" };

	repo.adaugaOferta(Oferta{ "munte", "Predeal", "vacanta", 1500 });
	repo.modificaOferta(1, Oferta{ "city-break", "Paris", "munca", 1000 });
	repo.stergeOferta(1);
	try {
		RepoFile repotest{ "asdd.txt" };
		assert(false);
	}
	catch (const RepoExceptii msg) {
		assert(true);
	}
}
///REPO PROBABILITATE

void Teste::testRepoProb() {
	Oferta o1("munte", "Predeal", "vacanta", 1500);
	auto repo=RepoProbabilitate(1);
	repo.adaugaOferta(o1);
	const auto lista = repo.getAll();
	assert(lista.size() == 1);
	assert(lista[0].getDenumire() == "munte");
	assert(lista[0].getDestinatie() == "Predeal");
	assert(lista[0].getTip() == "vacanta");
	assert(lista[0].getPret() == 1500);
	try {
		repo.adaugaOferta(Oferta{ "munte", "Predeal", "vacanta", 1500 });
		assert(false);
	}
	catch (const RepoExceptii& msj) {
		assert(msj.getMesaj() == "Oferta exista deja!\n");
	}

	Oferta o_cautata = Oferta{ "munte", "Predeal", "vacanta", 1500 };
	Oferta o_gasita = repo.cautaOfertaDenumire("munte");
	assert(o_gasita == o_cautata);
	try {
		repo.cautaOfertaDenumire("city-break");
		assert(false);
	}
	catch (const RepoExceptii& msj) {
		assert(msj.getMesaj() == "Nu exista oferta cu aceasta denumire!\n");
	}

	repo.modificaOferta(1, Oferta{ "city-break", "Paris", "munca", 1000 });
	const auto lista1 = repo.getAll();
	assert(lista1.size() == 1);
	assert(lista1[0].getDenumire() == "city-break");
	assert(lista1[0].getDestinatie() == "Paris");
	assert(lista1[0].getTip() == "munca");
	assert(lista1[0].getPret() == 1000);
	try {
		repo.modificaOferta(7, Oferta{ "city-break", "Paris", "munca", 1000 });
		assert(false);
	}
	catch (const RepoExceptii& msj) {
		assert(msj.getMesaj() == "Nu exista oferta!\n");
	}

	repo.stergeOferta(1);
	const auto lista2 = repo.getAll();
	assert(lista2.size() == 0);
	try {
		repo.stergeOferta(0);
		assert(false);
	}
	catch (const RepoExceptii& msj) {
		assert(msj.getMesaj() == "Nu exista oferta!\n");
	}

	repo = RepoProbabilitate((int)0.0);
	try {
		repo.adaugaOferta(o1);
		assert(false);
	}
	catch (RepoExceptii msg) {
		assert(true);
	}
}