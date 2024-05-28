#pragma once
#include <QtWidgets/qwidget.h>
#include <QtWidgets/qboxlayout.h>
#include <QtWidgets/qlistwidget.h>
#include <QtWidgets/qpushbutton.h>
#include <QtWidgets/qformlayout.h>
#include <QtWidgets/qlineedit.h>
#include <QtWidgets/qmessagebox.h>
#include "wishlist.h"
#include "GUI.h"
#include "service.h"
#include "exceptii.h"

class Gui;

class GuiWishlist : public QWidget {
	friend class Gui;
private:
	Wishlist& wishlist;
	Service& service;
	QHBoxLayout* mainLy = new QHBoxLayout();
	QListWidget* wlist = new QListWidget();
	QPushButton* btnAdaugaRandom;
	QPushButton* btnGoleste;
	QPushButton* btnExportaHtml;
	QLineEdit* txtExport = new QLineEdit();
	QLineEdit* txtAdaugaRandom = new QLineEdit();
	void initGuiWishlist();
	void connectSignals();

	/*
	* Adauga oferte random.
	*/
	void adaugaRandom();

	/*
	* Exporta in fisier html.
	*/
	void exporta();

	/*
	* Goleste wihslist.
	*/
	void goleste();

public:
	GuiWishlist(Wishlist& wishlist, Service& service);
};