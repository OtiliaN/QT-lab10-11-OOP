#include "GUIwishlist.h"

GuiWishlist::GuiWishlist(Wishlist& wishlist, Service& service) : wishlist{ wishlist }, service{ service } {
	initGuiWishlist();
	connectSignals();
}

void GuiWishlist::initGuiWishlist() {
	setLayout(mainLy);
	mainLy->addWidget(wlist);
	QFormLayout* formLy = new QFormLayout();
	formLy->addRow("Nr. oferte random", txtAdaugaRandom);
	formLy->addRow("Nume fisier", txtExport);
	QVBoxLayout* leftLy = new QVBoxLayout();
	leftLy->addLayout(formLy);
	mainLy->addLayout(leftLy);

	btnAdaugaRandom = new QPushButton("Adauga random");
	btnExportaHtml = new QPushButton("Exporta in fiser HTML");
	btnGoleste = new QPushButton("Goleste");

	QHBoxLayout* btnsLy1 = new QHBoxLayout();
	btnsLy1->addWidget(btnAdaugaRandom);
	btnsLy1->addWidget(btnExportaHtml);
	btnsLy1->addWidget(btnGoleste);
	leftLy->addLayout(btnsLy1);
}

void GuiWishlist::connectSignals() {
	QObject::connect(btnAdaugaRandom, &QPushButton::clicked, this, &GuiWishlist::adaugaRandom);
	QObject::connect(btnExportaHtml, &QPushButton::clicked, this, &GuiWishlist::exporta);
	QObject::connect(btnGoleste, &QPushButton::clicked, this, &GuiWishlist::goleste);
}

void GuiWishlist::adaugaRandom() {
	auto numar = txtAdaugaRandom->text().toInt();
	const auto& lista = service.getLista();
	wishlist.adaugaRandom(lista, numar);
	const auto& wishlistRandom = wishlist.getWishlist();
	for (const auto& oferta : wishlistRandom) {
		wlist->addItem(QString::fromStdString(oferta.getDestinatie()));
	}
}

void GuiWishlist::exporta() {
	auto fileName = txtExport->text().toStdString();
	wishlist.exportHTML(fileName);
}

void GuiWishlist::goleste() {
	wishlist.golesteWishlist();
	const auto& wish = wishlist.getWishlist();
	if (wish.size() == 0) {
		wlist->clear();
	}
	else {
		QMessageBox::warning(nullptr, "Warning", "Nu s-a putut goli wishlist-ul!");
	}

}