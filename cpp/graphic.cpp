#include "../h/graphic.h"

///////////////////////////////////////////////////////////
//
// Procédure permettant de changer la position du curseur
// Entrée : 2 entiers (x,y)
// Sortie : RIEN
//
///////////////////////////////////////////////////////////
void Gotoxy(int x, int y) {
	HANDLE ConsoleOutput;
	COORD Cursor_Pos = { x - 1,y - 1 };
	ConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(ConsoleOutput, Cursor_Pos);
}

/////////////////////////////////////////////////////////
//
// Procédure permettant d'effacer l'écran de la console
// Entrée : RIEN
// Sortie : RIEN
//
/////////////////////////////////////////////////////////
/*void ClearScreen() {
	HANDLE Output;
	COORD Position;
	Output = GetStdHandle(STD_OUTPUT_HANDLE);
	Position.X = 0;
	Position.Y = 0;
	SetConsoleCursorPosition(Output, Position);
}*/

/////////////////////////////////////////////////////////////
//
// Procédure permettant de changer la taille de la console
// Entrée : 2 entiers
// Sortie : RIEN
//
/////////////////////////////////////////////////////////////
void ResizeConsole(int longueur, int largeur) {
	HWND Console = GetConsoleWindow();
	RECT r;
	GetWindowRect(Console, &r);
	MoveWindow(Console, r.left, r.top, longueur, largeur, TRUE);
}