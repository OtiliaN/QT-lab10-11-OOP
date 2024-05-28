#pragma once
#include <QtWidgets/qwidget.h>
#include <QtWidgets/qboxlayout.h>
#include <QtWidgets/qpushbutton.h>
#include <QtWidgets/qlineedit.h>
#include <QtWidgets/qlistwidget.h>
#include <QtWidgets/qformlayout.h>
#include <QtWidgets/qmessagebox.h>
#include <QtWidgets/qtablewidget.h>

#include "service.h"
#include "exceptii.h"
#include "GUIwishlist.h"

#include<vector>
using std::vector;

class Gui : public QWidget {
	friend class GuiWishlist;
private:
	vector<QPushButton*> vectbtn;
	const GuiWishlist& guiWishlist;
	Service& service;

	QHBoxLayout* mainLy = new QHBoxLayout;
	QVBoxLayout* btntip = new QVBoxLayout;

	QListWidget* listaOferte = new QListWidget();
	QListWidget* rezultate = new QListWidget();

	QTableWidget* tabelOferte = new QTableWidget();

	QLineEdit* txtDenumire = new QLineEdit();
	QLineEdit* txtDestinatie = new QLineEdit();
	QLineEdit* txtTip = new QLineEdit();
	QLineEdit* txtPret = new QLineEdit();
	QLineEdit* txtPozitie = new QLineEdit();

	QPushButton* btnAdauga;
	QPushButton* btnSterge;
	QPushButton* btnModifica;
	QPushButton* btnRaport;
	QPushButton* btnCauta;

	QPushButton* btnSorteazaDupaDenumire;
	QPushButton* btnSorteazaDupaDestinatie;
	QPushButton* btnSorteazaDupaTipSiPret;
	
	QPushButton* btnAdaugaWishlist;
	QPushButton* btnFiltreazaDupaPret;
	QPushButton* btnFiltreazaDupaDestinatie;
	QPushButton* btnUndo;
	void initGui();
	void load();
	void connectSignals();
	void curataTextFielduri();

	void adauga();

	/*
	* functia sterge oferta de pe pozitia introdusa
	*/
	void sterge();

	/*
	* functia modifica oferta de pe pozitia introdusa
	*/
	void modifica();

	/*
	* functia cauta oferte dupa denumire, returneaza o oferta cu denumirea introdusa
	*/
	void cauta();

	/*
	* Raport in functie de tip
	*/
	void raport();

	/*
	* 
	*/
	void filtreazaPret();

	/*
	* filtreaza dupa destinatia introdusa, afisand tipurile existente pentru aceasta destinatie
	*/
	void filtreazaDestinatie();


	void sorteazaDenumire();
	void sorteazaDestinatie();
	void sorteazaTipPret();
	void undo();
	void detalii();

	void adaugaWlist();

	void conectButoaneRaport();
	
public:
	Gui(const GuiWishlist& guiWishlist, Service& service);
};
