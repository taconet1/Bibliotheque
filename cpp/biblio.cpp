#include <iostream>
#include "../h/graphic.h"
#include "../h/saisir.h"
#include "../h/biblio.h"
using namespace std;

//==================== SAISIR ====================//

/////////////////////////////////////////////////////
//
// Procédure permettant d'ajouter un genre au livre
// Entrée : structure genre
// Sortie : structure genre
//
/////////////////////////////////////////////////////
void Saisir_Genre(t_genre& G) {
	char rep;
	int pos;
	string genre;

	rep = 'o';
	pos = -1;
	do {
		if (G.nbGenre == MAX_GENRE) {
			cout << "Impossible !\nLe livre ne peut avoir que " << MAX_GENRE << " genres\n";
			break;
		}
		else
		{
			cin.ignore(MAX, '\n');
			genre = Saisir_Chaine("Entrer un genre : ");
			if (G.nbGenre != 0) {
				pos = Recherche_Genre_Livre(G, genre);
				if (pos != -1) {
					cout << "Le livre possede deja ce genre\n";
				}
			}
			else {
				cout << "Un genre vient d'etre ajoute\n";
				G.tab_genres[G.nbGenre] = genre;
				G.nbGenre += 1;
				rep = Verif_Reponse("Encore un genre ? o/n : ", 'o', 'n');
			}
		}
	} while (rep == 'o' && G.nbGenre != MAX_GENRE && pos == -1);
}

////////////////////////////////////////////
//
// Procédure permettant de saisir un livre
// Entrée : RIEN
// Sortie : structure livre
//
/////////////////////////////////////////////
void Saisir_Livre(t_livre& monLivre) {
	char rep;
	bool chiffre_ok = false;

	do {
		monLivre.code = Controle_Nombre_Caractere("Entrer le code ISBN du livre : ", 13, "chiffres");
		chiffre_ok = Verif_Chaine_Chiffre(monLivre.code);
	} while (chiffre_ok == false);
	cin.ignore(MAX_IGNORE, '\n');
	monLivre.titre = Saisir_Chaine("Entrer le titre du livre : ");
	monLivre.titre[0] = Majuscule_Caractere(monLivre.titre[0]);
	monLivre.genre.nbGenre = 0;
	Saisir_Genre(monLivre.genre);
	rep = Verif_Reponse("Est-ce une version originale ou traduite? o/t : ", 'o', 't');
	if (rep == 'o') {
		monLivre.version = "VO";
	}
	else {
		monLivre.version = "VT";
	}
	cin.ignore(MAX_IGNORE, '\n');
	monLivre.langue = Saisir_Chaine("Entrer la langue du livre : ");
}

///////////////////////////////////////////////////////////
//
// Procédure permettant de saisir et vérifier 
// la cohérence de la date de parution du livre
// Entrée : structure bibliothèque, structure livre,
// Sortie : structure livre
//
///////////////////////////////////////////////////////////
void Saisir_Date_Livre(t_biblio maBiblio, t_livre& monLivre) {
	bool correct;
	int position_auteur;
	char rep;

	position_auteur = Recherche_Code_Auteur(maBiblio, monLivre.code_auteur);
	do {
		rep = Verif_Reponse("\nSi vous ne connaissez que l'annee de parution, entrez 'o' sinon entrez 'n' : ", 'o', 'n');
		if (rep == 'o') {
			monLivre.date.jour = -1;
			monLivre.date.mois = -1;
			cout << "Entrer l'annee de parution : "; cin >> monLivre.date.annee;
			correct = true;
		}
		else
		{
			cout << endl << "Entrer la date de parution du livre : " << endl;
			SaisirDate(monLivre.date.jour, monLivre.date.mois, monLivre.date.annee);
			correct = VerifDate(monLivre.date.jour, monLivre.date.mois, monLivre.date.annee);
			if (correct == false) {
				cout << "La date saisie n'existe pas !" << endl;
			}
		}
		//Si le livre possede un auteur : vérifier la cohérence de l'existence de l'auteur et la parution du livre
		if (correct == true && position_auteur != -1 && monLivre.date.annee < maBiblio.auteur[position_auteur].naissance.annee + 5)
		{
			correct = false;
			cout << "Impossible !" << endl;
		}
	} while (correct == false); cout << endl;
}

//==================== SAISIR ====================//


//==================== FICHIER LECTURE ====================//

/////////////////////////////////////
//
// Fonction permettant de tester 
// si un fichier en lecture est vide
// Entrée : chaîne
// Retour : booléen
//
/////////////////////////////////////
bool TestReadVide(string filename) {
	bool check;
	int c;
	ifstream file;

	check = true;
	file.open(filename, ios::in);
	if (file.fail() == true) {
		cout << "Erreur d'ouverture de fichier : " << filename << endl;
	}
	else {
		file >> c;
		if (c != -858993460) {
			check = false;
		}
		file.close();
	}
	return check;
}

///////////////////////////////////////////////////
//
// Procédure permettant de lire des données 
// d'un auteur d'un fichier
// Entrée : fichier, structure auteur
// Sortie : fichier, structure auteur
//
///////////////////////////////////////////////////
void ReadAuthorLine(ifstream& file, t_auteur& A) {
	getline(file, A.nom, ';');
	getline(file, A.prenom, ';');
	getline(file, A.nationalite, ';');
	file >> A.naissance.jour; file.seekg(1, file.cur);
	file >> A.naissance.mois; file.seekg(1, file.cur);
	file >> A.naissance.annee; file.seekg(1, file.cur);
	file >> A.deces.jour; file.seekg(1, file.cur);
	file >> A.deces.mois; file.seekg(1, file.cur);
	file >> A.deces.annee; file.seekg(1, file.cur);
	file >> A.nbLivres; file.seekg(1, file.cur);
	getline(file, A.code_auteur);
}

////////////////////////////////////////////////////////////
//
// Procédure permettant de lire chaque ligne d'un fichier
// Entrée : chaine
// Sortie : structure bibliothèque
//
////////////////////////////////////////////////////////////
void ReadAuthorFile(string filename, t_biblio& B) {
	int i;
	bool vide;
	ifstream file;

	vide = TestReadVide(filename);
	if (vide == true) { cout << "La liste d'auteur est vide\n"; }
	else {
		file.open(filename, ios_base::in);
		if (file.fail() == true) {
			cout << "Fichiers introuvables !\n";
		}
		else {
			i = 0;
			while (!file.eof() && B.nbAuteur != MAX)
			{
				ReadAuthorLine(file, B.auteur[i]);
				i += 1;
				B.nbAuteur = i;
			}
			file.close();
		}
	}
}

//////////////////////////////////////////////////////
//
// Procédure permettant de lire les notes d'un livre
// d'un fichier
// Entrée : fichier
// Sortie : structure note
//
//////////////////////////////////////////////////////
void ReadNoteLine(ifstream& file, t_note& N) {
	int i;
	float x;
	file >> N.nbNote; file.ignore(1);
	if (N.nbNote != 0) {
		for (i = 0; i <= N.nbNote - 1; i++) {
			file >> x;
			N.tab_notes.push_back(x);
		}file.seekg(1, file.cur);
		file >> N.moyenne;
	}
	else {
		file.seekg(5, file.cur);
	}
}

///////////////////////////////////////////////////
//
// Procédure permettant de lire la liste de genres
// d'un livre
// Entrée : fichier
// Sortie : structure genre
//
///////////////////////////////////////////////////
void ReadGenreLine(ifstream& file, t_genre& G) {
	int i;

	file >> G.nbGenre; file.ignore(1);
	if (G.nbGenre > MAX_GENRE) {
		G.nbGenre = MAX_GENRE;
	}
	for (i = 0; i <= G.nbGenre - 1; i++) {
		if (i == G.nbGenre - 1) {
			getline(file, G.tab_genres[i], ';');
		}
		else {
			getline(file, G.tab_genres[i], ',');
		}
	}
}

/////////////////////////////////////////////////
//
// Procédure permettant de lire les données 
// d'un livre d'un fichier
// Entrée : fichier
// Sortie : structure livre
//
/////////////////////////////////////////////////
void ReadBookLine(ifstream& file, t_livre& L) {
	getline(file, L.code, ';');
	getline(file, L.version, ';');
	getline(file, L.titre, ';');
	ReadGenreLine(file, L.genre);
	getline(file, L.langue, ';');
	getline(file, L.code_auteur, ';');
	file >> L.date.jour; file.seekg(1, file.cur);
	file >> L.date.mois;  file.seekg(1, file.cur);
	file >> L.date.annee;  file.seekg(1, file.cur);
	getline(file, L.editeur, ';');
	file >> L.pages; file.seekg(1, file.cur);
	ReadNoteLine(file, L.note); file.seekg(1, file.cur);
	getline(file, L.etat);
}

