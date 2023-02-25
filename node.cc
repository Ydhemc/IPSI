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
