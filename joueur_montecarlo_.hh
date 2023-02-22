#pragma once

#include "joueur.hh"
#include "node.hh"

#include<vector>
#include<memory>



class Joueur_MonteCarlo_ : public Joueur
{
public:
  Joueur_MonteCarlo_(std::string nom, bool joueur);


  void recherche_coup(Jeu j, couple & coup) override;

 // couple random(Jeu j, couple &coup) //nouvelle fonction qui choisit un coup aléatoire


  //------------- nouvelles fonctions ---------------


  Node selection(Node noeud);
  Node expansion(Node noeud);
  int simulation(Node noeud);
  couple meilleur_coup(Node noeud);


};



