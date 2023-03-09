#pragma once
#ifndef ARBRE_HH
#define ARBRE_HH

#include "joueur_montecarlo_.hh"
#include <vector>

enum class courant {
   premier, deuxième
};

float tabln[12][11] = {
    {0, 1.17, 1.48, 1.66, 1.79, 1.89, 1.97, 2.04, 2.10, 2.15, 2.19},
    {0, 0.83, 1.05, 1.18, 1.27, 1.34, 1.39, 1.44, 1.48, 1.52, 1.55},
    {0, 0.68, 0.85, 0.96, 1.03, 1.09, 1.14, 1.18, 1.21, 1.24, 1.26},
    {0, 0.59, 0.74, 0.83, 0.90, 0.95, 0.99, 1.02, 1.05, 1.07, 1.09},
    {0, 0.53, 0.66, 0.74, 0.80, 0.85, 0.88, 0.91, 0.94, 0.96, 0.98},
    {0, 0.48, 0.60, 0.68, 0.73, 0.77, 0.80, 0.84, 0.85, 0.88, 0.89},
    {0, 0.44, 0.56, 0.63, 0.68, 0.71, 0.74, 0.77, 0.79, 0.81, 0.83},
    {0, 0.42, 0.52, 0.58, 0.63, 0.67, 0.70, 0.72, 0.74, 0.76, 0.77},
    {0, 0.39, 0.49, 0.55, 0.60, 0.63, 0.66, 0.68, 0.70, 0.71, 0.73},
    {0, 0.37, 0.47, 0.53, 0.57, 0.60, 0.62, 0.64, 0.66, 0.68, 0.69},
    {0, 0.35, 0.45, 0.50, 0.54, 0.57, 0.59, 0.61, 0.63, 0.64, 0.66},
    {0, 0.34, 0.43, 0.48, 0.52, 0.55, 0.57, 0.59, 0.60, 0.62, 0.63}
};
//Les tableaux en c++ commençant par 0,je crois qu'on aura pas le choix et on devra faire moins 1 pour n et k.Ex on veut le résultat pour n=2 et k=4 eh bien on fera tabln[n-1][k-1] soit
//avec cet exemple,tabln[1][3]

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

// methodes

   bool est_feuille() const; // renvoie vrai si le noeud n'a pas d'enfant
   bool est_terminal() const; //renvoie vrai si le noeud est un état terminal
   void ajouter_enfant(const Node &enfant); // ajoute un nœud enfant au vecteur _enfant
   int meilleur_coup() const; //renvoie le meilleur coup à jouer à partir du nœud courant
   float qubc(const Node &n) ;
   Node meilleur_enfant();
   Node & selection(Node const & n); //selectionne le meilleur enfant
   Node & expansion();
void * fusionnerArbres(Node const &,Node const &,Node &);

};

#endif // ARBRE_HH
