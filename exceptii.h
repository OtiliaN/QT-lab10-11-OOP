#pragma once
#include<string>
#include<vector>

using std::string;
using std::vector;

//Clasa de exceptii pentru repository
class RepoExceptii {
private:
	string mesaj;
public:
	//constructor
	RepoExceptii(string mesaj) : mesaj{ mesaj } {}
	string getMesaj() const {
		return mesaj;
	}

};

//Clasa de exceptii pentru validator
class ValidatorExceptii {
	vector<string> mesaje;
public:
	ValidatorExceptii(const vector<string>& mesaje): mesaje{ mesaje } {}
	vector<string> getMesaje() const {
		return mesaje;
	}
};