#pragma once
#include <vector>
#include "domain.h"

using std::vector;

class Wishlist {
private:
	vector<Oferta> wishlist;
public:
	//constructor 
	Wishlist();

	/*
	* Functia adauga o oferta in wishlist
	* @param: oferta - ce trebuie adaugata
	*/
	void adaugaWishlist(const Oferta& oferta);

	/*
	* Sterge toate ofertele din wishlist
	*/
	void golesteWishlist();

	/*
	* Adauga un numar introdus de oferte random
	*/
	void adaugaRandom(const vector<Oferta>& oferte, int nr);

	/*
	* Exporta wishlist-ul intr-un fisier html
	* @param: filename - string, numele fisierului in care se exporta
	*/
	void exportHTML(const string& filename);

	/*
	* Returneaza toate elementele din wishlist
	*/
	vector<Oferta> getWishlist();
};