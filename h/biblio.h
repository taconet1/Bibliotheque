#pragma once
#ifndef BIBLIO_H
#define BIBLIO_H
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
using namespace std;

const int MAX = 20;
const int MAX_MENU = 15;
const int MAX_GENRE = 5;

enum Main_Choix {
	Afficher = 1,
	Ajouter,
	Supprimer,
	Rechercher,
	Quitter
};

enum Livre {
	Infos_Livre = 1,
	Titre,
	Genre,
	Langue,
	Auteur,
	Date,
	Editeur,
	Pages,
	ISBN,
	Version
};

enum Auteur {
	Infos_Auteur = 1,
	Nom,
	Prenom,
	Nationalite,
	Naissance,
	Deces
};

struct t_date {
	int jour;
	int mois;
	int annee;
};

struct t_auteur {
	string nom;
	string prenom;
	string nationalite;
	t_date naissance;
	t_date deces;
	string code_auteur;
	int nbLivres;
};

struct t_note {
	int nbNote;
	vector<float> tab_notes;
	float moyenne;
};

struct t_genre {
	int nbGenre;
	string tab_genres[MAX_GENRE];
};

struct t_livre {
	string version;
	string titre;
	t_genre genre;
	string langue;
	string code_auteur;
	t_date date;
	string editeur;
	int pages;
	t_note note; 
	string etat;
	string code;
};

struct t_biblio {
	int nbLivre;
	t_livre livre[MAX];
	int nbAuteur;
	t_auteur auteur[MAX];
};

//==================== SAISIR ====================//

/////////////////////////////////////////////////////
//
// Proc�dure permettant d'ajouter un genre au livre
// Entr�e : structure genre
// Sortie : structure genre
//
/////////////////////////////////////////////////////
void Saisir_Genre(t_genre& G);

////////////////////////////////////////////
//
// Proc�dure permettant de saisir un livre
// Entr�e : RIEN
// Sortie : structure livre
//
/////////////////////////////////////////////
void Saisir_Livre(t_livre& monLivre);

///////////////////////////////////////////////////////////
//
// Proc�dure permettant de saisir et v�rifier 
// la coh�rence de la date de parution du livre
// Entr�e : structure biblioth�que, structure livre,
// Sortie : structure livre
//
///////////////////////////////////////////////////////////
void Saisir_Date_Livre(t_biblio maBiblio, t_livre& monLivre);

//==================== SAISIR ====================//


//==================== FICHIER LECTURE ====================//

/////////////////////////////////////
//
// Fonction permettant de tester 
// si un fichier en lecture est vide
// Entr�e : cha�ne
// Retour : bool�en
//
/////////////////////////////////////
bool TestReadVide(string filename);

///////////////////////////////////////////////////
//
// Proc�dure permettant de lire des donn�es 
// d'un auteur d'un fichier
// Entr�e : fichier, structure auteur
// Sortie : fichier, structure auteur
//
///////////////////////////////////////////////////
void ReadAuthorLine(ifstream& file, t_auteur& A);

////////////////////////////////////////////////////////////
//
// Proc�dure permettant de lire chaque ligne d'un fichier
// Entr�e : chaine
// Sortie : structure biblioth�que
//
////////////////////////////////////////////////////////////
void ReadAuthorFile(string filename, t_biblio& B);

//////////////////////////////////////////////////////
//
// Proc�dure permettant de lire les notes d'un livre
// d'un fichier
// Entr�e : fichier
// Sortie : structure note
//
//////////////////////////////////////////////////////
void ReadNoteLine(ifstream& file, t_note& N);

///////////////////////////////////////////////////
//
// Proc�dure permettant de lire la liste de genres
// d'un livre
// Entr�e : fichier
// Sortie : structure genre
//
///////////////////////////////////////////////////
void ReadGenreLine(ifstream& file, t_genre& G);

