#pragma once

#include"jeu.hh"
#include"joueurs/joueur_montecarlo_.hh"
#include"arbitre.hh"
#include"joueurs/node.hh"
class apprentissage{
    int resultat(result r){
    switch(r){
    case result::P1:return 1;break;
    case result::P2 :return -1;break;
    case result::ERREUR :return -10;break;
    case result::NULLE  :return 0;break;

    }
    };

    void updatev2(std::vector<Node> v,Node root,int r){
    int j(0);
       if(!v.empty())
      while (root._enfant.at(j)._x !=v.at(0)._x && root._enfant.at(j)._y != v.at(0)._y) {
        ++j;
        }

        root._enfant.at(j)._nbsim++;
        root._enfant.at(j)._score =+ r;
        //updatev2(v.erase(0),root._enfant.at(j),r);
        v.erase(v.begin());
            if (!v.empty()) {
                updatev2(v, root._enfant.at(j), r);
            }

      }


};
