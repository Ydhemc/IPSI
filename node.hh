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
    int _x;
    int _y;
    courant _j; //joueur courant
    int _score; //somme des récompenses des simulations passés par ce noeud
    int _nbsim; //nombre de simulations passé par ce noeud
    int _nbcoups; //nombre de coups possibles à partir de cet état du jeu
    std::vector<Node> _enfant; //vecteur de noeuds enfNode(const Jeu & jeu, std::vector<Node> const & enfant, int numcoup)ant

    Node();
    Node(const courant & j, const int & x, const int & y);  //constructeur qui initialise le jeu en début de partie
    Node(std::vector<Node> const & enfant, int const & nbsim, int const & score, int const & nbcoups, int const & x, int const & y, courant const & j); //constructeur pour le déroulement de la partie

};

#endif // ARBRE_HH