/////////////////////////////////////////////////
//
// Proc�dure permettant de lire les donn�es 
// d'un livre d'un fichier
// Entr�e : fichier
// Sortie : structure livre
//
/////////////////////////////////////////////////
void ReadBookLine(ifstream& file, t_livre& L);

///////////////////////////////////////////////
//
// Proc�dure permettant de lire les donn�es 
// d'une biblioth�que d'un fichier
// Entr�e : cha�ne, structure biblioth�que
// Sortie : structure biblioth�que
//
///////////////////////////////////////////////
void ReadLibrary(string filename, t_biblio& B);

//==================== FICHIER LECTURE ====================//


//==================== FICHIER ECRITURE ====================//

/////////////////////////////////////////////
//
// Proc�dure permettant d'�crire les donn�es 
// d'un auteur dans un fichier
// Entr�e : structure auteur
// Sortie : fichier
//
/////////////////////////////////////////////
void WriteAuthorLine(ofstream& file, t_auteur A);

///////////////////////////////////////////
//
// Proc�dure permettant d'�crire une liste
// d'auteurs dans un fichier
// Entr�e : chaine, structure biblioth�que
// Sortie : fichier
//
///////////////////////////////////////////
void WriteAuthorFile(string filename, t_biblio B);

//////////////////////////////////////////////
//
// Proc�dure permettant d'�crire les notes
// du livre dans un fichier
// Entr�e : structure note
// Sortie : fichier
//
//////////////////////////////////////////////
void WriteNoteLine(ofstream& file, t_note N);

///////////////////////////////////////////////
//
// Proc�dure permettant d'�crire une liste
// de genres d'un livre dans un fichier
// Entr�e : structure genre
// Sortie : fichier
//
///////////////////////////////////////////////
void WriteGenreLine(ofstream& file, t_genre G);

///////////////////////////////////////////////
//
// Proc�dure permettant d'�crire les donn�es 
// d'un livre dans un fichier
// Entr�e : structure livre
// Sortie : fichier
//
///////////////////////////////////////////////
void WriteBookLine(ofstream& file, t_livre L);

////////////////////////////////////////////
//
// Proc�dure permettant d'�crire une liste 
// de livres dans un fichier
// Entr�e : cha�ne, structure biblioth�que
// Sortie : fichier
//
////////////////////////////////////////////
void WriteLibrary(string filename, t_biblio B);

//==================== FICHIER ECRITURE ====================//


//==================== DIVERS ====================//

////////////////////////////////////////////////////////////
//
// Fonction permettant de convertir une variable en cha�ne
// Entr�e : variable
// Retour : cha�ne
//
////////////////////////////////////////////////////////////
template<typename toConvert>
string toString(toConvert value);

//////////////////////////////////////////////////////////////
//
// Fonction permettant de renvoyer une lettre en majuscule
// Entr�e : caract�re
// Retour : caract�re en majuscule
//
//////////////////////////////////////////////////////////////
char Majuscule_Caractere(char lettre);

/////////////////////////////////////////////////////////////////////
//
// Fonction permettant d'afficher un menu et effectuer un choix
// Entr�e : entier min et max, tableau cha�ne menu
// Retour : entier choix
//
/////////////////////////////////////////////////////////////////////
int Menu(int minchoix, int maxchoix, string menu[MAX_MENU]);

////////////////////////////////////////////////////////////
//
// Fonction permettant de v�rifier la coh�rence d'une date
// Entr�e : 3 entiers (jour, mois, ann�e)
// Retour : bool�en
//
////////////////////////////////////////////////////////////
bool VerifDate(int j, int m, int a);

////////////////////////////////////////////////////////////////
//
// Fonction permettant de cr�er un code unique pour un auteur
// Entr�e : structure auteur
// Retour : cha�ne code auteur
//
////////////////////////////////////////////////////////////////
string Code_ID_Auteur(t_auteur monAuteur);

////////////////////////////////////////////////////////
//
// Proc�dure permettant d'emprunter ou rendre un livre
// Entr�e : structure biblioth�que, 
//			cha�ne �tat livre, entier position livre
// Sortie : structure biblioth�que
//
/////////////////////////////////////////////////////////
void Emprunt_Rendre(t_biblio& maBiblio, string disponibilite, int sa_position);

