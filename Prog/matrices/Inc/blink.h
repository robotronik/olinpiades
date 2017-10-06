#include<stdio.h>

#define GF 32

void mise_zero_oeil(char oeil[GF][GF]);
void mise_un_oeil(char oeil[GF][GF]);
void symetrie_centrale_2(char oeil[GF][GF]);
void symetrie_centrale_4(char oeil[GF][GF]);
void inversion_matrice(char oeil[GF][GF]);
void remplissage_ligne(char oeil[GF], int debut, int fin);

void affichage_matrice(char oeil[GF][GF]);


void quart_cercle(char oeil[GF][GF]);
void iris_cercle(char oeil[GF][GF],int centre_i,int centre_j, int type_iris);

void contour_oeil(char oeil[GF][GF]);
void deplace_iris_choisi(char oeil[GF][GF], int centre, int type_iris);
void oeil_complet(char oeil[GF][GF], int centre, int type_iris);
void iris_centre(char oeil[GF][GF]);
void iris_centre_droit(char oeil[GF][GF]);
void iris_droite(char oeil[GF][GF]);
void oeil_ouvert(char oeil[GF][GF]);
