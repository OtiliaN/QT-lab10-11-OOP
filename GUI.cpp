#include "gui.h"

Gui::Gui(const GuiWishlist& guiWishlist, Service& service) : guiWishlist{ guiWishlist }, service { service } {
	initGui();
	load();
	connectSignals();
}

void Gui::initGui() {
	setLayout(mainLy);
	mainLy->addWidget(listaOferte);
	mainLy->addWidget(tabelOferte);
	QVBoxLayout* leftLy = new QVBoxLayout;
	QFormLayout* formLy = new QFormLayout;
	formLy->addRow("Denumire", txtDenumire);
	formLy->addRow("Destinatie", txtDestinatie);
	formLy->addRow("Tip", txtTip);
	formLy->addRow("Pret", txtPret);
	formLy->addRow("Introdu pozitia pt stergere/modificare", txtPozitie);

	leftLy->addLayout(formLy);
	btnAdauga = new QPushButton("Adauga");
	btnSterge = new QPushButton("Sterge");
	btnModifica = new QPushButton("Modifica");
	btnRaport = new QPushButton("Raport");
	btnCauta = new QPushButton("Cauta denumire");
	btnSorteazaDupaDenumire = new QPushButton("Sorteaza dupa denumire");
	btnSorteazaDupaDestinatie = new QPushButton("Sorteaza dupa destinatie");
	btnSorteazaDupaTipSiPret = new QPushButton("Sorteaza dupa tip si pret");
	btnFiltreazaDupaPret = new QPushButton("Filtreaza dupa pret");
	btnFiltreazaDupaDestinatie = new QPushButton("Filtreaza dupa destinatie");
	btnAdaugaWishlist = new QPushButton("Adauga in wishlist");
	btnUndo = new QPushButton("Undo");
	QHBoxLayout* btnsLy1 = new QHBoxLayout;
	btnsLy1->addWidget(btnAdauga);
	btnsLy1->addWidget(btnSterge);
	btnsLy1->addWidget(btnModifica);
	btnsLy1->addWidget(btnCauta);
	btnsLy1->addWidget(btnRaport);
	QHBoxLayout* btnsLy2 = new QHBoxLayout();
	btnsLy2->addWidget(btnSorteazaDupaDenumire);
	btnsLy2->addWidget(btnSorteazaDupaDestinatie);
	btnsLy2->addWidget(btnSorteazaDupaTipSiPret);
	QHBoxLayout* btnsLy3 = new QHBoxLayout();
	btnsLy3->addWidget(btnFiltreazaDupaPret);
	btnsLy3->addWidget(btnFiltreazaDupaDestinatie);
	btnsLy3->addWidget(btnAdaugaWishlist);
	btnsLy3->addWidget(btnUndo);
	leftLy->addLayout(btnsLy1);
	leftLy->addLayout(btnsLy2);
	leftLy->addLayout(btnsLy3);
	mainLy->addLayout(leftLy);
	mainLy->addWidget(rezultate);

	auto rp = service.generareRaport(service.getLista());
	for (auto const& t : rp) {
		QPushButton* buton = new QPushButton(QString::fromStdString(t.first));
		vectbtn.push_back(buton);
	}
	for (auto b : vectbtn) {
		btntip->addWidget(b);
	}
	mainLy->addLayout(btntip);
	conectButoaneRaport();
}

void Gui::load() {
	listaOferte->clear();
	const auto& lista = service.getLista();
	for (const auto& oferta : lista) {
		listaOferte->addItem(QString::fromStdString(oferta.getDestinatie()));
	}

	tabelOferte->setColumnCount(4);
	int nr = service.getLista().size();
	tabelOferte->setRowCount(nr);
	tabelOferte->setHorizontalHeaderLabels(QStringList{ "Denumire", "Destinatie", "Tip", "Pret" });
	auto oferte2 = service.getLista();
	for (int i = 0; i < nr; i++) {
		tabelOferte->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(oferte2[i].getDenumire())));
		tabelOferte->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(oferte2[i].getDestinatie())));
		tabelOferte->setItem(i, 2, new QTableWidgetItem(QString::fromStdString(oferte2[i].getTip())));
		tabelOferte->setItem(i, 3, new QTableWidgetItem(QString::number(oferte2[i].getPret())));
	}

}

