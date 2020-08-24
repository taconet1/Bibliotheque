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
// Procédure permettant d'ajouter un genre au livre
// Entrée : structure genre
// Sortie : structure genre
//
/////////////////////////////////////////////////////
void Saisir_Genre(t_genre& G);

////////////////////////////////////////////
//
// Procédure permettant de saisir un livre
// Entrée : RIEN
// Sortie : structure livre
//
/////////////////////////////////////////////
void Saisir_Livre(t_livre& monLivre);

///////////////////////////////////////////////////////////
//
// Procédure permettant de saisir et vérifier 
// la cohérence de la date de parution du livre
// Entrée : structure bibliothèque, structure livre,
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
// Entrée : chaîne
// Retour : booléen
//
/////////////////////////////////////
bool TestReadVide(string filename);

///////////////////////////////////////////////////
//
// Procédure permettant de lire des données 
// d'un auteur d'un fichier
// Entrée : fichier, structure auteur
// Sortie : fichier, structure auteur
//
///////////////////////////////////////////////////
void ReadAuthorLine(ifstream& file, t_auteur& A);

////////////////////////////////////////////////////////////
//
// Procédure permettant de lire chaque ligne d'un fichier
// Entrée : chaine
// Sortie : structure bibliothèque
//
////////////////////////////////////////////////////////////
void ReadAuthorFile(string filename, t_biblio& B);

//////////////////////////////////////////////////////
//
// Procédure permettant de lire les notes d'un livre
// d'un fichier
// Entrée : fichier
// Sortie : structure note
//
//////////////////////////////////////////////////////
void ReadNoteLine(ifstream& file, t_note& N);

///////////////////////////////////////////////////
//
// Procédure permettant de lire la liste de genres
// d'un livre
// Entrée : fichier
// Sortie : structure genre
//
///////////////////////////////////////////////////
void ReadGenreLine(ifstream& file, t_genre& G);

/////////////////////////////////////////////////
//
// Procédure permettant de lire les données 
// d'un livre d'un fichier
// Entrée : fichier
// Sortie : structure livre
//
/////////////////////////////////////////////////
void ReadBookLine(ifstream& file, t_livre& L);

///////////////////////////////////////////////
//
// Procédure permettant de lire les données 
// d'une bibliothèque d'un fichier
// Entrée : chaîne, structure bibliothèque
// Sortie : structure bibliothèque
//
///////////////////////////////////////////////
void ReadLibrary(string filename, t_biblio& B);

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
void WriteAuthorLine(ofstream& file, t_auteur A);

///////////////////////////////////////////
//
// Procédure permettant d'écrire une liste
// d'auteurs dans un fichier
// Entrée : chaine, structure bibliothèque
// Sortie : fichier
//
///////////////////////////////////////////
void WriteAuthorFile(string filename, t_biblio B);

//////////////////////////////////////////////
//
// Procédure permettant d'écrire les notes
// du livre dans un fichier
// Entrée : structure note
// Sortie : fichier
//
//////////////////////////////////////////////
void WriteNoteLine(ofstream& file, t_note N);

///////////////////////////////////////////////
//
// Procédure permettant d'écrire une liste
// de genres d'un livre dans un fichier
// Entrée : structure genre
// Sortie : fichier
//
///////////////////////////////////////////////
void WriteGenreLine(ofstream& file, t_genre G);

///////////////////////////////////////////////
//
// Procédure permettant d'écrire les données 
// d'un livre dans un fichier
// Entrée : structure livre
// Sortie : fichier
//
///////////////////////////////////////////////
void WriteBookLine(ofstream& file, t_livre L);

////////////////////////////////////////////
//
// Procédure permettant d'écrire une liste 
// de livres dans un fichier
// Entrée : chaîne, structure bibliothèque
// Sortie : fichier
//
////////////////////////////////////////////
void WriteLibrary(string filename, t_biblio B);

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
string toString(toConvert value);

//////////////////////////////////////////////////////////////
//
// Fonction permettant de renvoyer une lettre en majuscule
// Entrée : caractère
// Retour : caractère en majuscule
//
//////////////////////////////////////////////////////////////
char Majuscule_Caractere(char lettre);