//////////////////////////////////////////////////////////////////
//
// Proc�dure permettant de calculer la moyenne de note d'un livre
// Entr�e : structure note
// Sortie : structure note
//
//////////////////////////////////////////////////////////////////
void Note_Livre(t_note& uneNote);

/////////////////////////////////////////////////////////////////////
//
// Proc�dure permettant de trier une biblioth�que par ordre alphab�tique
// Entr�e : structure biblioth�que
// Sortie : structure biblioth�que
//
/////////////////////////////////////////////////////////////////////
void Tri_Bulle(t_biblio& B);

//==================== DIVERS ====================//


//==================== INITIALISER ====================//

/*////////////////////////////////////////////////////
//
// Fonction permettant d'initialiser un nombre � 0
// Entr�e : nombre
// Retour : nombre nul
//
////////////////////////////////////////////////////
template<typename Type>
Type Init_Nombre(Type value);

////////////////////////////////////////////////
//
// Fonction permettant d'initialiser une cha�ne
// Entr�e : cha�ne
// Retour : cha�ne
//
////////////////////////////////////////////////
string Init_Chaine(string chaine);*/

///////////////////////////////////////////////
//
// Proc�dure permettant d'initialiser une date
// Entr�e : structure date
// Sortie : structure date
//
///////////////////////////////////////////////
void Init_Date(t_date& maDate);

//==================== INITIALISER ====================//


//==================== AFFICHAGE ====================//

//////////////////////////////////////////////
//
// Proc�dure permettant d'afficher la liste 
// des genres d'un livre
// Entr�e : structure genre
// Sortie : RIEN
//
//////////////////////////////////////////////
void Aff_Genre(t_genre G);

////////////////////////////////////////////////////////////////
//
// Proc�dure permettant d'afficher les informations d'un livre
// Entr�e : structure biblioth�que et livre
// Sortie : RIEN 
//
////////////////////////////////////////////////////////////////
void Aff_Livre(t_biblio maBiblio, t_livre monLivre);

//////////////////////////////////////////////////////////////////
//
// Proc�dure permettant d'afficher les livres de la biblioth�que
// Entr�e : structure / donn�es de la biblioth�que
// Sortie : RIEN
//
//////////////////////////////////////////////////////////////////
void Aff_desLivres(t_biblio maBiblio);

////////////////////////////////////////////////////////////////
//
// Proc�dure permettant d'afficher les informations d'un auteur
// Entr�e : structure auteur
// Sortie : RIEN
//
////////////////////////////////////////////////////////////////
void Aff_Auteur(t_auteur monAuteur);

/////////////////////////////////////////////////////////////////
//
// Proc�dure permettant d'afficher les auteurs de la biblioth�que
// Entr�e : structure biblioth�que
// Sortie : RIEN
//
/////////////////////////////////////////////////////////////////
void Aff_desAuteurs(t_biblio maBiblio);

//////////////////////////////////////////////////////////
//
// Proc�dure permettant d'afficher les livres d'un auteur
// Entr�e : structure biblioth�que
// Sortie : RIEN
//
//////////////////////////////////////////////////////////
void Aff_Livres_Auteur(t_biblio biblioth�que);

///////////////////////////////////////////////
//
// Proc�dure permettant d'afficher des livres 
// selon un genre recherch�
// Entr�e : structure biblioth�que
// Sortie : RIEN
//
///////////////////////////////////////////////
void Aff_Livres_Genre(t_biblio biblioth�que);

///////////////////////////////////////////////
//
// Proc�dure permettant d'afficher des livres 
// selon une langue recherch�e
// Entr�e : structure biblioth�que
// Sortie : RIEN
//
///////////////////////////////////////////////
void Aff_Livres_Langue(t_biblio biblioth�que);

