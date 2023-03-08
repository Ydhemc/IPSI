#include "apprentissage.hh"

apprentissage::apprentissage(player player1, player player2, int nombre_parties, Node n):
_jeu(11),
_coups(nombre_parties),
_coups_mutex(nombre_parties),
_nombre_parties(nombre_parties),
_numero_partie(1),
_player1(player1),
_player2(player2),
_n(n)
{}



void apprentissage::initialisation()
{
    _joueur1=nullptr;
    _joueur2=nullptr;

    _jeu.vider_jeu();


    //si le numero de partie est pair, c'est _joueur1 qui commence
    switch (((_numero_partie%2)? _player1 : _player2)) {
        case player::M_1:
            _joueur1 = std::make_shared<Joueur_MonteCarlo_> ("MonteCarlo",true);
            break;
        case player::M_2:
            _joueur1 = std::make_shared<Joueur_MonteCarlo_> ("StoMonteCarlo",true);
            break;
        case player::MANUEL:
            _joueur1 = std::make_shared<Joueur_Manuel> ("Avenger",true);
            break;
        case player::MANUEL2:
            _joueur1 = std::make_shared<Joueur_Manuel> ("Vio",true);
            break;
        case player::RAND:
            _joueur1 = std::make_shared<Joueur_Random> ("Random",true);
            break;
        case player::RAND2:
            _joueur1 = std::make_shared<Joueur_Random> ("Aleatoire",true);
            break;
        case player::A_1:
        _joueur1 = std::make_shared<Joueur_AlphaBeta> ("AlphaBeta",true);
        break;
        case player::A_2:
        _joueur1 = std::make_shared<Joueur_AlphaBeta> ("MaxAlphaBeta",true);
        break;
        default:
            break;
        }

    //si le numero de partie est impair, c'est _joueur2 qui commence
    switch (((!(_numero_partie%2))? _player1 : _player2)) {
        case player::M_1:
            _joueur2 = std::make_shared<Joueur_MonteCarlo_> ("MonteCarlo",false);
            break;
        case player::M_2:
            _joueur2 = std::make_shared<Joueur_MonteCarlo_> ("StoMonteCarlo",false);
            break;
        case player::MANUEL:
            _joueur2 = std::make_shared<Joueur_Manuel> ("Caro",false);
            break;
        case player::MANUEL2:
            _joueur2 = std::make_shared<Joueur_Manuel> ("Vio",false);
            break;
        case player::RAND:
            _joueur2 = std::make_shared<Joueur_Random> ("Random",false);
            break;
        case player::RAND2:
            _joueur2 = std::make_shared<Joueur_Random> ("Aleatoire",false);
            break;
        case player::A_1:
            _joueur1 = std::make_shared<Joueur_AlphaBeta> ("AlphaBeta",false);
            break;
        case player::A_2:
            _joueur1 = std::make_shared<Joueur_AlphaBeta> ("MaxAlphaBeta",false);
            break;
        default:
            break;
        }

}


int apprentissage::challenge()
{
    initialisation(); // Au moins une fois pour que les objets de la ligne qui suit soient définis
    std::cout << "Le challenge de " << _nombre_parties << " parties "
              <<"entre " << _joueur1->nom() << " et " << _joueur2->nom()
             << " commence. " << std::endl;
    int victoire_joueur_1 = 0;
    int victoire_joueur_2 = 0;
    while( _numero_partie <= _nombre_parties)
        {
            std::cout << "\n" << "Partie n°" << _numero_partie << " : "<<std::endl<<_jeu;

            //lancement d'une partie
            std::pair<result,std::vector<couple>> resultat = partie();

            if (resultat.first == result::ERREUR)
                {
                    std::cerr << "Alerte bug. Sauvez votre terminal et prévenez Me Devred. Merci. " << std::endl;
                    return 1;
                } else if (resultat.first != result::NULLE)
                      (resultat.first==result::P1?
                        ((_numero_partie%2)?
                             victoire_joueur_1++
                           :
                             victoire_joueur_2++ )
                      :
                        (!(_numero_partie%2)?
                             victoire_joueur_1++
                           :
                             victoire_joueur_2++ ));

            updatev2(resultat.second, _n,  apprentissage::resultat(resultat.first));

            //lancement d'une nouvelle partie
            std::this_thread::sleep_for (std::chrono::milliseconds(2500)); // temps de latence entre deux parties
            _numero_partie++;
            initialisation();

        }
    std::cout << "FIN DU CHALLENGE\n\t"
              << _joueur1->nom()<< " gagne " << ((_numero_partie%2)? victoire_joueur_1 : victoire_joueur_2)
              << "\n\t"<< _joueur2->nom()<< " gagne " << ((_numero_partie%2) ? victoire_joueur_2 : victoire_joueur_1) << std::endl;
    return 0;
}


