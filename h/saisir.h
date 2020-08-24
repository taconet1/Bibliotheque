#pragma once
#ifndef SAISIR_H
#define SAISIR_H
#include <iostream>
#include <string>
using namespace std;

const int MAX_IGNORE = 100;

////////////////////////////////////////////////////////////////////////
//
// Fonction permettant de saisir un entier dans l'intervalle souhaitee
// Entr�e : chaine de caract�res contenant le message, entier min et max
// Retour : entier 
//
////////////////////////////////////////////////////////////////////////
int Saisir_Entier(string message, int min, int max);

////////////////////////////////////////////////
//
// Fonction permettant de saisir un entier 
// sup�rieur ou �gal � un entier
// Entr�e : chaine message, entier 
// Retour : entier
//
////////////////////////////////////////////////
int Saisir_Entier_Sup_Eg(string message, int min);

//////////////////////////////////////////////
//
// Fonction permettant de saisir une chaine
// Entr�e : cha�ne message
// Retour : cha�ne 
//
//////////////////////////////////////////////
string Saisir_Chaine(string message);

////////////////////////////////////////////
//
// Proc�dure permettant de saisir 2 chaines
// Entr�e : 2 cha�nes message
// Sortie : 2 chaines
//
////////////////////////////////////////////
void Saisir_2_Chaines(string mess1, string& s1, string mess2, string& s2);

///////////////////////////////////////////////
//
// Fonction permettant de saisir un caract�re
// Entr�e : cha�ne message
// Retour : caract�re
//
///////////////////////////////////////////////
char Saisir_Caractere(string message);

///////////////////////////////////////////////////
//
// Proc�dure permettant de saisir une date
// Entr�e : RIEN
// Sortie : 3 entiers (jour, mois, ann�e)
//
///////////////////////////////////////////////////
void SaisirDate(int& jour, int& mois, int& ann�e);

/////////////////////////////////////////////
//
// Fonction permettant de contr�ler 
// la saisie de la r�ponse de l'utilisateur
// Entr�e : cha�ne, 2 caract�res
// Retour : un caract�re
//
//////////////////////////////////////////////
char Verif_Reponse(string message, char choix1, char choix2);

////////////////////////////////////////////////////////////////////////
//
// Fonction permettant de saisir un d�cimal dans l'intervalle souhaitee
// Entr�e : chaine de caract�res contenant le message, entier min et max
// Retour : d�cimal
//
////////////////////////////////////////////////////////////////////////
float Saisir_Decimal(string message, int min, int max);

/////////////////////////////////////////////
//
// Fonction permettant de contr�ler 
// le nombre de caract�res d'une cha�ne
// Entr�e : 2 cha�nes, entier
// Retour : cha�ne
//
/////////////////////////////////////////////
string Controle_Nombre_Caractere(string message, int nbElement_max, string type);

/////////////////////////////////////////////////////////////////
//
// Fonction permettant de v�rifier si une cha�ne ne contient pas 
// d'autres caract�res que des chiffres
// Entr�e : chaine
// Retour : bool�en
//
/////////////////////////////////////////////////////////////////
bool Verif_Chaine_Chiffre(string chaine);

#endif // !SAISIR_H