///////////////////////////////////////////////
//
// Proc�dure permettant d'afficher des livres
// selon une lettre recherch�e
// Entr�e : structure biblioth�que
// Sortie : RIEN
//
///////////////////////////////////////////////
void Aff_Livres_Lettre(t_biblio maBiblio);

///////////////////////////////////////////////////////////
//
// Proc�dure permettant d'afficher tous les auteurs selon
// le nom ou pr�nom distinct recherch�
// Entr�e : structure biblioth�que
// Sortie : RIEN
//
///////////////////////////////////////////////////////////
void Aff_desAuteurs_NouP(t_biblio maBiblio);

//////////////////////////////////////////////////////
//
// Proc�dure permettant d'afficher des auteurs selon 
// la nationalite recherche
// Entr�e : structure biblioth�que
// Sortie : RIEN
//
//////////////////////////////////////////////////////
void Aff_Auteurs_Nationalite(t_biblio maBiblio);

/////////////////////////////////////////////////////////////////
//
// Proc�dure permettant d'afficher des auteurs n�s ou d�c�d�s
// dans un intervalle d'ann�e choisie
// Entr�e : structure biblioth�que
// Sortie : RIEN
//
/////////////////////////////////////////////////////////////////
void Aff_Auteurs_Annee(t_biblio maBiblio);

////////////////////////////////////////////////////
//
// Proc�dure permettant d'afficher des livres 
// selon la version recherch�e
// Entr�e : structure biblioth�que, cha�ne
// Sortie : RIEN
//
////////////////////////////////////////////////////
void Aff_Livres_Version(t_biblio B, string version);

//==================== AFFICHAGE ====================//


//==================== RECHERCHE ====================//

/////////////////////////////////////////////////////////////
//
// Fonction permettant de rechercher un auteur par son code
// Entr�e : structure biblioth�que, cha�ne code recherch�
// Retour : entier position auteur
//
/////////////////////////////////////////////////////////////
int Recherche_Code_Auteur(t_biblio maBib, string code_recherche);

/////////////////////////////////////////////////////////////////////
//
// Fonction permettant de compter le nombre d'auteurs ayant le m�me
// nom et pr�nom et de les afficher
// Entr�e : structure biblioth�que, cha�nes nom et pr�nom
// Retour : entier position auteur
//
/////////////////////////////////////////////////////////////////////
int Recherche_Auteur_Meme_Nom_Prenom(t_biblio maBiblio, string nom_recherche, string prenom_recherche);

/////////////////////////////////////////////////////////////////////
//
// Fonction permettant de rechercher un livre ayant le meme titre 
// et de l'afficher
// Entr�e : structure biblioth�que, titre recherch�
// Retour : entier position livre
//
/////////////////////////////////////////////////////////////////////
int Recherche_Livre_Meme_Titre(t_biblio maBiblio, string titre_recherche);

//////////////////////////////////////////////////////////////
//
// Fonction permettant de renvoyer la position d'un genre
// recherch� du livre
// Entr�e : structure genre, cha�ne
// Retour : entier
//
//////////////////////////////////////////////////////////////
int Recherche_Genre_Livre(t_genre L, string genre_recherche);

/////////////////////////////////////////////////
//
// Fonction permettant de v�rifier si un livre 
// existe d�j� par son code
// Entr�e : structure biblioth�que, cha�ne
// Retour : bool�en
//
/////////////////////////////////////////////////
bool Recherche_Code_Livre(t_biblio B, string code);

//==================== RECHERCHE ====================//


//==================== AJOUT ====================//

////////////////////////////////////////////////////////
//
// Proc�dure permettant d'ajouter les infos d'un auteur
// Entr�e : structure auteur
// Sortie : structure auteur
//
////////////////////////////////////////////////////////
void Ajout_Infos_Auteur(t_auteur& monAuteur);

/////////////////////////////////////////////////////////////////
//
// Proc�dure permettant d'ajouter un auteur dans la biblioth�que
// Entr�e : structure biblioth�que, entier position auteur
// Sortie : structure biblioth�que, entier position auteur
//
/////////////////////////////////////////////////////////////////
void Ajout_Auteur(t_biblio& maBiblio, int& position);

