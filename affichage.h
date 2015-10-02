/*
    Les fonctions bas-niveau de dessin
 */



// on récupère un tableau de 16 entiers de 16 bits qui représente l'image
uint16_t* getFrame();


// On sélectionne une colonne à afficher (qui change donc à chaque instant)
void selectionne_colonne(int ligne);


// Après avoir sélectionné la colonne, il faut sélectionner les lignes à afficher
void ajoute_ligne();


void affiche_frame();

void animation();
void init_text_display();
