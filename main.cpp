#include <iostream>
#include "h/graphic.h"
#include "h/saisir.h"
#include "h/biblio.h"
using namespace std;

int main() {
	ResizeConsole(1000, 600);
	int choix;
	t_biblio biblioth�que;
	string menu[MAX_MENU];

	const char* Library;
	Library = "Texte/Biblioth�que.txt";
	const char* Author;
	Author = "Texte/Auteur.txt";

	biblioth�que.nbLivre = 0;
	biblioth�que.nbAuteur = 0;
	choix = 0;
	//Lire les donn�es des fichiers contenant les livres et les auteurs
	ReadAuthorFile(Author, biblioth�que);
	ReadLibrary(Library, biblioth�que);
	do {
			Tri_Bulle(biblioth�que);
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
				Menu_Affichage(biblioth�que);
				break;
			case Ajouter:
				Menu_Ajout(biblioth�que);
				break;
			case Supprimer:
				Menu_Supprimer(biblioth�que);
				break;
			case Rechercher:
				Menu_Rechercher(biblioth�que);
				break;
			case Quitter:
				cout << "A bientot !" << endl;
				break;
		}
	} while (choix != 5);

	//ETAPE METTRE A JOUR LES DONNEES
	WriteLibrary(Library, biblioth�que);
	WriteAuthorFile(Author, biblioth�que);
	system("color 0F");
	return 0;
}