///////////////////////////////////////////////
//
// Procédure permettant de lire les données 
// d'une bibliothèque d'un fichier
// Entrée : chaîne, structure bibliothèque
// Sortie : structure bibliothèque
//
///////////////////////////////////////////////
void ReadLibrary(string filename, t_biblio& B) {
	int i;
	bool vide;
	ifstream file;

	vide = TestReadVide(filename);
	if (vide == true) { cout << "La bibliotheque est vide\n"; }
	else {
		file.open(filename, ios_base::in);
		if (file.fail() == true) {
			cout << "Fichiers introuvables !\n";
		}
		else {
			i = 0;
			file._Seekbeg;
			while (!file.eof() && B.nbLivre != MAX) {
				ReadBookLine(file, B.livre[i]);
				i += 1;
				B.nbLivre = i;
			}
			file.close();
		}
	}
}

//==================== FICHIER LECTURE ====================//


//==================== FICHIER ECRITURE ====================//

/////////////////////////////////////////////
//
// Procédure permettant d'écrire les données 
// d'un auteur dans un fichier
// Entrée : structure auteur
// Sortie : fichier
//
/////////////////////////////////////////////
void WriteAuthorLine(ofstream& file, t_auteur A) {
	file._Seekend;
	file << A.nom << ";" << A.prenom << ";" << A.nationalite << ";";
	file << A.naissance.jour << "/" << A.naissance.mois << "/" << A.naissance.annee << ";";
	file << A.deces.jour << "/" << A.deces.mois << "/" << A.deces.annee << ";" << A.nbLivres << ";";
	file << A.code_auteur;
}

///////////////////////////////////////////
//
// Procédure permettant d'écrire une liste
// d'auteurs dans un fichier
// Entrée : chaine, structure bibliothèque
// Sortie : fichier
//
///////////////////////////////////////////
void WriteAuthorFile(string filename, t_biblio B) {
	int i;
	ofstream file;

	file.open(filename, ios::out);
	if (file.fail() == true) {
		cout << "Erreur !\nLes nouvelles donnees ne seront pas sauvegardees !\n";
	}
	else {
		for (i = 0; i <= B.nbAuteur - 1; i++) {
			if (i != 0) {
				file << endl;
			}
			WriteAuthorLine(file, B.auteur[i]);
		}
		file.close();
	}
}

//////////////////////////////////////////////
//
// Procédure permettant d'écrire les notes
// du livre dans un fichier
// Entrée : structure note
// Sortie : fichier
//
//////////////////////////////////////////////
void WriteNoteLine(ofstream& file, t_note N) {
	int i;

	file << N.nbNote << ";";
	if (N.nbNote != 0) {
		for (i = 0; i <= N.nbNote - 1; i++) {
			if (i == N.nbNote - 1) { file << N.tab_notes[i]; }
			else { file << N.tab_notes[i] << " "; }
		}
		file << ";" << N.moyenne << ";";
	}
	else { file << -1 << ";" << -1 << ";"; }
}

///////////////////////////////////////////////
//
// Procédure permettant d'écrire une liste
// de genres d'un livre dans un fichier
// Entrée : structure genre
// Sortie : fichier
//
///////////////////////////////////////////////
void WriteGenreLine(ofstream& file, t_genre G) {
	int i;
	file << G.nbGenre << ";";
	for (i = 0; i <= G.nbGenre - 1; i++) {
		if (i == G.nbGenre - 1) {
			file << G.tab_genres[i] << ";";
		}
		else {
			file << G.tab_genres[i] << ",";
		}
	}
}

///////////////////////////////////////////////
//
// Procédure permettant d'écrire les données 
// d'un livre dans un fichier
// Entrée : structure livre
// Sortie : fichier
//
///////////////////////////////////////////////
void WriteBookLine(ofstream& file, t_livre L) {
	file._Seekend;
	file << L.code << ';';
	file << L.version << ";";
	file << L.titre << ";";
	WriteGenreLine(file, L.genre);
	file << L.langue << ";" << L.code_auteur << ";";
	file << L.date.jour << "/" << L.date.mois << "/" << L.date.annee << ";";
	file << L.editeur << ";" << L.pages << ";";
	WriteNoteLine(file, L.note);
	file << L.etat;
}

////////////////////////////////////////////
//
// Procédure permettant d'écrire une liste 
// de livres dans un fichier
// Entrée : chaîne, structure bibliothèque
// Sortie : fichier
//
////////////////////////////////////////////
void WriteLibrary(string filename, t_biblio B) {
	int i;
	ofstream file;

	file.open(filename, ios::out);
	if (file.fail() == true) {
		cout << "Erreur !\nLes nouvelles donnees ne seront pas sauvegardees !\n";
	}
	else
	{
		for (i = 0; i <= B.nbLivre - 1; i++) {
			WriteBookLine(file, B.livre[i]);
			if (i != B.nbLivre - 1) {
				file << endl;
			}
		}
		file.close();
	}
}

//==================== FICHIER ECRITURE ====================//


//==================== DIVERS ====================//

////////////////////////////////////////////////////////////
//
// Fonction permettant de convertir une variable en chaîne
// Entrée : variable
// Retour : chaîne
//
////////////////////////////////////////////////////////////
template<typename toConvert>
string toString(toConvert value)
{
	ostringstream oss;
	oss << value;
	return oss.str();
}

//////////////////////////////////////////////////////////////
//
// Fonction permettant de renvoyer une lettre en majuscule
// Entrée : caractère
// Retour : caractère en majuscule
//
//////////////////////////////////////////////////////////////
char Majuscule_Caractere(char lettre) {
	if (lettre >= 'a' && lettre <= 'z') {
		lettre = lettre + 'A' - 'a';
	}return lettre;
}

/////////////////////////////////////////////////////////////////////
//
// Fonction permettant d'afficher un menu et effectuer un choix
// Entrée : entier min et max, tableau chaîne menu
// Retour : entier choix
//
/////////////////////////////////////////////////////////////////////
int Menu(int minchoix, int maxchoix, string menu[MAX_MENU]) {
	int choix, i;

	do {
		Gotoxy(58, 2);
		cout << "==================== " << menu[0] << " ====================";
		for (i = 1; i <= maxchoix; i++) {
			Gotoxy(58, 2 + i);
			cout << menu[i];
		}
		Gotoxy(58, maxchoix + 3);
		cout << "=========================================================";
		Gotoxy(58, maxchoix + 5);
		cout << "Entrer votre choix : "; cin >> choix; 	system("cls");
		if (choix < minchoix || choix > maxchoix) {
			Gotoxy(58, maxchoix + 6);
			cout << "Entrer une valeur entre " << minchoix << " et " << maxchoix << endl;
		}
	} while (choix < minchoix || choix > maxchoix);
	return choix;
}

////////////////////////////////////////////////////////////
//
// Fonction permettant de vérifier la cohérence d'une date
// Entrée : 3 entiers (jour, mois, année)
// Retour : booléen
//
////////////////////////////////////////////////////////////
bool VerifDate(int j, int m, int a) {
	bool bissextile, trente_jour, trente_un_jour, fevrier_ok;
	bool existe;

	existe = false;
	bissextile = (a % 4 == 0 && a % 100 != 0) || (a % 400 == 0);
	fevrier_ok = (bissextile && j <= 29) || (!bissextile && j <= 28);
	trente_jour = (j <= 30) && (m == 4 || m == 6 || m == 9 || m == 11);
	trente_un_jour = (j <= 30) && (m == 1 || m == 3 || m == 5 || m == 7 || m == 8 || m == 10 || m == 12);

	if (bissextile || trente_jour || trente_un_jour || fevrier_ok)
	{
		existe = true;
	}return existe;
}

////////////////////////////////////////////////////////////////
//
// Fonction permettant de créer un code unique pour un auteur
// Entrée : structure auteur
// Retour : chaîne code auteur
//
////////////////////////////////////////////////////////////////
string Code_ID_Auteur(t_auteur monAuteur) {
	string code;

	//Code composé de : 1ère lettre nom + jour naissance 
	//					+ 1ère lettre prénom + 1ère lettre nationalité 
	//					+ 2ème lettre nom + 2ème lettre nationalité 
	//					+ 2ème lettre prénom + mois naissance
	code = monAuteur.nom[0] + toString(monAuteur.naissance.jour)
		+ monAuteur.prenom[0] + monAuteur.nationalite[0]
		+ monAuteur.nom[1] + monAuteur.nationalite[1]
		+ monAuteur.prenom[1] + toString(monAuteur.naissance.mois);
	return code;
}

////////////////////////////////////////////////////////
//
// Procédure permettant d'emprunter ou rendre un livre
// Entrée : structure bibliothèque, 
//			chaîne état livre, entier position livre
// Sortie : structure bibliothèque
//
/////////////////////////////////////////////////////////
void Emprunt_Rendre(t_biblio& maBiblio, string disponibilite, int sa_position) {
	if (sa_position >= 0 && maBiblio.livre[sa_position].etat != disponibilite) {
		maBiblio.livre[sa_position].etat = disponibilite;
		cout << "Le livre est maintenant a l'etat " << disponibilite << endl << endl;
		Aff_Livre(maBiblio, maBiblio.livre[sa_position]);
	}
	else if (sa_position >= 0 && maBiblio.livre[sa_position].etat == disponibilite) {
		cout << "Impossible ! Le livre est deja a l'etat " << disponibilite << endl;
	}
}

