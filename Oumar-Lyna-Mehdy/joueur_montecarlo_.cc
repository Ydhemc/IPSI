#include "joueur_montecarlo_.hh"
#include "ProjetMehdy-Oumar-Lyna/save.hh"

Joueur_MonteCarlo_::Joueur_MonteCarlo_(std::string nom, bool joueur)
    :Joueur(nom,joueur), _j(Jeu(11))
{
    save s;
    _Root=s.import("arbre.txt");
    _deroule=_Root;
}



void Joueur_MonteCarlo_::recherche_coup(Jeu j, couple &coup)
{
    //pour l'apprentissage
    //le jours du tournoi il sera peut être plus preferable de visité d'abord les noeuds qui amèene à la victoire puis les noeuds egalité puis joué aléatoirement
    //parcours l'arbre si noeud non visité on le prend
    //autrement qubc /meilleur coups / meilleur enfant
    //
    //si le nombre de coups possible est supérieur au nombre de coups possible de l'arbe alors on est dans une nouvelle partie donc _deroule=_root
    //cas pour si on joue en premiers, implementé si on est second


    /* en reflexion
    if(static_cast<int>(j.coups_possibles().size())>_deroule._nbcoups)
        _deroule=_Root;
    */


    //chercher le coups de l'adversaire
    //utiliser _jeu.coupspossibles et j.coupspossibles et trouver celui qui n'est plus dans le nouveau
    int it(-1);
    std::vector<couple> jeuav(_j.coups_possibles());
    std::vector<couple> c(j.coups_possibles());
    if(jeuav.size()>c.size()){
        for(std::vector<couple>::size_type x(0); x<jeuav.size();++x){
            bool test(false);
            for( auto y:c){
                if(jeuav[x].first==y.first && jeuav[x].second==y.second)
                    test=true;
            }
            if(!test)
                it=x;
        }
        //on se place au bonne endroit dans notre arbre
        if(!_deroule._enfant.empty()){
            int pos(0);
            while (_deroule._enfant.at(pos)._x !=jeuav.at(it).first && _deroule._enfant.at(pos)._y != jeuav.at(0).second){
              ++pos;
              }
            //si le noeud a été trouver
            if(pos==(int)_deroule._enfant.size() && ( _deroule._enfant.at(pos)._x==jeuav.at(it).first && _deroule._enfant.at(pos)._y == jeuav.at(0).second) ){
              _deroule=_deroule._enfant.at(pos);
            }
            else {
                Node n;
                _deroule=n;
            }
        }
    }

    if(!_deroule._enfant.empty()){
        if(c.size()>_deroule._enfant.size()){
            //y a des coups possibles non visité
            std::vector<couple>::size_type i(0);
            bool test(true);
            //on cherche si le coups est dans le vector enfant
            while(i<c.size() && test){
               for(std::vector<Node>::const_iterator x(_deroule._enfant.begin()); x!=_deroule._enfant.end(); ++x){
                    if(!(x->_x==c.at(i).first ||  x->_y==c.at(i).second)){
                        test=false;
                    }
               }
               if(test)
                   i++;
            }
            coup.first=c.at(i).first;
            coup.second=c.at(i).second;
            Node N;
            N._x=c.at(i).first;
            N._y=c.at(i).second;
            N._nbcoups=j.coups_possibles().size();
            _deroule=N;
        }
        //tout à déja été visité donc qubc
        else {
            int M=_deroule.meilleur_coup();
            coup.first=_deroule._enfant.at(M)._x;
            coup.second=_deroule._enfant.at(M)._y;
            //on se place maintenant sur notre derniers coups, pour la prochaine recherche de coups
            _deroule=_deroule._enfant.at(M);
        }
    }
    //un sous arbre jamais visité donc on devient random
    else {
        int taille = j.coups_possibles().size();
        int num = rand()%(taille);
        coup.first=j.coups_possibles()[num].first;
        coup.second=j.coups_possibles()[num].second;
    }

    //pour la prochaine iteration
    _j=j;
}


//couple Joueur_MonteCarlo_::random(Jeu j, couple &coup)
//{
//    int taille = j.coups_possibles().size();
//    int num = rand()%(taille);
//    couple c;
//    coup.first=j.coups_possibles()[num].first;
//    coup.second=j.coups_possibles()[num].second;

//    return c;
//}  //fonction qui choisit un coup aléatoire







// NB: on utilise un seul arbre pour stocker les coups, et on inverse les valeurs (score) des noeuds selon que l'on gagne ou que l'on perde




//void Joueur_MonteCarlo_::recherche_coup(Jeu j, couple &coup)
//{
    //faire dérouler l'arbre

//        // Création du nœud racine de l'arbre
       // Node racine(j);

        // Lancement de la boucle de recherche
//         for (int i = 0; i < nb_iterations_; i++) {
//             // Sélection du meilleur nœud
//             Node meilleur_noeud = selection(racine);

//             // Expansion du meilleur nœud
//             Node nouveau_noeud = expansion(meilleur_noeud);

//             // Simulation à partir du nouveau nœud
//             int resultat_simulation = simulation(nouveau_noeud);

//             // update du résultat de la simulation
//             update(nouveau_noeud, resultat_simulation);
//         }

//         // Recherche du meilleur coup à jouer
//         coup = meilleur_coup(racine);

//     }




//fonction selection: sélectionne le prochain nœud à explorer en parcourant l'arbre en fonction du QUBC jusqu'à atteindre un nœud feuille.
/*
Node Joueur_MonteCarlo_::selection(Node n) const
{
    while (!n.est_terminal()) {
            if (n._enfant.empty()) {
                return n.expansion();
            } else {
                n = n.meilleur_enfant(); //meilleur_enfant() implémentée dans node.hh
            }
        }
        return n;
}
*/