void Gui::connectSignals() {
	QObject::connect(btnAdauga, &QPushButton::clicked, this, &Gui::adauga);
	QObject::connect(btnSterge, &QPushButton::clicked, this, &Gui::sterge);
	QObject::connect(btnModifica, &QPushButton::clicked, this, &Gui::modifica);
	QObject::connect(btnCauta, &QPushButton::clicked, this, &Gui::cauta);
	QObject::connect(btnRaport, &QPushButton::clicked, this, &Gui::raport);
	QObject::connect(btnFiltreazaDupaPret, &QPushButton::clicked, this, &Gui::filtreazaPret);
	QObject::connect(btnFiltreazaDupaDestinatie, &QPushButton::clicked, this, &Gui::filtreazaDestinatie);
	QObject::connect(btnSorteazaDupaDenumire, &QPushButton::clicked, this, &Gui::sorteazaDenumire);
	QObject::connect(btnSorteazaDupaDestinatie, &QPushButton::clicked, this, &Gui::sorteazaDestinatie);
	QObject::connect(btnSorteazaDupaTipSiPret, &QPushButton::clicked, this, &Gui::sorteazaTipPret);
	QObject::connect(btnUndo, &QPushButton::clicked, this, &Gui::undo);
	QObject::connect(listaOferte, &QListWidget::itemClicked, this, &Gui::detalii);
	QObject::connect(btnAdaugaWishlist, &QPushButton::clicked, this, &Gui::adaugaWlist);
}

void Gui::conectButoaneRaport() {
	for (auto b : vectbtn) {
		QObject::connect(b, &QPushButton::clicked, this, [this, b]() {
			rezultate->clear();
			auto txt = b->text();
			const auto& rp = service.generareRaport(service.getLista());
			for (const auto& o : rp) {
				if (o.first == txt.toStdString()) {
					QMessageBox* msg = new QMessageBox;
					msg->information(this, txt, QString::number(o.second.nr));
				}
			}
			});
	}
}

void Gui::curataTextFielduri() {
	txtDenumire->clear();
	txtDestinatie->clear();
	txtTip->clear();
	txtPret->clear();
	txtPozitie->clear();
}


void Gui::adauga() {
	try {
		auto denumire = txtDenumire->text().toStdString();
		auto destinatie = txtDestinatie->text().toStdString();
		auto tip = txtTip->text().toStdString();
		auto pret = txtPret->text().toFloat();
		const auto& rp = service.generareRaport(service.getLista());
		service.adaugaSrv(denumire, destinatie, tip, pret);
		
		int ok = 0;
		for (const auto& o : rp) {
			if (o.first == tip) {
				ok = 1;
			}
		}
		if (ok == 0) {
			QPushButton* buton = new QPushButton(txtTip->text());
			vectbtn.push_back(buton);
			btntip->addWidget(buton);
			//conectButoaneRaport();
		}
		load();
		curataTextFielduri();
	}
	catch (const ValidatorExceptii) {
		QMessageBox::warning(nullptr, "Warning", "Camp invalid");
	}
	catch (const RepoExceptii& msg2) {
		QMessageBox::warning(nullptr, "Warning", QString::fromStdString(msg2.getMesaj()));
	}
}

void Gui::sterge() {
	try {
		auto pozitie = txtPozitie->text().toInt();
		service.stergeSrv(pozitie);
		load();
		curataTextFielduri();
	}
	catch (const RepoExceptii& msg2) {
		QMessageBox::warning(nullptr, "Warning", QString::fromStdString(msg2.getMesaj()));
	}
}

void Gui::modifica() {
	try {
		auto denumire = txtDenumire->text().toStdString();
		auto destinatie = txtDestinatie->text().toStdString();
		auto tip = txtTip->text().toStdString();
		auto pret = txtPret->text().toFloat();
		auto pozitie = txtPozitie->text().toInt();
		service.modificaSrv(pozitie, denumire, destinatie, tip, pret);
		load();
		curataTextFielduri();
	}
	catch (const ValidatorExceptii) {
		QMessageBox::warning(nullptr, "Warning", "Camp invalid");
	}
	catch (const RepoExceptii& msg2) {
		QMessageBox::warning(nullptr, "Warning", QString::fromStdString(msg2.getMesaj()));
	}
}