//////////////////////////////////////////////////////////////////
//
// Procédure permettant de calculer la moyenne de note d'un livre
// Entrée : structure note
// Sortie : structure note
//
//////////////////////////////////////////////////////////////////
void Note_Livre(t_note& uneNote) {
	float moyenne, note;
	int i, taille;

	moyenne = 0;
	note = Saisir_Decimal("Entrer une note entre 0 et 5 : ", 0, 5);
	uneNote.tab_notes.push_back(note);
	taille = uneNote.tab_notes.size();
	for (i = 0; i <= taille - 1; i++) {
		moyenne = moyenne + uneNote.tab_notes[i];
	}
	uneNote.nbNote = taille;
	moyenne = moyenne / uneNote.tab_notes.size();
	uneNote.moyenne = moyenne;
}

//////////////////////////////////////////////////
//
// Procédure permettant de trier une bibliothèque
// par ordre alphabétique
// Entrée : structure bibliothèque
// Sortie : structure bibliothèque
//
//////////////////////////////////////////////////
void Tri_Bulle(t_biblio& B) {
	int i;
	t_auteur tempo;
	t_livre buffer;
	bool exchange, exg;

	exchange = true;
	while (exchange && B.nbAuteur > 0) {
		exchange = false;
		for (i = 0; i <= B.nbAuteur - 2; i++) {
			if (B.auteur[i].nom > B.auteur[i + 1].nom)
			{
				tempo = B.auteur[i];
				B.auteur[i] = B.auteur[i + 1];
				B.auteur[i + 1] = tempo;
				exchange = true;
			}
		}
	}
	exg = true;
	while (exg && B.nbLivre > 0) {
		exg = false;
		for (i = 0; i <= B.nbLivre - 2; i++) {
			if (B.livre[i].titre > B.livre[i + 1].titre)
			{
				buffer = B.livre[i];
				B.livre[i] = B.livre[i + 1];
				B.livre[i + 1] = buffer;
				exg = true;
			}
		}
	}
}

//==================== DIVERS ====================//


//==================== INITIALISER ====================//

/*////////////////////////////////////////////////////
//
// Fonction permettant d'initialiser un nombre à 0
// Entrée : nombre
// Retour : nombre nul
//
////////////////////////////////////////////////////
template<typename Type>
Type Init_Nombre(Type value) {
	value = NULL;
	return value;
}

////////////////////////////////////////////////
//
// Fonction permettant d'initialiser une chaîne
// Entrée : chaîne
// Retour : chaîne
//
////////////////////////////////////////////////
string Init_Chaine(string chaine) {
	chaine = "";
	return chaine;
}*/

///////////////////////////////////////////////
//
// Procédure permettant d'initialiser une date
// Entrée : structure date
// Sortie : structure date
//
///////////////////////////////////////////////
void Init_Date(t_date& maDate) {
	maDate.jour = -1;
	maDate.mois = -1;
	maDate.annee = -1;
}

//==================== INITIALISER ====================//


//==================== AFFICHAGE ====================//

//////////////////////////////////////////////
//
// Procédure permettant d'afficher la liste 
// des genres d'un livre
// Entrée : structure genre
// Sortie : RIEN
//
//////////////////////////////////////////////
void Aff_Genre(t_genre G) {
	int i;

	cout << "Genre : ";
	for (i = 0; i <= G.nbGenre - 1; i++) {
		if (G.nbGenre == 1) {
			cout << G.tab_genres[i];
		}
		else {
			cout << endl << " - " << G.tab_genres[i];
		}
	}
}

////////////////////////////////////////////////////////////////
//
// Procédure permettant d'afficher les informations d'un livre
// Entrée : structure bibliothèque et livre
// Sortie : RIEN 
//
////////////////////////////////////////////////////////////////
void Aff_Livre(t_biblio maBiblio, t_livre monLivre) {
	int position;
	cout << "Titre : " << monLivre.titre << endl;
	Aff_Genre(monLivre.genre);
	cout << endl << "Langue : " << monLivre.langue;
	//Version
	if (monLivre.version == "VO") {
		cout << " (version originale)" << endl;
	}
	else {
		cout << " (version traduite)" << endl;
	}
	//Auteur
	position = Recherche_Code_Auteur(maBiblio, monLivre.code_auteur);
	if (position != -1) {
		if (monLivre.version == "VO") {
			cout << "Auteur : " << maBiblio.auteur[position].nom << " " << maBiblio.auteur[position].prenom << endl;
		}
		else {
			cout << "Traducteur : " << maBiblio.auteur[position].nom << " " << maBiblio.auteur[position].prenom << endl;
		}
	}
	else {
		cout << "Auteur : " << endl;
	}
	//Date parution
	if (monLivre.date.jour == -1 && monLivre.date.mois == -1) { cout << "Date de parution : " << monLivre.date.annee << endl; }
	else { cout << "Date de parution : " << monLivre.date.jour << "/" << monLivre.date.mois << "/" << monLivre.date.annee << endl; }
	//Editeur
	if (monLivre.editeur == "inconnue") { cout << "Edition : " << endl; }
	else { cout << "Edition : " << monLivre.editeur << endl; }
	cout << "Pages : " << monLivre.pages << endl;
	//Note critique
	if (monLivre.note.nbNote > 0) {
		cout << "Note : " << monLivre.note.moyenne << endl;
	}
	else { cout << "Note : pas de note\n"; }
	cout << "Etat : " << monLivre.etat << endl;
	cout << "ISBN : " << monLivre.code << endl;
}

//////////////////////////////////////////////////////////////////
//
// Procédure permettant d'afficher les livres de la bibliothèque
// Entrée : structure / données de la bibliothèque
// Sortie : RIEN
//
//////////////////////////////////////////////////////////////////
void Aff_desLivres(t_biblio maBiblio) {
	int i;

	for (i = 0; i <= maBiblio.nbLivre - 1; i++) {
		cout << endl << "Livre numero " << i << endl << endl;
		Aff_Livre(maBiblio, maBiblio.livre[i]);
		cout << endl << "---------------------------------------------" << endl;
	}
}

////////////////////////////////////////////////////////////////
//
// Procédure permettant d'afficher les informations d'un auteur
// Entrée : structure auteur
// Sortie : RIEN
//
////////////////////////////////////////////////////////////////
void Aff_Auteur(t_auteur monAuteur) {
	cout << "Nom : " << monAuteur.nom << endl;
	cout << "Prenom : " << monAuteur.prenom << endl;
	cout << "Nationalite : " << monAuteur.nationalite << endl;
	cout << "Naissance : " << monAuteur.naissance.jour << "/" << monAuteur.naissance.mois << "/" << monAuteur.naissance.annee << endl;
	if (monAuteur.deces.jour == -1 && monAuteur.deces.mois == -1 && monAuteur.deces.annee == -1) {
		cout << "Deces :" << endl;
	}
	else {
		cout << "Deces : " << monAuteur.deces.jour << "/" << monAuteur.deces.mois << "/" << monAuteur.deces.annee << endl;
	}
	cout << "Code : " << monAuteur.code_auteur << endl;
	cout << "Nombre de livres : " << monAuteur.nbLivres << endl;
}

/////////////////////////////////////////////////////////////////
//
// Procédure permettant d'afficher les auteurs de la bibliothèque
// Entrée : structure bibliothèque
// Sortie : RIEN
//
/////////////////////////////////////////////////////////////////
void Aff_desAuteurs(t_biblio maBiblio) {
	int i;

	for (i = 0; i <= maBiblio.nbAuteur - 1; i++) {
		cout << endl << "Auteur numero " << i << endl;
		Aff_Auteur(maBiblio.auteur[i]);
		cout << endl << "---------------------------------------------" << endl;
	}
}

//////////////////////////////////////////////////////////
//
// Procédure permettant d'afficher les livres d'un auteur
// Entrée : structure bibliothèque
// Sortie : RIEN
//
//////////////////////////////////////////////////////////
void Aff_Livres_Auteur(t_biblio bibliothèque) {
	string nom, prenom, code;
	int i, position_auteur, nombre;

	nombre = 0;
	Saisir_2_Chaines("Entrer le nom de l'auteur : ", nom, "Entrer le prenom de l'auteur : ", prenom);
	position_auteur = Recherche_Auteur_Meme_Nom_Prenom(bibliothèque, nom, prenom);

	if (position_auteur != -1) {
		code = bibliothèque.auteur[position_auteur].code_auteur;
		if (bibliothèque.auteur[position_auteur].nbLivres == 0) {
			cout << "L'auteur n'a aucun livre" << endl;
		}
		else {
			cout << "Voici ses livres : \n";
			for (i = 0; i <= bibliothèque.nbLivre - 1; i++) {
				if (bibliothèque.livre[i].code_auteur == code) {
					cout << endl << "Livre numero : " << nombre << endl << endl;
					nombre += 1;
					Aff_Livre(bibliothèque, bibliothèque.livre[i]);
					cout << endl << "---------------------------------------------" << endl;
				}
			}
		}
	}
}

