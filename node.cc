 
#include "node.hh"

Node::Node(): _x(0), _y(0), _j(courant::premier), _score(0), _nbsim(0), _nbcoups(0), _enfant({}) {}

Node::Node(const courant & j, const int & x, const int & y): _nbsim(0), _score(0), _j(j), _x(x), _y(y), _enfant({}) { }

Node::Node(std::vector<Node> const & enfant, int const & nbsim, int const & score, int const & nbcoups, int const & x, int const & y, courant const & j): _score(score), _nbsim(nbsim), _nbcoups(nbcoups), _x(x), _y(y), _enfant(enfant) { }


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

Node Node::meilleur_enfant()
{ std::size_t j=0;
  float max=qubc(_enfant.at(0));
  for(std::size_t i(1);i<_enfant.size();++i){
      if (qubc(_enfant.at(i))>max){
          max=qubc(_enfant.at(i));
          j=i;
      }
  }
  return _enfant.at(j);

}


float Node::qubc(const Node &n) {
   return _score/_nbsim+tabln[nb_simulations_total-1][_nbsim-1];//Il faudra traiter le cas où le total de simulations et le nombre de sim du noeud courant sont nuls
    }

void Node::fusionnerArbres(Node* arbre1, Node* arbre2)//Le résultat se retrouve alors dans arbre1
{
    if (!arbre1 || !arbre2) { // si l'un des arbres est vide, il n'y a rien à faire
        return;
    }

    arbre1->_score = arbre1->_score + arbre2->_score;
    arbre1->_nbsim += arbre2->_nbsim;
    arbre1->_nbcoups=arbre2->_nbcoups;

    for (std::size_t i = 0; i < arbre2->_enfant.size(); i++) {
        for (std::size_t j = 0; j < arbre1->_enfant.size(); j++) {
            if (arbre2->_enfant[i]._x != arbre1->_enfant[j]._x && arbre2->_enfant[i]._y != arbre1->_enfant[j]._y) {
                 arbre1->_enfant.push_back(arbre2->_enfant[i]);
            }
       else {
            fusionnerArbres(&arbre1->_enfant[j],&arbre2->_enfant[i]);
        }
    }
}
}