/////////////////////////////////////////////////////////////////////
//
// Fonction permettant d'afficher un menu et effectuer un choix
// Entrée : entier min et max, tableau chaîne menu
// Retour : entier choix
//
/////////////////////////////////////////////////////////////////////
int Menu(int minchoix, int maxchoix, string menu[MAX_MENU]);

////////////////////////////////////////////////////////////
//
// Fonction permettant de vérifier la cohérence d'une date
// Entrée : 3 entiers (jour, mois, année)
// Retour : booléen
//
////////////////////////////////////////////////////////////
bool VerifDate(int j, int m, int a);

////////////////////////////////////////////////////////////////
//
// Fonction permettant de créer un code unique pour un auteur
// Entrée : structure auteur
// Retour : chaîne code auteur
//
////////////////////////////////////////////////////////////////
string Code_ID_Auteur(t_auteur monAuteur);

////////////////////////////////////////////////////////
//
// Procédure permettant d'emprunter ou rendre un livre
// Entrée : structure bibliothèque, 
//			chaîne état livre, entier position livre
// Sortie : structure bibliothèque
//
/////////////////////////////////////////////////////////
void Emprunt_Rendre(t_biblio& maBiblio, string disponibilite, int sa_position);

//////////////////////////////////////////////////////////////////
//
// Procédure permettant de calculer la moyenne de note d'un livre
// Entrée : structure note
// Sortie : structure note
//
//////////////////////////////////////////////////////////////////
void Note_Livre(t_note& uneNote);

/////////////////////////////////////////////////////////////////////
//
// Procédure permettant de trier une bibliothèque par ordre alphabétique
// Entrée : structure bibliothèque
// Sortie : structure bibliothèque
//
/////////////////////////////////////////////////////////////////////
void Tri_Bulle(t_biblio& B);

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
Type Init_Nombre(Type value);

////////////////////////////////////////////////
//
// Fonction permettant d'initialiser une chaîne
// Entrée : chaîne
// Retour : chaîne
//
////////////////////////////////////////////////
string Init_Chaine(string chaine);*/

///////////////////////////////////////////////
//
// Procédure permettant d'initialiser une date
// Entrée : structure date
// Sortie : structure date
//
///////////////////////////////////////////////
void Init_Date(t_date& maDate);

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
void Aff_Genre(t_genre G);

////////////////////////////////////////////////////////////////
//
// Procédure permettant d'afficher les informations d'un livre
// Entrée : structure bibliothèque et livre
// Sortie : RIEN 
//
////////////////////////////////////////////////////////////////
void Aff_Livre(t_biblio maBiblio, t_livre monLivre);

//////////////////////////////////////////////////////////////////
//
// Procédure permettant d'afficher les livres de la bibliothèque
// Entrée : structure / données de la bibliothèque
// Sortie : RIEN
//
//////////////////////////////////////////////////////////////////
void Aff_desLivres(t_biblio maBiblio);

////////////////////////////////////////////////////////////////
//
// Procédure permettant d'afficher les informations d'un auteur
// Entrée : structure auteur
// Sortie : RIEN
//
////////////////////////////////////////////////////////////////
void Aff_Auteur(t_auteur monAuteur);

/////////////////////////////////////////////////////////////////
//
// Procédure permettant d'afficher les auteurs de la bibliothèque
// Entrée : structure bibliothèque
// Sortie : RIEN
//
/////////////////////////////////////////////////////////////////
void Aff_desAuteurs(t_biblio maBiblio);

//////////////////////////////////////////////////////////
//
// Procédure permettant d'afficher les livres d'un auteur
// Entrée : structure bibliothèque
// Sortie : RIEN
//
//////////////////////////////////////////////////////////
void Aff_Livres_Auteur(t_biblio bibliothèque);

///////////////////////////////////////////////
//
// Procédure permettant d'afficher des livres 
// selon un genre recherché
// Entrée : structure bibliothèque
// Sortie : RIEN
//
///////////////////////////////////////////////
void Aff_Livres_Genre(t_biblio bibliothèque);

