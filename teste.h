#pragma once
class Teste {
private:
	///DOMAIN
	void testCreareValidareOferta();
	void testEgalitate();

	//REPO
	void testAdaugaOferta();
	void testStergeOferta();
	void testModificareOferta();
	void testCautaOferta();

	//SERVICE
	void testServiceAdaugare();
	void testServiceSterge();
	void testServiceModificare();
	void testServiceCauta();
	void testfiltreazaOferte();
	void testSortare();

	void testGenerareRaport();

	void testUndo();

	//WISHLIST
	void testeWishlist();

	//FISIER
	void testFileRepo();

	//PROBABILITATE
	void testRepoProb();

public:
	//Ruleaza toate testele
	void toateTestele();
};
