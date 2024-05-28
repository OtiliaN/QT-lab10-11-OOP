#include "domain.h"
#include <string.h>
#include "exceptii.h"

using std::string;


////getters

string Oferta::getDenumire() const {
	return denumire;
}

string Oferta::getDestinatie() const {
	return destinatie;
}

string Oferta::getTip() const {
	return tip;
}

float Oferta::getPret() const {
	return pret;
}


////setters
void Oferta::setDenumire(string denumireNou) {
	denumire = denumireNou;
}

void Oferta::setDestinatie(string destinatieNou) {
	destinatie = destinatieNou;
}

void Oferta::setTip(string tipNou) {
	tip = tipNou;
}

void Oferta::setPret(float pretNou) {
	pret = pretNou;
}

////operatori
bool Oferta::operator==(const Oferta& copie) {
	return denumire == copie.getDenumire() && destinatie == copie.getDestinatie() && tip == copie.getTip() && pret == copie.getPret();
}

///comparatori
bool cmpDenumire(const Oferta& oferta1, const Oferta& oferta2) {
	if (oferta1.getDenumire() < oferta2.getDenumire())
		return true;
	return false;
}

bool cmpDestinatie(const Oferta& oferta1, const Oferta& oferta2) {
	if (oferta1.getDestinatie() < oferta2.getDestinatie())
		return true;
	return false;
}

////validatori
void Validator::valideazaOferta(string denumire, string destinatie, string tip, float pret) const {
	vector<string> erori;
	if (denumire.size() == 0) {
		erori.push_back("Denumirea nu poate fi vida!\n");
	}
	if (destinatie.size() == 0) {
		erori.push_back("Destinatia nu poate fi vida!\n");
	}
	if (tip.size() == 0) {
		erori.push_back("Tipul nu poate fi vid!\n");
	}
	if (pret <= 0) {
		erori.push_back("Pretul nu poate fi negativ!\n");
	}
	if (erori.size() > 0) {
		throw ValidatorExceptii(erori);
	}
}


////comparatori