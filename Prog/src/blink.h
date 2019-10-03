#include<stdio.h>
#include <stdint.h>

#define GF 32

void mise_zero_oeil(uint8_t oeil[GF][GF]);
void mise_un_oeil(uint8_t oeil[GF][GF]);
void symetrie_centrale_2(uint8_t oeil[GF][GF]);
void symetrie_centrale_4(uint8_t oeil[GF][GF]);
void symetrie_axiale_2(uint8_t oeil[GF][GF]);
void inversion_matrice(uint8_t oeil[GF][GF]);
void remplissage_ligne(uint8_t oeil[GF], int debut, int fin);

void affichage_matrice(uint8_t oeil[GF][GF]);


void quart_cercle(uint8_t oeil[GF][GF]);
void iris_cercle(uint8_t oeil[GF][GF],int centre_i,int centre_j, int type_iris);

void contour_oeil(uint8_t oeil[GF][GF]);
void deplace_iris_choisi(uint8_t oeil[GF][GF], int centre, int type_iris);
void oeil_complet(uint8_t oeil[GF][GF], int centre, int type_iris);
void oeil_complet_xy(uint8_t oeil[GF][GF], int centre_i, int centre_j, int type_iris);
void iris_centre(uint8_t oeil[GF][GF]);
void iris_centre_droit(uint8_t oeil[GF][GF]);
void iris_droite(uint8_t oeil[GF][GF]);
void oeil_ouvert(uint8_t oeil[GF][GF]);

void demi_crane(uint8_t oeil[GF][GF]);
void demi_machoire(uint8_t oeil[GF][GF], int position);
void crane_complet(uint8_t oeil[GF][GF], int position);


void animation(uint8_t oeil[GF][GF], char f);