/////////////////////////////////////////////////////////
//
// Proc�dure permettant d'ajouter les infos d'un livre
// Entr�e : structure biblioth�que et livre
// Sortie : structure livre
//
/////////////////////////////////////////////////////////
void Ajout_Infos_Livre(t_biblio maBiblio, t_livre& monLivre);

////////////////////////////////////////////////////////////////
//
// Proc�dure permettant d'ajouter un livre dans la biblioth�que
// Entr�e : structure biblioth�que
// Sortie : structure biblioth�que
//
////////////////////////////////////////////////////////////////
void Ajout_Livre(t_biblio& maBiblio);

//==================== AJOUT ====================//


//==================== SUPPRIMER ====================//

/////////////////////////////////////////////////////////
//
// Proc�dure permettant de supprimer un livre
// Entr�e : structure / donn�es d'une biblioth�que
// Sortie : structure / donn�es d'une biblioth�que
//
/////////////////////////////////////////////////////////
void Supprime_Livre(t_biblio& maBiblio);

/////////////////////////////////////////////////
//
// Proc�dure permettant de supprimer un auteur
// Entr�e : structure biblioth�que
// Sortie : structure biblioth�que
//
/////////////////////////////////////////////////
void Supprime_Auteur(t_biblio& maBiblio);

////////////////////////////////////////////////////////
//
// Proc�dure permettant de supprimer un genre du livre
// Entr�e : structure genre
// Sortie : structure genre
//
////////////////////////////////////////////////////////
void Supprime_Genre(t_genre& G);

//==================== SUPPRIMER ====================//


//==================== MODIFIER ====================//

////////////////////////////////////////////////////////////////
//
// Proc�dure permettant de modifier les informations d'un livre
// Entr�e : structure biblioth�que, entier position livre
// Sortie : structure biblioth�que
//
////////////////////////////////////////////////////////////////
void Modifier_Livre(t_biblio& maBiblio, int position);

//////////////////////////////////////////////////////////
//
// Proc�dure permettant de modifier les infos d'un auteur
// Entr�e : structure biblioth�que
// Sortie : structure bilbioth�que
//
//////////////////////////////////////////////////////////
void Modifier_Auteur(t_biblio& maBiblio);

//==================== MODIFIER ====================//

//==================== MINI MENU ====================//

//////////////////////////////////////////////////////////
//
// Proc�dure permettant d'effectuer des choix d'affichage
// Entr�e : structure biblioth�que
// Sortie : RIEN
//
//////////////////////////////////////////////////////////
void Menu_Affichage(t_biblio biblioth�que);

///////////////////////////////////////////////////////
// 
// Proc�dure permettant d'effectuer des choix d'ajout
// Entr�e : structure biblioth�que
// Sortie : structure biblioth�que
//
///////////////////////////////////////////////////////
void Menu_Ajout(t_biblio& biblioth�que);

//////////////////////////////////////////////////////////////
//
// Proc�dure permettant d'effectuer des choix de suppression
// Entr�e : structure biblioth�que
// Sortie : structure biblioth�que
//
//////////////////////////////////////////////////////////////
void Menu_Supprimer(t_biblio& biblioth�que);

////////////////////////////////////////////////////////////
//
// Proc�dure permettant d'effectuer des choix de recherche
// Entr�e : structure biblioth�que
// Sortie : structure biblioth�que
//
////////////////////////////////////////////////////////////
void Menu_Rechercher(t_biblio& biblioth�que);

/////////////////////////////////////////////////////////////
//
// Proc�dure permettant d'effectuer des choix de mofication
// Entr�e : structure biblioth�que
// Sortie : structure biblioth�que
//
/////////////////////////////////////////////////////////////
void Menu_Modifier(t_biblio& biblioth�que);

//==================== MINI MENU ====================//

#endif // !BIBLIO_H

