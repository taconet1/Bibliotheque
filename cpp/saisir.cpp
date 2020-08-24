#include "../h/saisir.h"
using namespace std;

////////////////////////////////////////////////////////////////////////
//
// Fonction permettant de saisir un entier dans l'intervalle souhaitee
// Entr�e : chaine de caract�res contenant le message, entier min et max
// Retour : entier 
//
////////////////////////////////////////////////////////////////////////
int Saisir_Entier(string message, int min, int max) {
	int n;

	do {
		cout << message;
		cin >> n;
		if (n < min || n > max) {
			cout << "Entrer une valeur entre " << min << " et " << max << endl;
		}
	} while (n < min || n > max);
	return n;
}

////////////////////////////////////////////////
//
// Fonction permettant de saisir un entier 
// sup�rieur ou �gal � un entier
// Entr�e : chaine message, entier 
// Retour : entier
//
////////////////////////////////////////////////
int Saisir_Entier_Sup_Eg(string message, int min) {
	int n;

	do {
		cout << message;
		cin >> n;
		if (n < min) {
			cout << "Entrer une valeur superieure ou egale a : " << min << endl;
		}
	} while (n < min);
	return n;
}

//////////////////////////////////////////////
//
// Fonction permettant de saisir une chaine
// Entr�e : cha�ne message
// Retour : cha�ne 
//
//////////////////////////////////////////////
string Saisir_Chaine(string message) {
	string chaine;
	do {
		cout << message;
		getline(cin, chaine);
	} while (chaine == "");
	return chaine;
}

///////////////////////////////////////////////
//
// Fonction permettant de saisir un caract�re
// Entr�e : cha�ne message
// Retour : caract�re
//
///////////////////////////////////////////////
char Saisir_Caractere(string message) {
	char c;

	do {
		cout << message;
		cin >> c;
	} while (c == NULL || (c < 141 && c > 172) || (c < 101 && c > 132));
	return c;
}

////////////////////////////////////////////
//
// Proc�dure permettant de saisir 2 chaines
// Entr�e : 2 cha�nes message
// Sortie : 2 chaines
//
////////////////////////////////////////////
void Saisir_2_Chaines(string mess1, string& s1, string mess2, string& s2) {
	cin.ignore(MAX_IGNORE, '\n');
	s1 = Saisir_Chaine(mess1);
	s2 = Saisir_Chaine(mess2);
}

///////////////////////////////////////////////////
//
// Proc�dure permettant de saisir une date
// Entr�e : RIEN
// Sortie : 3 entiers (jour, mois, ann�e)
//
///////////////////////////////////////////////////
void SaisirDate(int& jour, int& mois, int& ann�e) {
	do
	{
		cout << "Entrer le jour : ";
		cin >> jour;
	} while (jour <= 0 || jour > 31);
	do
	{
		cout << "Entrer le mois : ";
		cin >> mois;
	} while (mois <= 0 || mois > 12);
	cout << "Entrer l'annee : ";
	cin >> ann�e;
}

/////////////////////////////////////////////
//
// Fonction permettant de contr�ler 
// la saisie de la r�ponse de l'utilisateur
// Entr�e : cha�ne, 2 caract�res
// Retour : un caract�re
//
//////////////////////////////////////////////
char Verif_Reponse(string message, char choix1, char choix2) {
	char rep;

	do {
		rep = Saisir_Caractere(message);
	} while (rep != choix1 && rep != choix2);
	return rep;
}

////////////////////////////////////////////////////////////////////////
//
// Fonction permettant de saisir un d�cimal dans l'intervalle souhaitee
// Entr�e : chaine de caract�res contenant le message, entier min et max
// Retour : d�cimal
//
////////////////////////////////////////////////////////////////////////
float Saisir_Decimal(string message, int min, int max) {
	float n;

	do {
		cout << message;
		cin >> n;
		if (n < min || n > max) {
			cout << "Entrer une valeur entre " << min << " et " << max << endl;
		}
	} while (n < min || n > max);
	return n;
}

/////////////////////////////////////////////
//
// Fonction permettant de contr�ler 
// le nombre de caract�res d'une cha�ne
// Entr�e : 2 cha�nes, entier
// Retour : cha�ne
//
/////////////////////////////////////////////
string Controle_Nombre_Caractere(string message, int nbElement_max, string type) {
	int longueur;
	string chaine;

	do {
		cin.ignore(MAX_IGNORE, '\n');
		chaine = Saisir_Chaine(message);
		longueur = chaine.length();
		if (longueur != nbElement_max || chaine == "") {
			cout << "La chaine doit etre compose de " << nbElement_max << " " << type << endl;
		}
	} while (longueur != nbElement_max || chaine == "");
	return chaine;
}

/////////////////////////////////////////////////////////////////
//
// Fonction permettant de v�rifier si une cha�ne ne contient pas 
// d'autres caract�res que des chiffres
// Entr�e : chaine
// Retour : bool�en
//
/////////////////////////////////////////////////////////////////
bool Verif_Chaine_Chiffre(string chaine) {
	int i;
	bool ok = true;

	for (i = 0; i <= chaine.length() - 1; i++) {
		if (chaine[i] < '0' || chaine[i] > '9') {
			cout << "Erreur !\nLa chaine contient d'autres caracteres que des chiffres !";
			ok = false;
			break;
		}
	}
	return ok;
}