///////////////////////////////////////////////
//
// Procédure permettant d'afficher des livres 
// selon une langue recherchée
// Entrée : structure bibliothèque
// Sortie : RIEN
//
///////////////////////////////////////////////
void Aff_Livres_Langue(t_biblio bibliothèque);

///////////////////////////////////////////////
//
// Procédure permettant d'afficher des livres
// selon une lettre recherchée
// Entrée : structure bibliothèque
// Sortie : RIEN
//
///////////////////////////////////////////////
void Aff_Livres_Lettre(t_biblio maBiblio);

///////////////////////////////////////////////////////////
//
// Procédure permettant d'afficher tous les auteurs selon
// le nom ou prénom distinct recherché
// Entrée : structure bibliothèque
// Sortie : RIEN
//
///////////////////////////////////////////////////////////
void Aff_desAuteurs_NouP(t_biblio maBiblio);

//////////////////////////////////////////////////////
//
// Procédure permettant d'afficher des auteurs selon 
// la nationalite recherche
// Entrée : structure bibliothèque
// Sortie : RIEN
//
//////////////////////////////////////////////////////
void Aff_Auteurs_Nationalite(t_biblio maBiblio);

/////////////////////////////////////////////////////////////////
//
// Procédure permettant d'afficher des auteurs nés ou décédés
// dans un intervalle d'année choisie
// Entrée : structure bibliothèque
// Sortie : RIEN
//
/////////////////////////////////////////////////////////////////
void Aff_Auteurs_Annee(t_biblio maBiblio);

////////////////////////////////////////////////////
//
// Procédure permettant d'afficher des livres 
// selon la version recherchée
// Entrée : structure bibliothèque, chaîne
// Sortie : RIEN
//
////////////////////////////////////////////////////
void Aff_Livres_Version(t_biblio B, string version);

//==================== AFFICHAGE ====================//


//==================== RECHERCHE ====================//

/////////////////////////////////////////////////////////////
//
// Fonction permettant de rechercher un auteur par son code
// Entrée : structure bibliothèque, chaîne code recherché
// Retour : entier position auteur
//
/////////////////////////////////////////////////////////////
int Recherche_Code_Auteur(t_biblio maBib, string code_recherche);

/////////////////////////////////////////////////////////////////////
//
// Fonction permettant de compter le nombre d'auteurs ayant le même
// nom et prénom et de les afficher
// Entrée : structure bibliothèque, chaînes nom et prénom
// Retour : entier position auteur
//
/////////////////////////////////////////////////////////////////////
int Recherche_Auteur_Meme_Nom_Prenom(t_biblio maBiblio, string nom_recherche, string prenom_recherche);

/////////////////////////////////////////////////////////////////////
//
// Fonction permettant de rechercher un livre ayant le meme titre 
// et de l'afficher
// Entrée : structure bibliothèque, titre recherché
// Retour : entier position livre
//
/////////////////////////////////////////////////////////////////////
int Recherche_Livre_Meme_Titre(t_biblio maBiblio, string titre_recherche);

//////////////////////////////////////////////////////////////
//
// Fonction permettant de renvoyer la position d'un genre
// recherché du livre
// Entrée : structure genre, chaîne
// Retour : entier
//
//////////////////////////////////////////////////////////////
int Recherche_Genre_Livre(t_genre L, string genre_recherche);

/////////////////////////////////////////////////
//
// Fonction permettant de vérifier si un livre 
// existe déjà par son code
// Entrée : structure bibliothèque, chaîne
// Retour : booléen
//
/////////////////////////////////////////////////
bool Recherche_Code_Livre(t_biblio B, string code);

//==================== RECHERCHE ====================//


//==================== AJOUT ====================//

////////////////////////////////////////////////////////
//
// Procédure permettant d'ajouter les infos d'un auteur
// Entrée : structure auteur
// Sortie : structure auteur
//
////////////////////////////////////////////////////////
void Ajout_Infos_Auteur(t_auteur& monAuteur);

