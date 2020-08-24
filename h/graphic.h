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
// Proc�dure permettant de changer la position du curseur
// Entr�e : 2 entiers (x,y)
// Sortie : RIEN
//
///////////////////////////////////////////////////////////
void Gotoxy(int x, int y);

/////////////////////////////////////////////////////////
//
// Proc�dure permettant d'effacer l'�cran de la console
// Entr�e : RIEN
// Sortie : RIEN
//
/////////////////////////////////////////////////////////
/*void ClearScreen();*/

/////////////////////////////////////////////////////////////
//
// Proc�dure permettant de changer la taille de la console
// Entr�e : 2 entiers
// Sortie : RIEN
//
/////////////////////////////////////////////////////////////
void ResizeConsole(int hauteur, int longueur);

#endif // !GRAPHIC_H