///////////////////////////////////////////////
//
// Procédure permettant d'afficher des livres 
// selon un genre recherché
// Entrée : structure bibliothèque
// Sortie : RIEN
//
///////////////////////////////////////////////
void Aff_Livres_Genre(t_biblio bibliothèque) {
	string chaine;
	int i, nombre, k;

	cin.ignore(MAX_IGNORE, '\n');
	chaine = Saisir_Chaine("Entrer le genre que vous recherchez : ");
	nombre = 0;
	for (i = 0; i <= bibliothèque.nbLivre - 1; i++) {
		for (k = 0; k <= bibliothèque.livre[i].genre.nbGenre - 1; k++) {
			if (_stricmp(bibliothèque.livre[i].genre.tab_genres[k].c_str(), chaine.c_str()) == 0) {
				cout << endl << "Livre numero : " << i << endl << endl;
				Aff_Livre(bibliothèque, bibliothèque.livre[i]);
				cout << endl << "---------------------------------------------" << endl;
				nombre = nombre + 1;
			}
		}
	}
	if (nombre == 0) {
		cout << "Aucun livre n'appartient a ce genre" << endl;
	}
}

///////////////////////////////////////////////
//
// Procédure permettant d'afficher des livres 
// selon une langue recherchée
// Entrée : structure bibliothèque
// Sortie : RIEN
//
///////////////////////////////////////////////
void Aff_Livres_Langue(t_biblio bibliothèque) {
	string chaine;
	int i, nombre;

	cin.ignore(MAX_IGNORE, '\n');
	chaine = Saisir_Chaine("Entrer la langue que vous recherchez : ");
	nombre = 0;
	for (i = 0; i <= bibliothèque.nbLivre - 1; i++) {
		if (_stricmp(bibliothèque.livre[i].langue.c_str(), chaine.c_str()) == 0) {
			cout << endl << "Livre numero : " << i << endl << endl;
			Aff_Livre(bibliothèque, bibliothèque.livre[i]);
			cout << endl << "---------------------------------------------" << endl;
			nombre = nombre + 1;
		}
	}
	if (nombre == 0) {
		cout << "Aucun livre n'est ecrit dans cette langue" << endl;
	}
}

///////////////////////////////////////////////
//
// Procédure permettant d'afficher des livres
// selon une lettre recherchée
// Entrée : structure bibliothèque
// Sortie : RIEN
//
///////////////////////////////////////////////
void Aff_Livres_Lettre(t_biblio maBiblio) {
	int i, nombre;
	char tempon; // Le premier caractère du titre ne sera pas modifié
	char lettre_recherche;

	nombre = 0;
	lettre_recherche = Saisir_Caractere("Entrer un caractere : ");
	lettre_recherche = Majuscule_Caractere(lettre_recherche);
	for (i = 0; i <= maBiblio.nbLivre - 1; i++) {
		tempon = maBiblio.livre[i].titre[0];
		tempon = Majuscule_Caractere(tempon);
		if (tempon == lettre_recherche) {
			cout << endl << "Livre numero : " << i << endl << endl;
			Aff_Livre(maBiblio, maBiblio.livre[i]);
			cout << endl << "---------------------------------------------" << endl;
			nombre = nombre + 1;
		}
	}

	if (nombre == 0) {
		cout << "Aucun livre ne commence par la lettre " << lettre_recherche << endl;
	}
}

///////////////////////////////////////////////////////////
//
// Procédure permettant d'afficher tous les auteurs selon
// le nom ou prénom distinct recherché
// Entrée : structure bibliothèque
// Sortie : RIEN
//
///////////////////////////////////////////////////////////
void Aff_desAuteurs_NouP(t_biblio maBiblio) {
	int i, nombre;
	char rep;
	string chaine;

	nombre = -1;
	rep = Verif_Reponse("Nom ou Prenom? n/p : ", 'n', 'p');
	cin.ignore(MAX_IGNORE, '\n');
	chaine = Saisir_Chaine("Saisissez : ");
	for (i = 0; i <= maBiblio.nbAuteur - 1; i++) {
		if (rep == 'n' && _stricmp(maBiblio.auteur[i].nom.c_str(), chaine.c_str()) == 0) {
			cout << endl << "Auteur numero " << i << endl;
			Aff_Auteur(maBiblio.auteur[i]);
			cout << endl << "---------------------------------------------" << endl;
			nombre += 1;
		}
		else if (rep == 'p' && _stricmp(maBiblio.auteur[i].prenom.c_str(), chaine.c_str()) == 0) {
			cout << endl << "Auteur numero " << i << endl;
			Aff_Auteur(maBiblio.auteur[i]);
			cout << endl << "---------------------------------------------" << endl;
			nombre += 1;
		}
	}
	if (nombre == -1) { cout << "Aucun auteur trouve !\n"; }
}

//////////////////////////////////////////////////////
//
// Procédure permettant d'afficher des auteurs selon 
// la nationalite recherche
// Entrée : structure bibliothèque
// Sortie : RIEN
//
//////////////////////////////////////////////////////
void Aff_Auteurs_Nationalite(t_biblio maBiblio) {
	int i, nombre;
	string chaine;

	nombre = -1;
	cin.ignore(MAX_IGNORE, '\n');
	chaine = Saisir_Chaine("Entrer la nationalite : ");
	for (i = 0; i <= maBiblio.nbAuteur - 1; i++) {
		if (_stricmp(maBiblio.auteur[i].nationalite.c_str(), chaine.c_str()) == 0) {
			cout << endl << "Auteur numero " << i << endl << endl;
			Aff_Auteur(maBiblio.auteur[i]);
			cout << endl << "---------------------------------------------" << endl;
			nombre += 1;
		}
	}
	if (nombre == -1) { cout << "Aucun auteur trouve !\n"; }
}

/////////////////////////////////////////////////////////////////
//
// Procédure permettant d'afficher des auteurs nés ou décédés
// dans un intervalle d'année choisie
// Entrée : structure bibliothèque
// Sortie : RIEN
//
/////////////////////////////////////////////////////////////////
void Aff_Auteurs_Annee(t_biblio maBiblio) {
	int i, an1, an2, nombre;

	nombre = -1;
	cout << "Entrer la premiere marge d'annee : ";  cin >> an1;
	an2 = Saisir_Entier_Sup_Eg("Entrer la deuxieme marge d'annee : ", an1); cout << endl;
	for (i = 0; i <= maBiblio.nbAuteur - 1; i++) {
		if ((maBiblio.auteur[i].naissance.annee >= an1 && maBiblio.auteur[i].naissance.annee <= an2)
			|| (maBiblio.auteur[i].deces.annee >= an1 && maBiblio.auteur[i].deces.annee <= an2)) {
			cout << endl << "Auteur numero " << i << endl;
			Aff_Auteur(maBiblio.auteur[i]);
			cout << endl << "---------------------------------------------" << endl;
			nombre += 1;
		}
	}
	if (nombre == -1) { cout << "Aucun auteur trouve !\n"; }
}

////////////////////////////////////////////////////
//
// Procédure permettant d'afficher des livres 
// selon la version recherchée
// Entrée : structure bibliothèque, chaîne
// Sortie : RIEN
//
////////////////////////////////////////////////////
void Aff_Livres_Version(t_biblio B, string version) {
	int i, nombre;

	nombre = 0;
	for (i = 0; i <= B.nbLivre - 1; i++) {
		if (_stricmp(B.livre[i].version.c_str(), version.c_str()) == 0) {
			cout << endl << "Livre numero : " << i << endl << endl;
			Aff_Livre(B, B.livre[i]);
			cout << endl << "---------------------------------------------" << endl;
			nombre = nombre + 1;
		}
	}
	if (nombre == 0) {
		cout << "Aucun livre trouve !\n";
	}
}

//==================== AFFICHAGE ====================//


//==================== RECHERCHE ====================//

/////////////////////////////////////////////////////////////
//
// Fonction permettant de rechercher un auteur par son code
// Entrée : structure bibliothèque, chaîne code recherché
// Retour : entier position auteur
//
/////////////////////////////////////////////////////////////
int Recherche_Code_Auteur(t_biblio maBib, string code_recherche) {
	int position, i;

	position = -1;
	for (i = 0; i <= maBib.nbAuteur - 1; i++) {
		if (maBib.auteur[i].code_auteur == code_recherche) {
			position = i;
			break;
		}
	}
	return position;
};

/////////////////////////////////////////////////////////////////////
//
// Fonction permettant de compter le nombre d'auteurs ayant le même
// nom et prénom et de les afficher
// Entrée : structure bibliothèque, chaînes nom et prénom
// Retour : entier position auteur
//
/////////////////////////////////////////////////////////////////////
int Recherche_Auteur_Meme_Nom_Prenom(t_biblio maBiblio, string nom_recherche, string prenom_recherche) {
	int i, position_auteur;
	char reponse;

	position_auteur = -1;
	for (i = 0; i <= maBiblio.nbAuteur - 1; i++) {
		if (_stricmp(maBiblio.auteur[i].nom.c_str(), nom_recherche.c_str()) == 0
			&& _stricmp(maBiblio.auteur[i].prenom.c_str(), prenom_recherche.c_str()) == 0)
		{
			cout << endl << "Auteur numero " << i << endl;
			Aff_Auteur(maBiblio.auteur[i]);
			cout << endl << "---------------------------------------------" << endl;
			reponse = Verif_Reponse("Trouvez-vous l'auteur que vous voulez ? o/n : ", 'o', 'n');
			if (reponse == 'o') {
				position_auteur = i + position_auteur + 1;
			}
			system("cls");
		}
	}
	if (position_auteur == -1) { cout << "Auteur non trouve dans la bibliotheque\n"; }
	return position_auteur;
}

