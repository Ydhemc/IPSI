#include "node.hh"
#include <cmath>
Node::Node(): _x(0), _y(0), _j(courant::premier), _score(0), _nbsim(0), _nbcoups(0), _enfant({}) {}
int _x;
int _y;
courant _j; //joueur courant
int _score; //somme des récompenses des simulations passés par ce noeud
int _nbsim; //nombre de simulations passé par ce noeud
int _nbcoups; //nombre de coups possibles à partir de cet état du jeu
std::vector<Node> _enfant; //vecteur de noeuds enfNode(const Jeu & jeu, std::vector<Node> const & enfant, int numcoup)ant

Node::Node(const courant & j, const int & x, const int & y): _x(x), _y(y), _j(j),_score(0), _nbsim(0), _enfant({}) { }

Node::Node(std::vector<Node> const & enfant, int const & nbsim, int const & score, int const & nbcoups, int const & x, int const & y, courant const & j):_x(x), _y(y),_j(j), _score(score), _nbsim(nbsim), _nbcoups(nbcoups),  _enfant(enfant) { }


// methodes


bool Node::est_feuille() const {
    return _enfant.empty();
}

bool Node::est_terminal() const {

        return (_nbcoups == 0);     // l'état est terminal si aucun coup n'est possible
}



void Node::ajouter_enfant(const Node &enfant) {
    _enfant.push_back(enfant);
}
float Node::qubc( Node n){
    return _score+sqrt(2*(log(_nbsim)/n._nbsim));
}

//à finir
void Node::fusionnerArbres(const Node &arbre1, const Node &arbre2, Node &resultat){
    if (arbre1._enfant.empty()){
            resultat = arbre2;// si l'un des arbres est vide, il n'y a rien à faire
        }
        else if(arbre2._enfant.empty()){
            resultat = arbre1;
        }
    else {
        resultat._score = arbre1._score + arbre2._score;
        resultat._nbsim = arbre2._nbsim+arbre1._nbsim;
        resultat._nbcoups=arbre1._nbcoups;

        for (std::size_t i = 0; i < arbre2._enfant.size(); i++) {
            for (std::size_t j = 0; j < arbre1._enfant.size(); j++) {
                if (!(arbre2._enfant[i]._x == arbre1._enfant[j]._x && arbre2._enfant[i]._y == arbre1._enfant[j]._y)) {
                     resultat._enfant.push_back(arbre2._enfant[i]);
                }
                else {
                fusionnerArbres(arbre1._enfant[j],arbre2._enfant[i],resultat);
                }
            }
        }
    }
}
int Node::meilleur_coup()
{ std::size_t j=0;
  float max=Node::qubc(_enfant.at(0));
  for(std::size_t i(1);i<_enfant.size();++i){
      if (qubc(_enfant.at(i))>max){
          max=qubc(_enfant.at(i));
          j=i;
      }
  }
  return (int)j;

}

//Node & Node::selection(Node const & n) {

//    while (!n.est_terminal()) {
//        if (n._enfant.empty()) {
//            return n.expansion();  // la fonction expansion() à implémenter
//        } else {
//            n = n.meilleur_enfant(); //meilleur_enfant() à implémenter en utilisant le qubc
//        }
//    }
//    return n;
//}
