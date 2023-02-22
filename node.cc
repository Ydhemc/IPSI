#include "node.hh"

Node::Node(const courant & j): _nbsim(0), _score(0), _j(j) { }

Node::Node(std::vector<Node> const & enfant, int nbsim, int score, int nbcoups,int numcoup): _score(score), _nbsim(nbsim), _nbcoups(nbcoups), _enfant(enfant) {


//    _player = _game.getCurrentPlayer();
//     _nMoves = int(_game.getMoves().size());
//      _children.reserve(_nMoves);

    //Le nombre de mouvements possibles est récupéré à partir de l'état de jeu actuel et le vecteur "_children" est initialisé avec une capacité pré-allouée égale à "_nMoves".
}

