#include "repo.h"
#include "exceptii.h"
#include<iostream>
#include<algorithm>


bool Repo::existaOferta(const Oferta& o) {
	for (auto of : oferte) {
		if (of == o) {
			return true;
		}
	}
	return false;
	
}

void Repo::adaugaOferta(const Oferta& oferta) {

	if (existaOferta(oferta) == false) {
		oferte.push_back(oferta);
	}
	else {
		throw RepoExceptii("Oferta exista deja!\n");
	}
}

void Repo::stergeOferta(const int& poz) {
	size_t index = 0;
	for (auto of: oferte) {
		if (index == poz - 1) {
			oferte.erase(oferte.begin() + index);
			return;
		}
		index++;
	}
	throw RepoExceptii("Nu exista oferta!\n");
}

void Repo::modificaOferta(const int& poz, const Oferta& o) {
	size_t i = 0;
	for (auto of : oferte) {
		if (i == poz - 1) {
			oferte[i].setDenumire(o.getDenumire());
			oferte[i].setDestinatie(o.getDestinatie());
			oferte[i].setTip(o.getTip());
			oferte[i].setPret(o.getPret());
			return;
		}
		i++;
	}
	throw RepoExceptii("Nu exista oferta!\n");
}

Oferta& Repo::cautaOfertaDenumire(const string& denumire){
	auto it = std::find_if(oferte.begin(), oferte.end(), [=](const Oferta& oferta) {
		return oferta.getDenumire() == denumire;
		});

	if (it != oferte.end()) {
		return *it;
	}
	throw RepoExceptii("Nu exista oferta cu aceasta denumire!\n");}

Oferta& Repo::cautaOfertaDestinatie(const string& destinatie) {
	auto it = std::find_if(oferte.begin(), oferte.end(), [=](const Oferta& oferta) {
		return oferta.getDestinatie() == destinatie;
		});

	if (it != oferte.end()) {
		return *it;
	}
	throw RepoExceptii("Nu exista oferta cu aceasta destinatie!\n");
}

vector <Oferta> Repo::getAll()  {
	return oferte;
}

///FISIER
void RepoFile::loadFromFile() {
	ifstream fin(filename);
	if (!fin.is_open()) {
		throw RepoExceptii("Nu s-a putut deschide fisierul: " + filename);
	}
	while (!fin.eof()) {
		string denumire;
		std::getline(fin, denumire, ',');
		string destinatie;
		std::getline(fin, destinatie, ',');
		string tip;
		std::getline(fin, tip, ',');
		string pretStr;
		std::getline(fin, pretStr);
		if (pretStr == "")
			break;
		float pret = std::stof(pretStr);
		Oferta o{ denumire, destinatie, tip, pret };
		Repo::adaugaOferta(o);
	}
	
	fin.close();
}

void RepoFile::writeToFile() {
	ofstream fout(filename);
	if (!fout.is_open()) {
		throw RepoExceptii("Nu s-a putut deschide fisierul: " + filename);
	}
	for (auto& o : getAll()) {
		fout << o.getDenumire() << "," << o.getDestinatie() << "," << o.getTip() << "," << o.getPret() << "\n";
	}
	fout.close();
}

//PROBABILITATE

RepoProbabilitate::RepoProbabilitate(float sansa) {
	probabiliate = sansa;
	cheie = 0;
	elem.clear();
}

void RepoProbabilitate::determinaSanse() {
	auto const prob = int(probabiliate * 10);
	int const nr = rand() % 10 + 1;
	if (nr <= prob) {
		return;
	}
	throw RepoExceptii("Eroare!!\n");
}

bool RepoProbabilitate::existaOferta(const Oferta& o) {
	determinaSanse();
	for (auto& it : elem) {
		if (it.second.getDenumire() == o.getDenumire() && it.second.getDestinatie() == o.getDestinatie() && it.second.getPret() == o.getPret() && it.second.getTip() == o.getTip()) {
			return true;
		}
	}
	return false;
}

void RepoProbabilitate::adaugaOferta(const Oferta& oferta) {
	determinaSanse();
	if (existaOferta(oferta) == false) {
		cheie++;
		elem.insert(make_pair(cheie, oferta));
	}
	else {
		throw RepoExceptii("Oferta exista deja!\n");
	}

}

void RepoProbabilitate::stergeOferta(const int& poz) {
	determinaSanse();
	for (auto& it : elem) {
		if (it.first == poz) {
			elem.erase(poz);
			return;
		}
	}
	throw RepoExceptii("Nu exista oferta!\n");
}

void RepoProbabilitate::modificaOferta(const int& poz, const Oferta& o) {
	determinaSanse();
	for (auto& it : elem) {
		if (it.first == poz) {
			elem.erase(poz);
			elem.insert(make_pair(poz, o));
			return;
		}
	}
	throw RepoExceptii("Nu exista oferta!\n");
}

Oferta& RepoProbabilitate::cautaOfertaDenumire(const string& denumire) {
	determinaSanse();
	for (auto& it : elem) {
		if (it.second.getDenumire() == denumire) {
			return it.second;
		}
	}
	throw RepoExceptii("Nu exista oferta cu aceasta denumire!\n");
}

Oferta& RepoProbabilitate::cautaOfertaDestinatie(const string& destinatie) {
	determinaSanse();
	for (auto& it : elem) {
		if (it.second.getDestinatie() == destinatie) {
			return it.second;
		}
	}
	throw RepoExceptii("Nu exista oferta cu aceasta destinatie!\n");
}


vector <Oferta> RepoProbabilitate::getAll()  {
	determinaSanse();
	vector<Oferta> all;
	all.clear();
	for (auto& it : elem) {
		all.push_back(it.second);
	}
	return all;
}