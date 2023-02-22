 #pragma once
#ifndef ARBRE_HH
#define ARBRE_HH

#include "joueur_montecarlo_.hh"

enum class courant {
    adversaire, avengers
};


class Node
{
public:
    int x;
    int y;
    courant _j; //joueur courant
    int _score; //somme des récompenses des simulations passés par ce noeud
    int _nbsim; //nombre de simulations passé par ce noeud
    int _nbcoups; //nombre de coups possibles à partir de cet état du jeu
    Jeu _jeu; //état du jeu de ce noeud;
    std::vector<Node> _enfant; //vecteur de noeuds enfNode(const Jeu & jeu, std::vector<Node> const & enfant, int numcoup)ant

    Node(const Node &)= delete; //interdit la copie
    Node(const Jeu & jeu, const courant & j);  //constructeur qui initialise le jeu en début de partie
    Node(const Jeu & jeu, std::vector<Node> const & enfant, int numcoup); //constructeur pour le déroulement de la partie

};

#endif // ARBRE_HH