/////////////////////////////////////////////////////////////////
//
// Procédure permettant d'ajouter un auteur dans la bibliothèque
// Entrée : structure bibliothèque, entier position auteur
// Sortie : structure bibliothèque, entier position auteur
//
/////////////////////////////////////////////////////////////////
void Ajout_Auteur(t_biblio& maBiblio, int& position);

/////////////////////////////////////////////////////////
//
// Procédure permettant d'ajouter les infos d'un livre
// Entrée : structure bibliothèque et livre
// Sortie : structure livre
//
/////////////////////////////////////////////////////////
void Ajout_Infos_Livre(t_biblio maBiblio, t_livre& monLivre);

////////////////////////////////////////////////////////////////
//
// Procédure permettant d'ajouter un livre dans la bibliothèque
// Entrée : structure bibliothèque
// Sortie : structure bibliothèque
//
////////////////////////////////////////////////////////////////
void Ajout_Livre(t_biblio& maBiblio);

//==================== AJOUT ====================//


//==================== SUPPRIMER ====================//

/////////////////////////////////////////////////////////
//
// Procédure permettant de supprimer un livre
// Entrée : structure / données d'une bibliothèque
// Sortie : structure / données d'une bibliothèque
//
/////////////////////////////////////////////////////////
void Supprime_Livre(t_biblio& maBiblio);

/////////////////////////////////////////////////
//
// Procédure permettant de supprimer un auteur
// Entrée : structure bibliothèque
// Sortie : structure bibliothèque
//
/////////////////////////////////////////////////
void Supprime_Auteur(t_biblio& maBiblio);

////////////////////////////////////////////////////////
//
// Procédure permettant de supprimer un genre du livre
// Entrée : structure genre
// Sortie : structure genre
//
////////////////////////////////////////////////////////
void Supprime_Genre(t_genre& G);

//==================== SUPPRIMER ====================//


//==================== MODIFIER ====================//

////////////////////////////////////////////////////////////////
//
// Procédure permettant de modifier les informations d'un livre
// Entrée : structure bibliothèque, entier position livre
// Sortie : structure bibliothèque
//
////////////////////////////////////////////////////////////////
void Modifier_Livre(t_biblio& maBiblio, int position);

//////////////////////////////////////////////////////////
//
// Procédure permettant de modifier les infos d'un auteur
// Entrée : structure bibliothèque
// Sortie : structure bilbiothèque
//
//////////////////////////////////////////////////////////
void Modifier_Auteur(t_biblio& maBiblio);

//==================== MODIFIER ====================//

//==================== MINI MENU ====================//

//////////////////////////////////////////////////////////
//
// Procédure permettant d'effectuer des choix d'affichage
// Entrée : structure bibliothèque
// Sortie : RIEN
//
//////////////////////////////////////////////////////////
void Menu_Affichage(t_biblio bibliothèque);

///////////////////////////////////////////////////////
// 
// Procédure permettant d'effectuer des choix d'ajout
// Entrée : structure bibliothèque
// Sortie : structure bibliothèque
//
///////////////////////////////////////////////////////
void Menu_Ajout(t_biblio& bibliothèque);

//////////////////////////////////////////////////////////////
//
// Procédure permettant d'effectuer des choix de suppression
// Entrée : structure bibliothèque
// Sortie : structure bibliothèque
//
//////////////////////////////////////////////////////////////
void Menu_Supprimer(t_biblio& bibliothèque);

////////////////////////////////////////////////////////////
//
// Procédure permettant d'effectuer des choix de recherche
// Entrée : structure bibliothèque
// Sortie : structure bibliothèque
//
////////////////////////////////////////////////////////////
void Menu_Rechercher(t_biblio& bibliothèque);

/////////////////////////////////////////////////////////////
//
// Procédure permettant d'effectuer des choix de mofication
// Entrée : structure bibliothèque
// Sortie : structure bibliothèque
//
/////////////////////////////////////////////////////////////
void Menu_Modifier(t_biblio& bibliothèque);

//==================== MINI MENU ====================//

#endif // !BIBLIO_H

