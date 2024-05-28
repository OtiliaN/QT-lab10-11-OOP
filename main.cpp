#include "QtWidgetsApplication.h"
#include <QtWidgets/QApplication>
#include "teste.h"
#include "domain.h"
#include "repo.h"
#include "service.h"
#include "GUI.h"
#include "wishlist.h"
#include <iostream>

using std::cout;
		
int main(int argc, char *argv[])
{	
	Teste teste;
	teste.toateTestele();
	//cout << "Teste finalizate cu succes!";
	//Repo repo;
	RepoFile repo("oferte.txt");
	//RepoProbabilitate repo((float)0.9);
	Validator validator;
	Service service(repo, validator);
	//Console ui(service);
	//ui.run();
	Wishlist wlist;
    QApplication a(argc, argv);
	GuiWishlist gui2(wlist, service);
    Gui gui(gui2, service);
    gui.show();
	gui2.show();
    return a.exec();
}