std::pair<result,std::vector<couple>> apprentissage::partie()
{
    //le vector pour faire le update
    std::vector<couple> c;
    std::pair<result,std::vector<couple>> res;

    int tour = 0;
    bool coup_ok; //si le coup est valide
    while(!_jeu.partie_finie())
        {
            bool try_lock = false;
            _coups[_numero_partie-1].first = -1;
            _coups[_numero_partie-1].second = -1;
            coup_ok=true;
            tour++;
            std::cout << "tour : " << tour << std::endl;
            _coups_mutex[_numero_partie-1].unlock();

            std::thread thread_joueur(&Joueur::jouer,
                                      ((tour%2)? (_joueur1) :(_joueur2) ),
                                      _jeu,
                                      std::ref(_coups[_numero_partie-1]),
                    std::ref(_coups_mutex[_numero_partie-1]));

            std::this_thread::sleep_for (std::chrono::milliseconds(TEMPS_POUR_UN_COUP));
            //        std::this_thread::sleep_for (std::chrono::seconds(TEMPS_POUR_UN_COUP));

            if (!_coups_mutex[_numero_partie-1].try_lock()) {
                    std::cerr <<  std::endl << "mutex non rendu " << std::endl;
                    try_lock = true;
                }
            else if(_jeu.case_libre(_coups[_numero_partie-1]) == false) {
                    std::cerr << "coup invalide abs : " <<_coups[_numero_partie-1].second<<" ,ord : "<< _coups[_numero_partie-1].first<< std::endl;
                    coup_ok = false;
                }

            thread_joueur.detach();

            if(try_lock || !coup_ok )
                {
                   if(tour%2)
                        {
                            std::cout << _joueur2->nom() <<" gagne ! Nombre de tours : " << tour << std::endl;
                            res.first= result::P2;
                            res.second=c;
                            return res; // joueur jouant en 2eme gagne
                        }
                    else
                        {
                            std::cout << _joueur1->nom() <<" gagne ! Nombre de tours : " << tour << std::endl;
                            res.first=result::P1;
                            res.second=c;
                            return  res ;// joueur jouant en 1er gagne
                        }
                }
            //On joue le coup, on l'affiche et on affiche le plateau
            _jeu.jouer_coup(_coups[_numero_partie-1],(tour%2) ? 1 : 2 );
            std::cout << ((tour%2) ? _joueur1->nom() : _joueur2->nom())<<" abs : " <<_coups[_numero_partie-1].second<<" ord : "<< _coups[_numero_partie-1].first
                      << std::endl << _jeu << std::endl
                         ;
            //on stock le coups à jouer
        }


    //si aucun ne gagne alors egalité
    if (_jeu.cotes_relies()!=1 && _jeu.cotes_relies()!=2)
        {
            std::cout << std::endl << "Partie nulle" << std::endl;
            res.first=result::NULLE;
            res.second=c;
            return  res ;
        }
    else
    if (_jeu.cotes_relies()==1)
        {
            std::cout << std::endl << _joueur1->nom()  <<" gagne. Nombre de tours : " << tour << std::endl;
            res.first=result::P1;
            res.second=c;
            return  res ;

        }
    else if (_jeu.cotes_relies()==2)
        {
            std::cout << std::endl << _joueur2->nom()  <<" gagne. Nombre de tours : " << tour << std::endl;
            res.first= result::P2;
            res.second=c;
            return res;
        }

    res.first= result::ERREUR;
    res.second=c;
    return res;

}


int apprentissage::resultat(result r)
{
    {
        switch(r){
        case result::P1:return 1;break;
        case result::P2 :return -1;break;
        case result::ERREUR :return -10;break;
        case result::NULLE  :return 0;break;

        }
    }
    return 0;
}

void apprentissage::updatev2(std::vector<couple> v, Node &root, int r)
{
    int j(-1);
    if(!v.empty()){
    //cherche la branche qui à été visité
      while (root._enfant.at(j)._x !=v.at(0).first && root._enfant.at(j)._y != v.at(0).second){
        ++j;
        }
      //si le noeud n'a pas été trouver donc n'existe pas alors on le créé
      if(j==(int)root._enfant.size() && ( root._enfant.at(j)._x !=v.at(0).first && root._enfant.at(j)._y != v.at(0).second) ){
        Node n;
        n._x=v.at(0).first;
        n._y=v.at(0).second;
        n._nbcoups=root._enfant.at(0)._nbcoups;
        if(root._j==courant::premier)
            n._j=courant::deuxième;
        else
            n._j=courant::premier;
        n._score=r;
        n._nbsim++;
        //pas besoin de continuer car on crée un nouveau noeud par update
      }
      else {
        root._enfant.at(j)._nbsim++;
        root._enfant.at(j)._score += r;

        v.erase(v.begin());

        //rapelle de la fonction pour la continuer la descente de l'arbre
        updatev2(v, root._enfant.at(j), r);
      }
    }
}
