#include "wishlist.h"
#include <random>
#include<fstream>
#include "exceptii.h"

Wishlist::Wishlist() {
	wishlist.clear();
}

void Wishlist::adaugaWishlist(const Oferta& oferta) {
	wishlist.push_back(oferta);
}

void Wishlist::golesteWishlist() {
	wishlist.clear();
}

void Wishlist::adaugaRandom(const vector<Oferta>& oferte, int nr) {
	std::mt19937 mt{ std::random_device{}() };
	std::uniform_int_distribution<> dist(0, (int)oferte.size() - 1);
	int randNr;
	for (int i = 0; i < nr; i++) {
		randNr = dist(mt);
		adaugaWishlist(oferte[randNr]);
	}
}

void Wishlist::exportHTML(const string& filename) {
    std::ofstream fout(filename);
    fout << "<html>" << std::endl;
    fout << "<h1><div align=\"center\"><b>Wishlist</b></div></h1>\n" << std::endl;
    fout << "<body>" << std::endl;
    fout << "<table border='1'>" << std::endl;
    fout << "<tr>"
        << "<th>Denumire</th>"
        << "<th>Destinatie</th>"
        << "<th>Tip</th>"
        << "<th>Pret</th>"
        << "</tr>" << std::endl;
    for (auto& o : wishlist) {
        fout << "<tr>"
            << "<td>" << o.getDenumire() << "</td>"
            << "<td>" << o.getDestinatie() << "</td>"
            << "<td>" << o.getTip() << "</td>"
            << "<td>" << o.getPret() << "</td>"
            << "</tr>" << std::endl;
    }
    fout << "</table>" << std::endl;
    fout << "</body>" << std::endl;
    fout << "</html>" << std::endl;

}
vector<Oferta> Wishlist::getWishlist() {
	return wishlist;
}