/////////////////////////////////////////////////////////////////////
//
// Fonction permettant de rechercher un livre ayant le meme titre 
// et de l'afficher
// Entrée : structure bibliothèque, titre recherché
// Retour : entier position livre
//
/////////////////////////////////////////////////////////////////////
int Recherche_Livre_Meme_Titre(t_biblio maBiblio, string titre_recherche) {
	int i, position_livre;
	char reponse;

	position_livre = -1;
	for (i = 0; i <= maBiblio.nbLivre - 1; i++) {
		if (_stricmp(maBiblio.livre[i].titre.c_str(), titre_recherche.c_str()) == 0) {
			cout << endl << "Livre numero : " << i << endl << endl;
			Aff_Livre(maBiblio, maBiblio.livre[i]);
			cout << endl << "---------------------------------------------" << endl;
			reponse = Verif_Reponse("Trouvez-vous le livre que vous voulez ? o/n : ", 'o', 'n');
			if (reponse == 'o') {
				position_livre = i + position_livre + 1;
			}
			system("cls");
		}
	}
	if (position_livre == -1) { cout << "Livre non trouve dans la bibliotheque\n"; }
	return position_livre;
}

//////////////////////////////////////////////////////////////
//
// Fonction permettant de renvoyer la position d'un genre
// recherché du livre
// Entrée : structure genre, chaîne
// Retour : entier
//
//////////////////////////////////////////////////////////////
int Recherche_Genre_Livre(t_genre G, string genre_recherche) {
	int i, position_genre;

	position_genre = -1;
	for (i = 0; i <= G.nbGenre - 1; i++) {
		if ( _stricmp(G.tab_genres[i].c_str(), genre_recherche.c_str()) == 0 ) {
			position_genre = i;
			break;
		}
	}
	return position_genre;
}

/////////////////////////////////////////////////
//
// Fonction permettant de vérifier si un livre 
// existe déjà par son code
// Entrée : structure bibliothèque, chaîne
// Retour : booléen
//
/////////////////////////////////////////////////
bool Recherche_Code_Livre(t_biblio B, string code) {
	bool existe = false;
	int i;

	for (i = 0; i <= B.nbLivre - 1; i++) {
		if (B.livre[i].code == code) {
			existe = true;
			break;
		}
	}
	return existe;
}

//==================== RECHERCHE ====================//

//==================== AJOUT ====================//

////////////////////////////////////////////////////////
//
// Procédure permettant d'ajouter les infos d'un auteur
// Entrée : structure auteur
// Sortie : structure auteur
//
////////////////////////////////////////////////////////
void Ajout_Infos_Auteur(t_auteur& monAuteur) {
	bool correct;
	char reponse;

	cin.ignore(MAX_IGNORE, '\n');
	monAuteur.nationalite = Saisir_Chaine("Entrer la nationalite de l'auteur : ");
	monAuteur.nationalite[0] = Majuscule_Caractere(monAuteur.nationalite[0]);

	do {
		cout << endl << "Entrer la date de naissance : " << endl;
		SaisirDate(monAuteur.naissance.jour, monAuteur.naissance.mois, monAuteur.naissance.annee);
		correct = VerifDate(monAuteur.naissance.jour, monAuteur.naissance.mois, monAuteur.naissance.annee);
		if (correct == false) {
			cout << "La date saisie n'existe pas " << endl;
		}
	} while (correct == false);

	reponse = Verif_Reponse("L'auteur est-il decede? o/n : ", 'o', 'n');
	if (reponse == 'o') {
		do {
			cout << endl << "Entrer la date de deces : " << endl;
			SaisirDate(monAuteur.deces.jour, monAuteur.deces.mois, monAuteur.deces.annee);
			correct = VerifDate(monAuteur.deces.jour, monAuteur.deces.mois, monAuteur.deces.annee);
			//La date de naissance ne peut être égale à celle de décès
			//L'auteur doit avoir au moins 5 ans
			if (correct == false) {
				cout << "La date saisie n'existe pas " << endl;
			}
			else if (monAuteur.naissance.annee == monAuteur.deces.annee || monAuteur.deces.annee < monAuteur.naissance.annee + 5) {
				correct = false;
				cout << "Incoherent ! L'auteur doit avoir au moins 5 ans ! " << endl;
			}
		} while (correct == false);
	}
	else {
		monAuteur.deces.jour = -1;
		monAuteur.deces.mois = -1;
		monAuteur.deces.annee = -1;
	}
	monAuteur.code_auteur = Code_ID_Auteur(monAuteur);
	//Nombre de livres d'un auteur au départ
	monAuteur.nbLivres = 0; 
}

/////////////////////////////////////////////////////////////////
//
// Procédure permettant d'ajouter un auteur dans la bibliothèque
// Entrée : structure bibliothèque, entier position auteur
// Sortie : structure bibliothèque, entier position auteur
//
/////////////////////////////////////////////////////////////////
void Ajout_Auteur(t_biblio& maBiblio, int& position) {
	int position_auteur;
	string code, nom, prenom;

	Saisir_2_Chaines("Entrer le nom de l'auteur : ", nom, "Entrer le prenom de l'auteur : ", prenom);
	position_auteur = Recherche_Auteur_Meme_Nom_Prenom(maBiblio, nom, prenom);

	if (position_auteur == -1) {
		if (maBiblio.nbAuteur == MAX) {
			cout << "Impossible, la bibliotheque ne peut contenir que " << MAX << " auteurs" << endl;
			position = -1;
		}
		else {
			cout << "Vous pouvez maintenant ajouter ses informations : " << endl;
			nom[0] = Majuscule_Caractere(nom[0]);
			maBiblio.auteur[maBiblio.nbAuteur].nom = nom;
			prenom[0] = Majuscule_Caractere(prenom[0]);
			maBiblio.auteur[maBiblio.nbAuteur].prenom = prenom;
			Ajout_Infos_Auteur(maBiblio.auteur[maBiblio.nbAuteur]);
			position = maBiblio.nbAuteur;
			position_auteur = Recherche_Code_Auteur(maBiblio, maBiblio.auteur[maBiblio.nbAuteur].code_auteur);
			if (position_auteur != -1) {
				system("cls");
				cout << "Il existe deja un auteur ayant les memes donnees !\nAnnulation d'ajout d'auteur !\n\n";
				cout << "Vous avez entre comme informations : \n";
				Aff_Auteur(maBiblio.auteur[maBiblio.nbAuteur]);
				cout << endl << "L'auteur existant est : \n";
				Aff_Auteur(maBiblio.auteur[position_auteur]);
				position = -1;
			}
			else {
				system("cls");
				cout << endl << "Un auteur vient d'etre ajouter dans la bibliotheque. \nSon numero est : " << position << endl;
				//Nombre d'auteurs dans la biblithèque
				maBiblio.nbAuteur = maBiblio.nbAuteur + 1;
			}
		}
	}
	else {
		system("cls");
		cout << "Vous avez choisi l'auteur " << position_auteur << endl << endl;
		Aff_Auteur(maBiblio.auteur[position_auteur]);
		position = position_auteur;
	}
}

/////////////////////////////////////////////////////////
//
// Procédure permettant d'ajouter les infos d'un livre
// Entrée : structure bibliothèque et livre
// Sortie : structure livre
//
/////////////////////////////////////////////////////////
void Ajout_Infos_Livre(t_biblio maBiblio, t_livre& monLivre) {
	char rep;
	rep = Verif_Reponse("Connaissez-vous l'editeur? o/n : ", 'o', 'n');
	if (rep == 'o') {
		cin.ignore(MAX_IGNORE, '\n');
		monLivre.editeur = Saisir_Chaine("Entrer l'editeur : ");
	}
	else {
		monLivre.editeur = "inconnue";
	}
	monLivre.pages = Saisir_Entier_Sup_Eg("Entrer le nombre de pages du livre : ", 1);
	//Le livre n'a aucune critique au départ
	monLivre.note.nbNote = 0;
	monLivre.note.moyenne = -1; cout << endl;
	monLivre.etat = "disponible";
}