void Gui::cauta() {
	try {
		auto& oferta = service.cautaSrv(txtDenumire->text().toStdString());
		txtDenumire->setText(QString::fromStdString(oferta.getDenumire()));
		txtDestinatie->setText(QString::fromStdString(oferta.getDestinatie()));
		txtTip->setText(QString::fromStdString(oferta.getTip()));
		txtPret->setText(QString::number(oferta.getPret()));

	}
	catch (const RepoExceptii& msg2) {
		QMessageBox::warning(nullptr, "Warning", QString::fromStdString(msg2.getMesaj()));
	}
}

void Gui::raport() {
	const auto& rprt = service.generareRaport(service.getLista());
	if (rprt.size()) {
		rezultate->clear();
		rezultate->addItem("Raport (tipuri):");
		for (const auto& oferta : rprt) {
			rezultate->addItem(QString::fromStdString(oferta.first) + ": " + QString::number(oferta.second.nr));
		}
	}
	else {
		QMessageBox::warning(nullptr, "Warning", "Nu exista date!");
	}
}

void Gui::filtreazaPret() {
	auto pret = txtPret->text().toFloat();
	const auto& listaFiltrata = service.filtreazaOferta("z", pret, 2);
	rezultate->clear();
	rezultate->addItem("Lista filtrata dupa pret:");
	if (listaFiltrata.size()) {
		for (const auto& oferta : listaFiltrata) {
			rezultate->addItem(QString::fromStdString(oferta.getDestinatie()));
		}
	}
	else {
		rezultate->addItem("Nu s-au gasit rezultate!");
	}
	curataTextFielduri();
}

void Gui::filtreazaDestinatie() {
	auto destinatie = txtDestinatie->text().toStdString();
	const auto& listaFiltrata = service.filtreazaOferta(destinatie, 1, 1);
	rezultate->clear();
	rezultate->addItem("Lista filtrata dupa destinatie:");
	if (listaFiltrata.size()) {
		for (const auto& oferta : listaFiltrata) {
			rezultate->addItem(QString::fromStdString(oferta.getTip()));
		}
	}
	else {
		rezultate->addItem("Nu s-au gasit rezultate!");
	}
	curataTextFielduri();
}

void Gui::sorteazaDenumire() {
	const auto& listaSortata = service.sortareDupaDenumire();
	rezultate->clear();
	rezultate->addItem("Lista sortata dupa denumire este:");
	if (listaSortata.size()) {
		for (const auto& oferta : listaSortata) {
			rezultate->addItem(QString::fromStdString(oferta.getDestinatie()));
		}
	}
	else {
		rezultate->addItem("Lista este goala!");
	}
}

void Gui::sorteazaDestinatie() {
	const auto& listaSortata = service.sortareDupaDestinatie();
	rezultate->clear();
	rezultate->addItem("Lista sortata dupa destinatie este:");
	if (listaSortata.size()) {
		for (const auto& oferta : listaSortata) {
			rezultate->addItem(QString::fromStdString(oferta.getDestinatie()));
		}
	}
	else {
		rezultate->addItem("Lista este goala!");
	}
}

void Gui::sorteazaTipPret() {
	const auto& listaSortata = service.sortareTipPret();
	rezultate->clear();
	rezultate->addItem("Lista sortata dupa tip si pret este:");
	if (listaSortata.size()) {
		for (const auto& oferta : listaSortata) {
			rezultate->addItem(QString::fromStdString(oferta.getDestinatie()));
		}
	}
	else {
		rezultate->addItem("Lista este goala!");
	}
}

void Gui::undo() {
	service.undo();
	load();
}

void Gui::detalii() {
	auto destinatieOferta = listaOferte->currentItem()->text().toStdString();
	auto oferta = service.cautaSrvDestinatie(destinatieOferta);
	txtDenumire->setText(QString::fromStdString(oferta.getDenumire()));
	txtDestinatie->setText(QString::fromStdString(oferta.getDestinatie()));
	txtTip->setText(QString::fromStdString(oferta.getTip()));
	txtPret->setText(QString::number(oferta.getPret()));
}

void Gui::adaugaWlist() {
	const auto& denumire = txtDenumire->text().toStdString();
	const auto& destinatie = txtDestinatie->text().toStdString();
	const auto& tip = txtTip->text().toStdString();
	auto pret = txtPret->text().toFloat();
	Oferta oferta{ denumire, destinatie, tip, pret };
	guiWishlist.wishlist.adaugaWishlist(oferta);
	guiWishlist.wlist->addItem(QString::fromStdString(oferta.getDestinatie()));
	curataTextFielduri();
}