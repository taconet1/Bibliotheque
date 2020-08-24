#include <iostream>
#include "h/graphic.h"
#include "h/saisir.h"
#include "h/biblio.h"
using namespace std;

int main() {
	ResizeConsole(1000, 600);
	int choix;
	t_biblio bibliothèque;
	string menu[MAX_MENU];

	const char* Library;
	Library = "Texte/Bibliothèque.txt";
	const char* Author;
	Author = "Texte/Auteur.txt";

	bibliothèque.nbLivre = 0;
	bibliothèque.nbAuteur = 0;
	choix = 0;
	//Lire les données des fichiers contenant les livres et les auteurs
	ReadAuthorFile(Author, bibliothèque);
	ReadLibrary(Library, bibliothèque);
	do {
			Tri_Bulle(bibliothèque);
			//system("color 0B"); //system("color %"); to see the colors code
			menu[0] = "MENU PRINCIPAL";
			menu[1] = "1: Afficher";
			menu[2] = "2: Ajouter";
			menu[3] = "3: Supprimer";
			menu[4] = "4: Rechercher";
			menu[5] = "5: Quitter";
			choix = Menu(1, 5, menu);

		switch (choix)
			{
			case Afficher:
				Menu_Affichage(bibliothèque);
				break;
			case Ajouter:
				Menu_Ajout(bibliothèque);
				break;
			case Supprimer:
				Menu_Supprimer(bibliothèque);
				break;
			case Rechercher:
				Menu_Rechercher(bibliothèque);
				break;
			case Quitter:
				cout << "A bientot !" << endl;
				break;
		}
	} while (choix != 5);

	//ETAPE METTRE A JOUR LES DONNEES
	WriteLibrary(Library, bibliothèque);
	WriteAuthorFile(Author, bibliothèque);
	system("color 0F");
	return 0;
}