////////////////////////////////////////////////////////////////
//
// Procédure permettant d'ajouter un livre dans la bibliothèque
// Entrée : structure bibliothèque
// Sortie : structure bibliothèque
//
////////////////////////////////////////////////////////////////
void Ajout_Livre(t_biblio& maBiblio) {
	int position, position_livre;
	char rep;
	bool existe;

	if (maBiblio.nbLivre == MAX) {
		cout << "Impossible, la bibliotheque ne peut contenir que " << MAX << " livres\n";
	}
	else {
		cout << "Entrer les informations du livre : \n";
		Saisir_Livre(maBiblio.livre[maBiblio.nbLivre]);
		position_livre = Recherche_Livre_Meme_Titre(maBiblio, maBiblio.livre[maBiblio.nbLivre].titre);
		existe = Recherche_Code_Livre(maBiblio, maBiblio.livre[maBiblio.nbLivre].code);
		if (position_livre == -1 && existe == false) {
			//Etape ajout informations du livre
			Ajout_Infos_Livre(maBiblio, maBiblio.livre[maBiblio.nbLivre]);
			//Etape ajouter auteur au livre
			rep = Verif_Reponse("Connaissez-vous l'auteur/traducteur? o/n : ", 'o', 'n');
			if (rep == 'o') {
				Ajout_Auteur(maBiblio, position);
				if (position == -1) {
					cout << "Erreur de saisie d'auteur ! Impossible d'ajouter un livre !\n";
				}
				else {
					//Nombre de livres d'un auteur
					maBiblio.auteur[position].nbLivres = maBiblio.auteur[position].nbLivres + 1;
					//Lier code de l'auteur correspondant au livre 
					maBiblio.livre[maBiblio.nbLivre].code_auteur = maBiblio.auteur[position].code_auteur;
				}
			}
			else {
				maBiblio.livre[maBiblio.nbLivre].code_auteur = "inconnue";
			}
			Saisir_Date_Livre(maBiblio, maBiblio.livre[maBiblio.nbLivre]);
			system("cls");
			cout << "Un livre vient d'etre ajouter dans la bibliotheque" << endl;
			//Nombre de livres dans la bibliothèque
			maBiblio.nbLivre = maBiblio.nbLivre + 1;
		}
		else {
			system("cls");
			cout << "Il existe deja un livre ayant ce code ISBN : " << maBiblio.livre[maBiblio.nbLivre].code << "\nAnnulation d'ajout du livre !\n";
		}
	}
}

//==================== AJOUT ====================//


//==================== SUPPRIMER ====================//

/////////////////////////////////////////////////////////
//
// Procédure permettant de supprimer un livre
// Entrée : structure / données d'une bibliothèque
// Sortie : structure / données d'une bibliothèque
//
/////////////////////////////////////////////////////////
void Supprime_Livre(t_biblio& maBiblio) {
	char rep;
	string titre;
	int position, position_auteur;

	cin.ignore(MAX_IGNORE, '\n');
	titre = Saisir_Chaine("Entrer le titre du livre que vous voulez supprimer : ");

	position = Recherche_Livre_Meme_Titre(maBiblio, titre);
	if (position == -1) {
		cout << "Suppression impossible !\n";
	}
	else {
		rep = Verif_Reponse("\nVoulez-vous le supprimer ? o/n ? : ", 'o', 'n');
		if (rep == 'o') {
			position_auteur = Recherche_Code_Auteur(maBiblio, maBiblio.livre[position].code_auteur);
			if (position_auteur != -1) {
				//Supprimer le livre de l'auteur
				maBiblio.auteur[position_auteur].nbLivres = maBiblio.auteur[position_auteur].nbLivres - 1;
			}
			else {
				cout << "Le livre n'a pas d'auteur\n";
			}

			//Le dernier livre prend la place du celui que l'on souhaite supprimer
			maBiblio.livre[position] = maBiblio.livre[maBiblio.nbLivre - 1];

			//Diminuer le nombre de livres dans la bibliothèque
			maBiblio.nbLivre = maBiblio.nbLivre - 1;
			cout << "Le livre est supprime" << endl;
		}
		else { cout << "La suppression est annulee !\n"; }
	}
}

/////////////////////////////////////////////////
//
// Procédure permettant de supprimer un auteur
// Entrée : structure bibliothèque
// Sortie : structure bibliothèque
//
/////////////////////////////////////////////////
void Supprime_Auteur(t_biblio& maBiblio) {
	char rep;
	string nom, prenom;
	int i, position_auteur, code;

	Saisir_2_Chaines("Entrer le nom de l'auteur : ", nom, "Entrer le prenom de l'auteur : ", prenom);
	position_auteur = Recherche_Auteur_Meme_Nom_Prenom(maBiblio, nom, prenom);

	if (position_auteur != -1) {
		rep = Verif_Reponse("\nVoulez-vous le supprimer ? o/n ? : ", 'o', 'n');
		if (rep == 'o') {
			//Supprimer l'auteur du livre
			for (i = 0; i <= maBiblio.nbLivre - 1; i++) {
				if (maBiblio.livre[i].code_auteur == maBiblio.auteur[position_auteur].code_auteur) {
					maBiblio.livre[i].code_auteur = "inconnue";
				}
			}
			//Le dernier auteur prend la place de celui que l'on souhaite supprimer
			maBiblio.auteur[position_auteur] = maBiblio.auteur[maBiblio.nbAuteur - 1];

			//Diminuer le nombre d'auteurs dans la bibliothèque
			maBiblio.nbAuteur = maBiblio.nbAuteur - 1;
			cout << "L'auteur est supprime" << endl;
		}
		else { cout << "La suppression est annulee !\n"; }
	}
}

////////////////////////////////////////////////////////
//
// Procédure permettant de supprimer un genre du livre
// Entrée : structure genre
// Sortie : structure genre
//
////////////////////////////////////////////////////////
void Supprime_Genre(t_genre& G) {
	string chaine;
	int pos_genre;

	cin.ignore(MAX_IGNORE, '\n');
	chaine = Saisir_Chaine("Entrer le genre a supprimer : ");
	pos_genre = Recherche_Genre_Livre(G, chaine);
	if (pos_genre != -1) {
		//Affecte le dernier genre au genre supprimé
		G.tab_genres[pos_genre] = G.tab_genres[G.nbGenre - 1];
		//Diminuer le nombre de genre du livre
		G.nbGenre -= 1;
		cout << "Le genre '" << chaine << "' est supprime du livre\n";
		cout << "Le livre possede maintenant " << G.nbGenre << " genre(s)" << endl;
	}
	else { cout << "Genre non existant !\nLa suppression est annulee !\n"; }
}
//==================== SUPPRIMER ====================//


//==================== MODIFIER ====================//

