#pragma once
#ifndef GRAPHIC_H
#define GRAPHIC_H
#include <iostream>
#include <string>
#include <sstream>
#include <conio.h>
#include <Windows.h>
using namespace std;

///////////////////////////////////////////////////////////
//
// Procédure permettant de changer la position du curseur
// Entrée : 2 entiers (x,y)
// Sortie : RIEN
//
///////////////////////////////////////////////////////////
void Gotoxy(int x, int y);

/////////////////////////////////////////////////////////
//
// Procédure permettant d'effacer l'écran de la console
// Entrée : RIEN
// Sortie : RIEN
//
/////////////////////////////////////////////////////////
/*void ClearScreen();*/

/////////////////////////////////////////////////////////////
//
// Procédure permettant de changer la taille de la console
// Entrée : 2 entiers
// Sortie : RIEN
//
/////////////////////////////////////////////////////////////
void ResizeConsole(int hauteur, int longueur);

#endif // !GRAPHIC_H
