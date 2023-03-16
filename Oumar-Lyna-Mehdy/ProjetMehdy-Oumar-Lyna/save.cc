#include "save.hh"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>

int save::courant(enum::courant c){
    if(c==courant::premier){
        return 1;
    }
    return 2;
}
enum::courant save::courant(int c){
    if(c==1){
        return courant::premier;
    }
    return courant::deuxième;
}
void save::noeux(std::ofstream &file, Node arbre){

    file<<arbre._x<<" "<<arbre._y<<" "<<courant(arbre._j)<<" ";
    file<<arbre._score<<" "<<arbre._nbsim<<" "<<arbre._nbcoups<<" "<< arbre._enfant.size()<<"\n";
    if(arbre._enfant.size()!=0){
        for(auto i : arbre._enfant){
            noeux(file,i);
        }
    };
}

Node save::noeux(std::ifstream &file){
    int c;
    int j;
    Node arbre;
    file>>arbre._x;
    file>>arbre._y;
    file>>c; arbre._j=courant(c);
    file>>arbre._score;
    file>>arbre._nbsim;
    file>>arbre._nbcoups;
    file>>j;
    if(j!=0){
        for(int i(0);i<j;i++){
            arbre._enfant.push_back(noeux(file));
        }
    }
    return arbre;
}
Node save::import(std::string fichier)
{
    Node Racine;
    //ouverture fichier
    //curseur au début
    std::ifstream file(fichier);
    if(file){
        //on veut se placer ligne 2
        std::string s;
        int nbsim;
        file>>s;//deplacement curseur après nombre
        file>>s;//après de
        file>>s;//après "simalation:"
        file>> nbsim;
        //curseur normalement sur la deuxième ligne
        //lecture et deplacement du curseur dans noeux
        Racine=noeux(file);
    }
    else {
        Racine._x=-1;
        Racine._y=-1;
        Racine._nbcoups=121;
    }

    return Racine;
}

void save::exporter(Node arbre, std::string fichier)
{
    std::string const monficher(fichier+".txt");
    std::ofstream file(monficher.c_str());

    if(file) {
        //entête
        file << "nombre de simulation: "<<arbre._nbsim << "\n";
        //ecriture de l'arbre de maniere recursive
        // x y joueur(courant) score nbsimulation nbcoups nbrenfant
        // si nbrenfant==0 frère ou rien
        // autrement enfant
        noeux(file, arbre);
    }
}