////////////////////////////////////////////////////////////////
//
// Procédure permettant de modifier les informations d'un livre
// Entrée : structure bibliothèque, entier position livre
// Sortie : structure bibliothèque
//
////////////////////////////////////////////////////////////////
void Modifier_Livre(t_biblio& maBiblio, int position) {
	int choix, position_auteur;
	string chaine;
	bool correct, chiffre_ok;
	char rep;
	string menu[MAX_MENU];

	choix = 0;

	do {
		menu[0] = "  MENU LIVRE  ";
		menu[1] = "Que voulez-vous modifier?";
		menu[2] = "1: Afficher le livre";
		menu[3] = "2: Titre";
		menu[4] = "3: Genre";
		menu[5] = "4: Langue";
		menu[6] = "5: Auteur";
		menu[7] = "6: Date de parution";
		menu[8] = "7: Editeur";
		menu[9] = "8: Pages";
		menu[10] = "9: ISBN";
		menu[11] = "10: Version";
		menu[12] = "11: Retour au menu recherche";
		choix = Menu(1, 12, menu);

		switch (choix)
		{
		case Infos_Livre:
			cout << "Vous avez choisi ce livre :\n\n";
			Aff_Livre(maBiblio, maBiblio.livre[position]);
			break;
		case Titre:
			cout << "Titre actuel : " << maBiblio.livre[position].titre << endl;
			cin.ignore(MAX_IGNORE, '\n');
			maBiblio.livre[position].titre = Saisir_Chaine("Entrer le nouveau titre : ");
			cout << "\nRedirection au menu modification..."; Sleep(1000); system("cls");
			cout << "Le nouveau titre est : " << maBiblio.livre[position].titre;
			choix = 9;
			break;
		case Genre:
			cout << "Genres actuels : \n";
			Aff_Genre(maBiblio.livre[position].genre);
			rep = Verif_Reponse("\nVoulez-vous ajouter ou supprimer un genre du livre? a/s : ", 'a', 's');
			if (rep == 'a') {
				Saisir_Genre(maBiblio.livre[position].genre);
			}
			else {
				Supprime_Genre(maBiblio.livre[position].genre);
			}
			break;
		case Langue:
			cout << "Langue actuelle : " << maBiblio.livre[position].langue << endl;
			cin.ignore(MAX_IGNORE, '\n');
			maBiblio.livre[position].langue = Saisir_Chaine("Entrer la nouvelle langue : ");
			break;
		case Auteur:
			if (maBiblio.livre[position].code_auteur == "inconnue") {
				cout << "Le livre n'a pas d'auteur\nVous pouvez maintenant ajouter un auteur\n";
				Ajout_Auteur(maBiblio, position_auteur);
				if (position_auteur == -1) {
					cout << "Erreur d'ajout auteur !" << endl;
				}
				else {
					correct = true;
					do {
						if (maBiblio.livre[position].date.annee < maBiblio.auteur[position_auteur].naissance.annee + 5)
						{
							cout << "Incohérent ! Veuillez resaisir la date de naissance de l'auteur : ";
							cin >> maBiblio.auteur[position_auteur].naissance.annee;
							correct = false;
						}
					} while (correct == false);
					maBiblio.auteur[position_auteur].nbLivres = maBiblio.auteur[position_auteur].nbLivres + 1;
					maBiblio.livre[position].code_auteur = maBiblio.auteur[position_auteur].code_auteur;
				}

			}
			else {
				position_auteur = Recherche_Code_Auteur(maBiblio, maBiblio.livre[position].code_auteur);
				cout << "L'auteur du livre est : \n";
				Aff_Auteur(maBiblio.auteur[position_auteur]);

				rep = Verif_Reponse("Voulez-vous changer d'auteur pour le livre? o/n : ", 'o', 'n');
				if (rep == 'o') {
					maBiblio.auteur[position_auteur].nbLivres = maBiblio.auteur[position_auteur].nbLivres - 1;
					Ajout_Auteur(maBiblio, position_auteur);
					if (position_auteur == -1) { cout << "Erreur d'ajout d'auteur !\n"; }
					else {
						maBiblio.livre[position].code_auteur = maBiblio.auteur[position_auteur].code_auteur;
						maBiblio.auteur[position_auteur].nbLivres = maBiblio.auteur[position_auteur].nbLivres + 1;
						cout << "Le livre possede maintenant un auteur\n";
					}
				}
			}
			break;
		case Date:
			if (maBiblio.livre[position].date.jour == -1) {
				cout << "Annee actuelle : " << maBiblio.livre[position].date.annee << endl;
			}
			else {
				cout << "Date actuelle : " << maBiblio.livre[position].date.jour << "/" << maBiblio.livre[position].date.mois << "/" << maBiblio.livre[position].date.annee << endl;
			}
			Saisir_Date_Livre(maBiblio, maBiblio.livre[position]);
			break;
		case Editeur:
			cout << "Edition actuelle : " << maBiblio.livre[position].editeur << endl;
			cin.ignore(MAX_IGNORE, '\n');
			maBiblio.livre[position].editeur = Saisir_Chaine("Entrer le nouveau editeur : ");
			break;
		case Pages:
			cout << "Nombre de pages actuels : " << maBiblio.livre[position].pages << endl;
			maBiblio.livre[position].pages = Saisir_Entier_Sup_Eg("Entrer le nouveau nombre de pages : ", 1);
			break;
		case ISBN:
			cout << "ISBN actuel : " << maBiblio.livre[position].code << endl;
			do {
				maBiblio.livre[position].code = Controle_Nombre_Caractere("Entrer le code ISBN du livre : ", 13, "chiffres");
				chiffre_ok = Verif_Chaine_Chiffre(maBiblio.livre[position].code);
				correct = Recherche_Code_Livre(maBiblio, maBiblio.livre[position].code);
				if (correct == true) {
					cout << "Un livre possede deja ce code ISBN\n";
				}
			} while (chiffre_ok == false && correct == true);
			break;
		case Version:
			rep = Verif_Reponse("Est-ce une version originale ou traduite? o/t : ", 'o', 't');
			if (rep == 'o') {
				maBiblio.livre[position].version = "VO";
			}
			else {
				maBiblio.livre[position].version = "VT";
			}
			break;
		}
	} while (choix != 11);
}

//////////////////////////////////////////////////////////
//
// Procédure permettant de modifier les infos d'un auteur
// Entrée : structure bibliothèque
// Sortie : structure bilbiothèque
//
//////////////////////////////////////////////////////////
void Modifier_Auteur(t_biblio& maBiblio) {
	string nom, prenom;
	char rep;
	int choix, position_auteur, code, position_livre, i;
	string menu[MAX_MENU];
	bool correct;

	choix = 0;
	Saisir_2_Chaines("Entrer le nom de l'auteur : ", nom, "Entrer le prenom de l'auteur : ", prenom);
	position_auteur = Recherche_Auteur_Meme_Nom_Prenom(maBiblio, nom, prenom);
	if (position_auteur != -1) {
		code = Recherche_Code_Auteur(maBiblio, maBiblio.auteur[position_auteur].code_auteur);
		do {
			menu[0] = "  MENU AUTEUR  ";
			menu[1] = "Que voulez-vous modifier?";
			menu[2] = "1: Afficher l'auteur";
			menu[3] = "2: Nom";
			menu[4] = "3: Prenom";
			menu[5] = "4: Nationalite";
			menu[6] = "5: Date de naissance";
			menu[7] = "6: Date de deces";
			menu[8] = "7: Retour au menu recherche";
			choix = Menu(1, 8, menu);

			switch (choix)
			{
			case Infos_Auteur:
				cout << "Vous avez choisi cet auteur :\n\n";
				Aff_Auteur(maBiblio.auteur[code]);
				break;
			case Nom:
				cout << "Nom actuel : " << maBiblio.auteur[code].nom << endl;
				cin.ignore(MAX_IGNORE, '\n');
				maBiblio.auteur[code].nom = Saisir_Chaine("Entrer le nouveau nom : ");
				cout << "Le nouveau nom est : " << maBiblio.auteur[code].nom;
				break;
			case Prenom:
				cout << "Prenom actuel : " << maBiblio.auteur[code].prenom << endl;
				cin.ignore(MAX_IGNORE, '\n');
				maBiblio.auteur[code].prenom = Saisir_Chaine("Entrer le nouveau prenom : ");
				cout << "Le nouveau prenom est : " << maBiblio.auteur[code].prenom;
				break;
			case Nationalite:
				cout << "Nationalite actuelle : " << maBiblio.auteur[code].nationalite << endl;
				cin.ignore(MAX_IGNORE, '\n');
				maBiblio.auteur[code].nationalite = Saisir_Chaine("Entrer la nouvelle nationalite : ");
				break;
			case Naissance:
				cout << "Date actuelle : " << maBiblio.auteur[code].naissance.jour << "/" << maBiblio.auteur[code].naissance.mois << "/" << maBiblio.auteur[code].naissance.annee << endl;
				do {
					cout << endl << "Entrer la date de naissance : " << endl;
					SaisirDate(maBiblio.auteur[code].naissance.jour, maBiblio.auteur[code].naissance.mois, maBiblio.auteur[code].naissance.annee);
					correct = VerifDate(maBiblio.auteur[code].naissance.jour, maBiblio.auteur[code].naissance.mois, maBiblio.auteur[code].naissance.annee);
					if (correct == false) {
						cout << "La date saisie n'existe pas !" << endl;
					}
					else if ( (correct == true
						&& maBiblio.auteur[code].deces.annee != -1) 
						&& (maBiblio.auteur[code].naissance.annee >= maBiblio.auteur[code].deces.annee - 5
						|| maBiblio.auteur[code].naissance.annee >= maBiblio.auteur[code].deces.annee) ) {
						correct = false;
						cout << "Impossible !\nIncoherence date naissance et deces !\nUn auteur doit avoir au moins 5 ans !" << endl;
					}
					//Vérifier la cohérence de date parution du livre de l'auteur et l'existence de l'auteur
					if (maBiblio.auteur[code].nbLivres != 0) {
						for (i = 0; i <= maBiblio.nbLivre - 1; i++) {
							if (maBiblio.livre[i].code_auteur == maBiblio.auteur[position_auteur].code_auteur && maBiblio.livre[i].date.annee < maBiblio.auteur[position_auteur].naissance.annee + 5) {
								correct = false;
								cout << "Incoherence date livre et auteur !\n";
								cout << "Livre : " << maBiblio.livre[i].titre << endl;
								cout << "Annee de parution du livre : " << maBiblio.livre[i].date.annee << endl;
								break;
							}
						}
					}
				} while (correct == false); cout << endl;
				break;
			case Deces:
				if (maBiblio.auteur[code].deces.annee != -1) {
					cout << "Date actuelle : " << maBiblio.auteur[code].deces.jour << "/" << maBiblio.auteur[code].deces.mois << "/" << maBiblio.auteur[code].deces.annee << endl;
				}
				rep = Verif_Reponse("Voulez-vous supprimer la date de deces ou la modifier? s/m : ", 's', 'm');
				if (rep == 's') {
					Init_Date(maBiblio.auteur[code].deces);
					cout << "La date de deces est supprimee\n";
				}
				else {
					do {
						cout << endl << "Entrer la date de deces : " << endl;
						SaisirDate(maBiblio.auteur[code].deces.jour, maBiblio.auteur[code].deces.mois, maBiblio.auteur[code].deces.annee);
						correct = VerifDate(maBiblio.auteur[code].deces.jour, maBiblio.auteur[code].deces.mois, maBiblio.auteur[code].deces.annee);
						if (correct == false) {
							cout << "La date saisie n'existe pas !" << endl;
						}
						else if (correct == true && maBiblio.auteur[code].deces.annee <= maBiblio.auteur[code].naissance.annee + 5) {
							correct = false;
							cout << "Impossible !\nIncoherent date naissance et deces !\nUn auteur doit avoir au moins 5 ans !" << endl;
						}
					} while (correct == false); cout << endl;
				}
				break;
			}
		} while (choix != 7);
	}
	else cout << "Veuillez resaisir le nom et prenom\n";
}

