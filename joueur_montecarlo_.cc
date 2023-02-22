#include "joueur_montecarlo_.hh"
#include "node.hh"


Joueur_MonteCarlo_::Joueur_MonteCarlo_(std::string nom, bool joueur)
    :Joueur(nom,joueur)
{}


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
//        Node * racine = new Node(j);

//        // Lancement de la boucle de recherche
//        for (int i = 0; i < nb_iterations_; i++) {
//            // Sélection du meilleur nœud
//            Node * meilleur_noeud = selection(racine);

//            // Expansion du meilleur nœud
//            Node * nouveau_noeud = expansion(meilleur_noeud);

//            // Simulation à partir du nouveau nœud
//            int resultat_simulation = simulation(nouveau_noeud);

//            // update du résultat de la simulation
//            update(nouveau_noeud, resultat_simulation);
//        }

//        // Recherche du meilleur coup à jouer
//        coup = meilleur_coup(racine);

//        // Libération de la mémoire allouée aux nœuds de l'arbre
//        delete_arbre(racine);
//    }

//}



//fonction selection: sélectionne le prochain nœud à explorer en parcourant l'arbre en fonction de l'UQBC jusqu'à atteindre un nœud feuille.

Node Joueur_MonteCarlo_::selection(Node noeud)
{
    while (!noeud.est_feuille()) {
        if (noeud.tous_les_enfants_visites()) {
            noeud = noeud.uqbc();
        }
        else {
            return expansion(noeud);
        }
    }
    return noeud;
}
