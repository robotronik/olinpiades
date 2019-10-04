/*
 * Fichier généré par pixelbot@Robotronik
 * Paramètres :
 * Taille de la matrice : 32 px
 * Images par secondes : 60 FPS
 * Niveaux de luminosité : 8
 * Fréquence de rafraîchissement : 13440 Hz
 * Sens de lecture : par colonne
 * Rotation : pi/2
 * Taille d'un caractère : 10*14 px
 * Police de caractère : Sans
 * Ensemble de caractères : chiffres 
 * Date de création : mer. mars 21 19:05:07 2018
 */

#ifndef SPRITES_HEADER
#define SPRITES_HEADER

#define MATRIX_SIZE 32
#define CLOCK_FREQUENCY 13440
#define BRIGHTNESS_LEVELS 8

#define ROW_LENGTH 10
#define ROWS_PER_FRAME 14
#define BYTES_PER_ROW 2

#define NUMBERS 1
#define LOWERCASE 0
#define UPPERCASE 0

#if NUMBERS==1
#define NUMBERS_INDEX 0
#endif

#if LOWERCASE==1
#define LOWERCASE_INDEX 0
#endif

#if UPPERCASE==1
#define UPPERCASE_INDEX 0
#endif

/*
 * Syntaxe :
 * sprites[indice_caractère][n° de frame][rangée][octet]
 */
extern unsigned char sprites[10][8-1][14][2];

#endif
