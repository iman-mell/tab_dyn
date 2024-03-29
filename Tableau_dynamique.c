#include "Tableau_dynamique.h"

void liberer_tab(Tab_dyn *tab){
    int i;
    for(i = 0; i < tab->taille_reelle; ++i)
        free(tab->donnees[i]);
    free(tab->donnees);
}

int init_tab_dyn(Tab_dyn *tab){
    tab->donnees = NULL;
    tab->donnees = (void **)malloc(sizeof(void *) * TAILLE_INIT);
    if(NULL == tab->donnees){
        fprintf(stderr, "Erreur lors de l'allocation de la mémoire !\n");
        return 0;
    }
    tab->taille_reelle = 0;
    tab->taille_max = TAILLE_INIT;
    return 1;
}

int ajouter_fin(Tab_dyn *tab, void *elem, void *(*allouer_elem)(const void *)){
    if(tab->taille_reelle >= tab->taille_max){
        tab->taille_max *= 2;
        tab->donnees = (void **)realloc(tab->donnees, tab->taille_max);
        if(NULL == tab->donnees){
            fprintf(stderr, "Erreur lors de la réallocation de la mémoire !\n");
            liberer_tab(tab);
            return 0;
        }
    }
    tab->donnees[tab->taille_reelle] = allouer_elem(elem);
    if(NULL == tab->donnees[tab->taille_reelle]){
        fprintf(stderr, "Erreur lors de l'ajout d'un élément dans le tableau dynamique !\n");
        liberer_tab(tab);
        return 0;
    }
    ++tab->taille_reelle;
    return 1;
}