//==================== MODIFIER ====================//


//==================== MINI MENU ====================//

//////////////////////////////////////////////////////////
//
// Procédure permettant d'effectuer des choix d'affichage
// Entrée : structure bibliothèque
// Sortie : RIEN
//
//////////////////////////////////////////////////////////
void Menu_Affichage(t_biblio bibliothèque) {
	int choix;
	string menu[MAX_MENU];
	string version;

	choix = 0;
	do {
		menu[0] = "MENU AFFICHAGE";
		menu[1] = "1: Affiche tous les livres";
		menu[2] = "2: Affiche tous les auteurs";
		menu[3] = "3: Affiche ensemble livres par :";
		menu[4] = "4: Affiche ensemble auteurs par :";
		menu[5] = "5: Retour au menu principal";
		choix = Menu(1, 5, menu);

		switch (choix)
		{
		case 1://Afficher l'ensemble des livres
			cout << "La bibliotheque contient : " << bibliothèque.nbLivre << " livre(s)";
			cout << endl << "---------------------------------------------" << endl;
			Aff_desLivres(bibliothèque);
			break;

		case 2://Afficher l'ensemble des auteurs
			cout << "La bibliotheque contient : " << bibliothèque.nbAuteur << " auteur(s)";
			cout << endl << "---------------------------------------------" << endl;
			Aff_desAuteurs(bibliothèque);
			break;

		case 3:
			do {
				menu[0] = "AFFICHE LIVRE";
				menu[1] = "1: Version Originale";
				menu[2] = "2: Version Traduite";
				menu[3] = "3: Auteur";
				menu[4] = "4: Genre";
				menu[5] = "5: Langue";
				menu[6] = "6: Lettre";
				menu[7] = "7: Retour au menu affichage";
				choix = Menu(1, 7, menu);
				switch (choix)
				{
				case 1: //Affichier les livres version originale
					Aff_Livres_Version(bibliothèque, "VO");
					break;
				case 2: //Affichier les livres version traduite
					Aff_Livres_Version(bibliothèque, "VT");
					break;
				case 3://Afficher les livres d'un auteur recherche
					Aff_Livres_Auteur(bibliothèque);
					break;
				case 4://Afficher livres par genre recherché 
					Aff_Livres_Genre(bibliothèque);
					break;
				case 5://Afficher livres par langue recherchée
					Aff_Livres_Langue(bibliothèque);
					break;
				case 6://Afficher les livres selon la lettre recherchée
					Aff_Livres_Lettre(bibliothèque);
					break;
				}
			} while (choix != 7);
			break;

		case 4:
			do {
				menu[0] = "AFFICHE AUTEUR";
				menu[1] = "1: Nom ou Prenom";
				menu[2] = "2: Annee (naissance et deces)";
				menu[3] = "3: Nationalite";
				menu[4] = "4: Retour au menu affichage";
				choix = Menu(1, 4, menu);

				switch (choix)
				{
				case 1:Aff_desAuteurs_NouP(bibliothèque);
					break;
				case 2:Aff_Auteurs_Annee(bibliothèque);
					break;
				case 3:Aff_Auteurs_Nationalite(bibliothèque);
					break;
				}
			} while (choix != 4);
			break;
		}
	} while (choix != 5);
}

///////////////////////////////////////////////////////
// 
// Procédure permettant d'effectuer des choix d'ajout
// Entrée : structure bibliothèque
// Sortie : structure bibliothèque
//
///////////////////////////////////////////////////////
void Menu_Ajout(t_biblio& bibliothèque) {
	int choix, position;
	string menu[MAX_MENU];

	position = -1;
	choix = 0;
	do {
		menu[0] = "MENU AJOUT";
		menu[1] = "1: Ajouter un livre";
		menu[2] = "2: Ajouter un auteur";
		menu[3] = "3: Retour au menu principal";
		choix = Menu(1, 3, menu);

		switch (choix)
		{
		case 1: //Ajouter un livre
			Ajout_Livre(bibliothèque);
			break;
		case 2: //Ajouter un auteur
			Ajout_Auteur(bibliothèque, position);
			break;
		}
	} while (choix != 3);
}

//////////////////////////////////////////////////////////////
//
// Procédure permettant d'effectuer des choix de suppression
// Entrée : structure bibliothèque
// Sortie : structure bibliothèque
//
//////////////////////////////////////////////////////////////
void Menu_Supprimer(t_biblio& bibliothèque) {
	int choix, i;
	string menu[MAX_MENU];
	char reponse;

	choix = 0;
	do {
		menu[0] = "MENU SUPPRESSION";
		menu[1] = "1: Toute la bibliotheque";
		menu[2] = "2: Tous les livres";
		menu[3] = "3: Tous les auteurs";
		menu[4] = "4: Un livre";
		menu[5] = "5: Un auteur";
		menu[6] = "6: Retour au menu principal";
		choix = Menu(1, 6, menu);

		switch (choix)
		{
		case 1: //Toute la bibliothèque 
			reponse = Verif_Reponse("Etes-vous sur de supprimer toute la bibliotheque? o/n :", 'o', 'n');
			if (reponse == 'o') {
				bibliothèque.nbLivre = 0;
				bibliothèque.nbAuteur = 0;
				cout << "Tous les livres et auteurs ont ete supprimes" << endl;
			}
			else { cout << "La suppression est annulee !\n"; }
			break;
		case 2: //Tous les livres 
			reponse = Verif_Reponse("Etes-vous sur de supprimer tous les livres? o/n :", 'o', 'n');
			if (reponse == 'o') {
				bibliothèque.nbLivre = 0;
				cout << "Tous les livres ont ete supprimes" << endl;
				// Le nombre de livre de chaque auteur est initialisé à 0
				for (i = 0; i <= bibliothèque.nbAuteur - 1; i++) {
					bibliothèque.auteur[i].nbLivres = 0;
				}
			}
			else { cout << "La suppression est annulee !\n"; }
			break;
		case 3: //Tous les auteurs 
			reponse = Verif_Reponse("Etes-vous sur de supprimer tous les auteurs? o/n :", 'o', 'n');
			if (reponse == 'o') {
				bibliothèque.nbAuteur = 0;
				//Le code auteur lié au livre devient "inconnue"
				for (i = 0; i <= bibliothèque.nbLivre - 1; i++) {
					bibliothèque.livre[i].code_auteur = "inconnue";
				}
			}
			else { cout << "La suppression est annulee !\n"; }
			break;
		case 4: //Un livre
			Supprime_Livre(bibliothèque);
			break;
		case 5: //Un auteur
			Supprime_Auteur(bibliothèque);
			break;
		}
	} while (choix != 6);
}

////////////////////////////////////////////////////////////
//
// Procédure permettant d'effectuer des choix de recherche
// Entrée : structure bibliothèque
// Sortie : structure bibliothèque
//
////////////////////////////////////////////////////////////
void Menu_Rechercher(t_biblio& bibliothèque) {
	int choix, position;
	string chaine, nom, prenom;
	string menu[MAX_MENU];

	position = -1;
	do {
		menu[0] = "MENU RECHERCHE";
		menu[1] = "1: Livre";
		menu[2] = "2: Auteur";
		menu[3] = "3: Retour au menu principal";
		choix = Menu(1, 3, menu);

		switch (choix)
		{
		case 1: //Recherche d'un livre
			cin.ignore(MAX_IGNORE, '\n');
			chaine = Saisir_Chaine("Entrer le titre du livre que vous voulez rechercher : ");
			position = Recherche_Livre_Meme_Titre(bibliothèque, chaine);

			if (position == -1) {
				cout << "Vueillez resaisir le titre !\n";
			}
			else {
				do {
					menu[0] = "MENU LIVRE";
					menu[1] = "1: Afficher";
					menu[2] = "2: Emprunter le livre";
					menu[3] = "3: Rendre le livre";
					menu[4] = "4: Donner une note";
					menu[5] = "5: Modifier le livre";
					menu[6] = "6: Retour au menu recherche";
					choix = Menu(1, 6, menu);

					switch (choix)
					{
					case 1: //Afficher
						if (position != -1) {
							system("cls");
							cout << "Vous avez choisi ce livre :\n\n";
							Aff_Livre(bibliothèque, bibliothèque.livre[position]);
						}
						break;
					case 2: //Emprunter le livre
						Emprunt_Rendre(bibliothèque, "emprunte", position);
						break;
					case 3: //Rendre le livre
						Emprunt_Rendre(bibliothèque, "disponible", position);
						break;
					case 4: //Donner une note
						Note_Livre(bibliothèque.livre[position].note);
						break;
					case 5: //Modifier les éléments du livre
						Modifier_Livre(bibliothèque, position);
						break;
					}
				} while (choix != 6);
			}
			break;
		case 2: //Recherche d'un auteur
			Modifier_Auteur(bibliothèque);
			break;
		}
	} while (choix != 3);
}

//==================== MINI MENU ====================//
