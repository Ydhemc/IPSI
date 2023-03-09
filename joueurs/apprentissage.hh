#pragma once

#include"../jeu.hh"

#include "joueur.hh"
#include "joueur_random.hh"
#include "joueur_manuel.hh"
#include "joueur_montecarlo_.hh"
#include "joueur_alphabeta.hh"

#include"joueur_montecarlo_.hh"
#include"node.hh"


class apprentissage{
private:
    std::shared_ptr<Joueur> _joueur1;
    std::shared_ptr<Joueur> _joueur2;

    Jeu _jeu;
    std::vector<couple> _coups;

    std::vector<std::mutex> _coups_mutex;

    int _nombre_parties;
    int _numero_partie;

    player _player1;
    player _player2;

    Node _n;

public:
    //relié à l'abre de notre monte carlo
    apprentissage(player player1 , player player2, int nombre_parties, Node &n);


    void initialisation();
    /**
     * @brief challenge
     * @param nombre_parties
     * methode lançant un challenge avec un nombre de parties
     * affiche le nombre de parties gagnées pour chaque participant
     * @return 0 si tout c'est bien passé, 1 sinon
     */
    Node challenge();

    /**
     * @brief partie
     * @return le gagnant de la partie (result::1 pour le joueur 1, result::2 pour joueur 2, result::NULLE en cas de partie nulle, result::ERREUR en cas de problème)
     * lance une partie,
     *
     */
    std::pair<result,std::vector<couple>> partie();



    int resultat(result r);

    void updatev2(std::vector<couple> v,Node &root,int r);


};
