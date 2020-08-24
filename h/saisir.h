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
// Entrée : chaine de caractères contenant le message, entier min et max
// Retour : entier 
//
////////////////////////////////////////////////////////////////////////
int Saisir_Entier(string message, int min, int max);

////////////////////////////////////////////////
//
// Fonction permettant de saisir un entier 
// supérieur ou égal à un entier
// Entrée : chaine message, entier 
// Retour : entier
//
////////////////////////////////////////////////
int Saisir_Entier_Sup_Eg(string message, int min);

//////////////////////////////////////////////
//
// Fonction permettant de saisir une chaine
// Entrée : chaîne message
// Retour : chaîne 
//
//////////////////////////////////////////////
string Saisir_Chaine(string message);

////////////////////////////////////////////
//
// Procédure permettant de saisir 2 chaines
// Entrée : 2 chaînes message
// Sortie : 2 chaines
//
////////////////////////////////////////////
void Saisir_2_Chaines(string mess1, string& s1, string mess2, string& s2);

///////////////////////////////////////////////
//
// Fonction permettant de saisir un caractère
// Entrée : chaîne message
// Retour : caractère
//
///////////////////////////////////////////////
char Saisir_Caractere(string message);

///////////////////////////////////////////////////
//
// Procédure permettant de saisir une date
// Entrée : RIEN
// Sortie : 3 entiers (jour, mois, année)
//
///////////////////////////////////////////////////
void SaisirDate(int& jour, int& mois, int& année);

/////////////////////////////////////////////
//
// Fonction permettant de contrôler 
// la saisie de la réponse de l'utilisateur
// Entrée : chaîne, 2 caractères
// Retour : un caractère
//
//////////////////////////////////////////////
char Verif_Reponse(string message, char choix1, char choix2);

////////////////////////////////////////////////////////////////////////
//
// Fonction permettant de saisir un décimal dans l'intervalle souhaitee
// Entrée : chaine de caractères contenant le message, entier min et max
// Retour : décimal
//
////////////////////////////////////////////////////////////////////////
float Saisir_Decimal(string message, int min, int max);

/////////////////////////////////////////////
//
// Fonction permettant de contrôler 
// le nombre de caractères d'une chaîne
// Entrée : 2 chaînes, entier
// Retour : chaîne
//
/////////////////////////////////////////////
string Controle_Nombre_Caractere(string message, int nbElement_max, string type);

/////////////////////////////////////////////////////////////////
//
// Fonction permettant de vérifier si une chaîne ne contient pas 
// d'autres caractères que des chiffres
// Entrée : chaine
// Retour : booléen
//
/////////////////////////////////////////////////////////////////
bool Verif_Chaine_Chiffre(string chaine);

#endif // !SAISIR_H
