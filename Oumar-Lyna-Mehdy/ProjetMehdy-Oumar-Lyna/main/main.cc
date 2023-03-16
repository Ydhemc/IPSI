
#include <iostream>
#include "arbitre.hh"
#include "jeu.hh"
#include "joueurs/ProjetMehdy-Oumar-Lyna/apprentissage.hh"
#include "joueurs/ProjetMehdy-Oumar-Lyna/save.hh"


int main()
{
/*
    //initialise la graine du générateur aléatoire
    std::srand(std::time(nullptr));

    //création de l'Arbitre (joueur jouant en 1er la premiere partie, joueur jouant en 2eme celle-ci , nombre de parties)
    Arbitre a (player::M_1, player::M_2,10);
     //commence le challenge
    int r= a.challenge();
    */
    std::srand(std::time(nullptr));

    //création de l'Arbitre (joueur jouant en 1er la premiere partie, joueur jouant en 2eme celle-ci , nombre de parties)
    save s;
    Node App= s.import("arbre.txt");
    apprentissage a(player::M_1, player::M_2,1000,App);
     //commence le challenge
    Node r= a.challenge();
    s.exporter(r,"arbre");

   return 1; //r si arbitre



}
