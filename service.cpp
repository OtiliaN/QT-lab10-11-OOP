#include "service.h"
#include "domain.h"
#include "exceptii.h"
#include<algorithm>
#include<iterator>

void Service::adaugaSrv(const string& denumire, const string& destinatie, const string& tip, float pret) {

	validator.valideazaOferta(denumire, destinatie, tip, pret);
	Oferta oferta {denumire, destinatie, tip, pret };
	repo.adaugaOferta(oferta);
	int poz = int(getLista().size());
	undoAct.push_back(std::make_unique<UndoAdauga>(repo, oferta, poz));
}

void Service::stergeSrv(const int& poz) {
	const auto& l = getLista(); 
	repo.stergeOferta(poz);
	const Oferta& oferta_stearsa = l[poz-1];
	undoAct.push_back(std::make_unique<UndoSterge>(repo, oferta_stearsa));

}

void Service::modificaSrv(const int& poz, const string& denumire, const string& destinatie, const string& tip, float pret) {
	validator.valideazaOferta(denumire, destinatie, tip, pret);
	const auto& l = getLista();
	Oferta oferta{denumire, destinatie, tip, pret };
	repo.modificaOferta(poz, oferta);
	const Oferta& oferta_modificata = l[poz - 1];
	undoAct.push_back(std::make_unique<UndoModifica>(repo, oferta_modificata, poz));
}


Oferta& Service::cautaSrv(const string& denumire ) {
	return repo.cautaOfertaDenumire(denumire);
}

Oferta& Service::cautaSrvDestinatie(const string& destinatie) {
	return repo.cautaOfertaDestinatie(destinatie);
}

vector <Oferta> Service::getLista() const {
	return repo.getAll();
}

vector<Oferta> Service::filtreazaOferta(const string& destinatie, const float pret, const int tip) {
	vector<Oferta> rezultat;
	auto copie = repo.getAll();
	if (tip == 1) {
		std::copy_if(copie.begin(), copie.end(), std::back_inserter(rezultat), [destinatie](const Oferta& o) {
			return o.getDestinatie() == destinatie;
		});
	}
	else {
		std::copy_if(copie.begin(), copie.end(), std::back_inserter(rezultat), [pret](const Oferta& o) {
			return o.getPret() <= pret;
			});
	}
	return rezultat;

}
vector<Oferta> Service::sortareDupaDenumire() {
	auto copie = this->getLista();
	std::sort(copie.begin(), copie.end(), cmpDenumire);
	return copie;
}

vector<Oferta> Service::sortareDupaDestinatie() {
	auto copie = this->getLista();
	std::sort(copie.begin(), copie.end(), cmpDestinatie);
	return copie;
}

vector<Oferta> Service::sortareTipPret() {
	auto copie = this->getLista();
	std::sort(copie.begin(), copie.end(), [](const Oferta& o1, const Oferta& o2) {
		if (o1.getTip() == o2.getTip()) {
			return o1.getPret() < o2.getPret();
		}
		return o1.getTip() < o2.getTip();
		});
	return copie;

}

std::map<std::string, OfertaDTO> Service::generareRaport(const std::vector<Oferta>& oferte) {
	std::map<std::string, OfertaDTO> raport;
	for (const auto& of : oferte) {
		const std::string& tip = of.getTip();
		if (raport.find(tip) != raport.end()) {
			raport[tip].nr = raport[tip].nr + 1;
		}
		else {
			raport[tip] = OfertaDTO(tip, 1);
		}
	}
	return raport;
}

void Service::undo() {
	if (undoAct.empty()) {
		throw RepoExceptii("Nu se mai poate face undo!\n");
	}
	undoAct.back()->doUndo();
	undoAct.pop_back();
}