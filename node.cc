#include "node.hh"

Node::Node(const Jeu & jeu, const courant & j): _nbsim(0), _score(0), _jeu(jeu), _j(j) { }

Node::Node(const Jeu & jeu, std::vector<Node> const & enfant, int numcoup): _score(0), _nbsim(0), _enfant(enfant)  {


//    _player = _game.getCurrentPlayer();
//     _jeu.playK(numcoup);
//     _nMoves = int(_game.getMoves().size());
//      _children.reserve(_nMoves);

    //Le nombre de mouvements possibles est récupéré à partir de l'état de jeu actuel et le vecteur "_children" est initialisé avec une capacité pré-allouée égale à "_nMoves".
}

