/*
 * Fichier: main.c
 * Auteur: Tom MACARD
 * ---------------------
 * Fichier principal du projet.
 */

#include <stdio.h>
#include <stdbool.h>
#include <limits.h>
#include <stdlib.h>
#include <omp.h>

#include "fonction.h"


# define TAILLE_ARBRE 1000


// Taille max arbre pour analyse mémoire et vitesse
// Exemple TAILLE_MAX_ARBRE = 8 -> 10^8 noeuds, soit environ 3 Go de mémoire
// !!!!!! ATTENTION !!!!!!
// Sur ma machine (16Go de RAM), 9 et + -> RAM saturée et crash
// Par défaut, 7 devrait fonctionner sur la plupart des machines
# define TAILLE_MAX_ARBRE 7



int main() {

    printf("Taille de structure Noeud: %zu octets\n", sizeof(struct Noeud));

    // Déclaration des variables
    double w1;
    double w2;
    bool resultatRecursif;
    bool resultatIteratif;
    double tempsRecursif;
    double tempsIteratif;
    int i;


    // Création des arbres

    // Arbre 1
    struct Noeud* arbre_basique = creerNoeud(2);
    arbre_basique->gauche = creerNoeud(1);
    arbre_basique->droite = creerNoeud(3);

    // Arbre 2
    struct Noeud* arbre_abr = creer_ABR(TAILLE_ARBRE);

    // Arbre 3
    struct Noeud* arbre_non_abr = creerNoeud(2);
    arbre_non_abr->droite = creerNoeud(1);
    arbre_non_abr->gauche = creerNoeud(3);

    // Arbre 4
    struct Noeud* arbre_aleatoire = creer_AB_aleatoire(TAILLE_ARBRE);



    // Ajout des arbres à la foret pour analyses plus faciles
    struct Foret* foret = malloc(sizeof(struct Foret));
    foret->arbre = arbre_basique;
    foret->suivant = malloc(sizeof(struct Foret));
    foret->suivant->arbre = arbre_abr;
    foret->suivant->suivant = malloc(sizeof(struct Foret));
    foret->suivant->suivant->arbre = arbre_non_abr;
    foret->suivant->suivant->suivant = malloc(sizeof(struct Foret));
    foret->suivant->suivant->suivant->arbre = arbre_aleatoire;
    foret->suivant->suivant->suivant->suivant = NULL;


    // Calculs généraux de tous les arbres
    printf("=======Calculs généraux=======\n");
    struct Foret* arbre_actuel = foret;
    i=1;
    while (arbre_actuel != NULL) {
        w1 = omp_get_wtime();
        resultatRecursif = estABR_recursif(arbre_actuel->arbre, INT_MIN, INT_MAX);
        w2 = omp_get_wtime();
        tempsRecursif = w2 - w1;

        w1 = omp_get_wtime();
        resultatIteratif = estABR_iteratif(arbre_actuel->arbre);
        w2 = omp_get_wtime();
        tempsIteratif = w2 - w1;

        // Affichage
        printf("=======Arbre numéro %d=======\n", i);
        printf("Temps récursif    : %.10f\n", tempsRecursif);
        if (resultatRecursif)
            printf("Résultat recursif : Oui ABR\n");
        else
            printf("Résultat recursif : Non ABR\n");

        printf("Temps itératif    : %.10f\n", tempsIteratif);
        if (resultatIteratif)
            printf("Résultat itératif : Oui ABR\n");
        else
            printf("Résultat itératif : Non ABR\n");

        // Arbre suivant
        i++;
        arbre_actuel = arbre_actuel->suivant;
    }
    printf("=====Fin des calculs généraux=====\n");


    printf("\n\n\n=======Analyse de taille d'arbre======\n");
    int taille = 1;
    for (int j = 1; j <= TAILLE_MAX_ARBRE; j++)
    {
        taille = taille*10;
        struct Noeud* arbre = creer_ABR(taille);
        w1 = omp_get_wtime();
        resultatRecursif = estABR_recursif(arbre, INT_MIN, INT_MAX);
        w2 = omp_get_wtime();
        tempsRecursif = w2 - w1;

        w1 = omp_get_wtime();
        resultatIteratif = estABR_iteratif(arbre);
        w2 = omp_get_wtime();
        tempsIteratif = w2 - w1;
        free(arbre);

        // Affichage
        printf("=======Arbre de taille %d=======\n", taille);
        printf("Temps récursif    : %.10f\n", tempsRecursif);
        printf("Temps itératif    : %.10f\n", tempsIteratif);

    }
    printf("=====Fin Analyse de taille d'arbre=====\n");







    return 0;
}
